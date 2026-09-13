#include "catch2/catch_all.hpp"

#include "RE/B/BSShaderAccumulator.h"
#include "REL/REL.h"
#include "SKSE/SKSE.h"

#include <array>
#include <cstdint>
#include <tuple>
#include <type_traits>

static_assert(std::is_same_v<RE::BSGraphics::BSShaderAccumulator, RE::BSShaderAccumulator>);

#if defined(SKYRIM_CROSS_VR)
namespace
{
	struct AccumulatorFixture
	{
		AccumulatorFixture(REL::Version a_version, REL::Module::Runtime a_runtime)
		{
			REQUIRE(REL::Module::mock(a_version, a_runtime, L"AccumulatorTest.exe", 0x1000));
		}

		~AccumulatorFixture() { REL::Module::reset(); }

		alignas(8) std::array<std::byte, 0x1B0> storage{};
	};
}

TEST_CASE("BSShaderAccumulator/RuntimeDataOffsets", "[unit][shader-accumulator]")
{
	using Runtime = REL::Module::Runtime;
	const auto [version, runtime, tail] = GENERATE(
		std::tuple{ SKSE::RUNTIME_SSE_1_5_97, Runtime::SE, 0x130 },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1170, Runtime::AE, 0x130 },
		std::tuple{ REL::Version{ 1, 7, 104, 0 }, Runtime::AE, 0x130 },
		std::tuple{ SKSE::RUNTIME_VR_1_4_15, Runtime::VR, 0x158 });
	CAPTURE(version.string());
	AccumulatorFixture fixture(version, runtime);
	auto*              accumulator = reinterpret_cast<RE::BSShaderAccumulator*>(fixture.storage.data());
	auto*              base = fixture.storage.data();

	SECTION("the shared render-state tail lands at the runtime's offset")
	{
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData()) == base + tail);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData().batchRenderer) == base + tail);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData().currentPass) == base + tail + 0x8);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData().activeShadowSceneNode) == base + tail + 0x18);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData().renderMode) == base + tail + 0x20);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeData().eyePosition) == base + tail + 0x3C);
	}

	SECTION("the full view is the one this runtime owns")
	{
		if (runtime == Runtime::VR) {
			CHECK(accumulator->GetFlatRuntimeData() == nullptr);
			CHECK(reinterpret_cast<std::byte*>(accumulator->GetVRRuntimeData()) == base + 0x58);
		} else {
			CHECK(reinterpret_cast<std::byte*>(accumulator->GetFlatRuntimeData()) == base + 0x58);
			CHECK(accumulator->GetVRRuntimeData() == nullptr);
		}
	}

	SECTION("the flags sit at one offset on every runtime")
	{
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeFlags()) == base + 0x128);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeFlags().firstPerson) == base + 0x128);
		CHECK(reinterpret_cast<std::byte*>(&accumulator->GetRuntimeFlags().drawDecals) == base + 0x12C);
	}
}
#endif
