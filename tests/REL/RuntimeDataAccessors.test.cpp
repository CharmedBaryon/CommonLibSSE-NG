#include "catch2/catch_all.hpp"

#include "REL/REL.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/SKSE.h"

#include <array>
#include <cstdint>
#include <cstring>

using namespace REL::literals;

namespace
{
#if defined(SKYRIM_CROSS_VR)
	struct FakeRuntimeData
	{
		std::uint32_t sentinel;
	};

	struct alignas(alignof(FakeRuntimeData)) FakeAccessorHost
	{
		std::uint8_t pad[0x40]{};
		RUNTIME_DATA_ACCESSOR(FakeRuntimeData, 0x10, 0x20)
	};

	struct alignas(alignof(FakeRuntimeData)) FakeCastHost
	{
		std::uint8_t pad[0x40]{};
		RUNTIME_CAST_ACCESSOR(FakeRuntimeData, AsRuntimeData, 0x10, 0x20)
	};

	struct alignas(alignof(FakeRuntimeData)) FakePointerHost
	{
		std::uint8_t pad[0x40]{};
		SE_ONLY_POINTER_ACCESSOR(FakeRuntimeData, GetSEData, 0x10)
		VR_ONLY_POINTER_ACCESSOR(FakeRuntimeData, GetVRData, 0x20)
		AE_ONLY_POINTER_ACCESSOR(FakeRuntimeData, GetAEData, 0x28)
	};

	constexpr std::uint32_t kSESentinel = 0xDEADBEEF;
	constexpr std::uint32_t kAESentinel = 0xBAADF00D;
	constexpr std::uint32_t kVRSentinel = 0xCAFEF00D;
	constexpr std::uint32_t kSEAndAESentinel = 0xAAAAAAAA;
	constexpr std::uint32_t kVROffsetSentinel = 0xBBBBBBBB;
	constexpr std::uint32_t kOlderSentinel = 0x11111111;
	constexpr std::uint32_t kNewerSentinel = 0x22222222;

	TEST_CASE("Relocate/ThreeWaySelection", "[unit]")
	{
		SECTION("SE selects the first argument")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::Relocate(1, 2, 3) == 1);
			REL::Module::reset();
		}
		SECTION("AE selects the second argument")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::Relocate(1, 2, 3) == 2);
			REL::Module::reset();
		}
		SECTION("VR selects the third argument")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			REQUIRE(REL::Relocate(1, 2, 3) == 3);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("RelocateMember/SelectsCorrectOffset", "[unit]")
	{
		alignas(alignof(std::uint32_t)) std::array<std::uint8_t, 0x30> buffer{};
		std::memcpy(buffer.data() + 0x10, &kSEAndAESentinel, sizeof(kSEAndAESentinel));
		std::memcpy(buffer.data() + 0x20, &kVROffsetSentinel, sizeof(kVROffsetSentinel));

		SECTION("SE uses the shared offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::RelocateMember<std::uint32_t>(buffer.data(), 0x10, 0x20) == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("AE uses the shared offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::RelocateMember<std::uint32_t>(buffer.data(), 0x10, 0x20) == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("VR uses the VR-specific offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			REQUIRE(REL::RelocateMember<std::uint32_t>(buffer.data(), 0x10, 0x20) == kVROffsetSentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("RelocateMemberIfNewer/VersionGate", "[unit]")
	{
		alignas(alignof(std::uint32_t)) std::array<std::uint8_t, 0x30> buffer{};
		constexpr std::ptrdiff_t                                       kOlderOffset = 0x08;
		constexpr std::ptrdiff_t                                       kNewerOffset = 0x18;
		std::memcpy(buffer.data() + kOlderOffset, &kOlderSentinel, sizeof(kOlderSentinel));
		std::memcpy(buffer.data() + kNewerOffset, &kNewerSentinel, sizeof(kNewerSentinel));

		const REL::Version gateVersion = SKSE::RUNTIME_SSE_1_6_353;

		SECTION("Older runtime uses the older offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::RelocateMemberIfNewer<std::uint32_t>(gateVersion, buffer.data(), kOlderOffset, kNewerOffset) == kOlderSentinel);
			REL::Module::reset();
		}
		SECTION("Newer runtime uses the newer offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_629, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::RelocateMemberIfNewer<std::uint32_t>(gateVersion, buffer.data(), kOlderOffset, kNewerOffset) == kNewerSentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("RUNTIME_DATA_ACCESSOR/CrossRuntimeCorrectness", "[unit]")
	{
		FakeAccessorHost host{};
		std::memcpy(host.pad + 0x10, &kSEAndAESentinel, sizeof(kSEAndAESentinel));
		std::memcpy(host.pad + 0x20, &kVROffsetSentinel, sizeof(kVROffsetSentinel));

		SECTION("SE reads from the shared offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(host.GetRuntimeData().sentinel == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("AE reads from the shared offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(host.GetRuntimeData().sentinel == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("VR reads from the VR-specific offset")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			REQUIRE(host.GetRuntimeData().sentinel == kVROffsetSentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("SE_ONLY_POINTER_ACCESSOR/NullInVR", "[unit]")
	{
		FakePointerHost host{};
		std::memcpy(host.pad + 0x10, &kSESentinel, sizeof(kSESentinel));

		SECTION("VR returns nullptr")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			REQUIRE(host.GetSEData() == nullptr);
			REL::Module::reset();
		}
		SECTION("SE returns a pointer to the correct data")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			auto* data = host.GetSEData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kSESentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("VR_ONLY_POINTER_ACCESSOR/NullOutsideVR", "[unit]")
	{
		FakePointerHost host{};
		std::memcpy(host.pad + 0x20, &kVRSentinel, sizeof(kVRSentinel));

		SECTION("SE returns nullptr")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(host.GetVRData() == nullptr);
			REL::Module::reset();
		}
		SECTION("VR returns a pointer to the correct data")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			auto* data = host.GetVRData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kVRSentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("AE_ONLY_POINTER_ACCESSOR/NullOutsideAE", "[unit]")
	{
		FakePointerHost host{};
		std::memcpy(host.pad + 0x28, &kAESentinel, sizeof(kAESentinel));

		SECTION("SE returns nullptr")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(host.GetAEData() == nullptr);
			REL::Module::reset();
		}
		SECTION("AE returns a pointer to the correct data")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			auto* data = host.GetAEData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kAESentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("RUNTIME_CAST_ACCESSOR/CrossRuntimeCorrectness", "[unit]")
	{
		FakeCastHost host{};
		std::memcpy(host.pad + 0x10, &kSEAndAESentinel, sizeof(kSEAndAESentinel));
		std::memcpy(host.pad + 0x20, &kVROffsetSentinel, sizeof(kVROffsetSentinel));

		SECTION("SE returns a pointer to the shared layout")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			auto* data = host.AsRuntimeData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("AE returns a pointer to the shared layout")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			auto* data = host.AsRuntimeData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kSEAndAESentinel);
			REL::Module::reset();
		}
		SECTION("VR returns a pointer to the VR-specific layout")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			auto* data = host.AsRuntimeData();
			REQUIRE(data != nullptr);
			REQUIRE(data->sentinel == kVROffsetSentinel);
			REL::Module::reset();
		}
		REL::Module::reset();
	}

	TEST_CASE("Module/RuntimeQueries", "[unit]")
	{
		SECTION("SE")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::Module::GetRuntime() == REL::Module::Runtime::SE);
			REQUIRE(REL::Module::IsSE());
			REQUIRE_FALSE(REL::Module::IsAE());
			REQUIRE_FALSE(REL::Module::IsVR());
			REL::Module::reset();
		}
		SECTION("AE")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
			REQUIRE(REL::Module::GetRuntime() == REL::Module::Runtime::AE);
			REQUIRE_FALSE(REL::Module::IsSE());
			REQUIRE(REL::Module::IsAE());
			REQUIRE_FALSE(REL::Module::IsVR());
			REL::Module::reset();
		}
		SECTION("VR")
		{
			REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
			REQUIRE(REL::Module::GetRuntime() == REL::Module::Runtime::VR);
			REQUIRE_FALSE(REL::Module::IsSE());
			REQUIRE_FALSE(REL::Module::IsAE());
			REQUIRE(REL::Module::IsVR());
			REL::Module::reset();
		}
		REL::Module::reset();
	}
#endif
}
