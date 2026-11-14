#include "catch2/catch_all.hpp"

#include "RE/S/State.h"
#include "REL/Module.h"
#include "SKSE/Impl/PCH.h"
#include "SKSE/Version.h"

#include <array>
#include <cstddef>
#include <tuple>

namespace
{
	using Runtime = REL::Module::Runtime;
	constexpr std::array kRuntimeCases{
#ifdef ENABLE_SKYRIM_SE
		std::tuple{ SKSE::RUNTIME_SSE_1_5_97, Runtime::SE, std::size_t{ 0x50 } },
#endif
#ifdef ENABLE_SKYRIM_AE
		std::tuple{ SKSE::RUNTIME_SSE_1_6_353, Runtime::AE, std::size_t{ 0x54 } },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1170, Runtime::AE, std::size_t{ 0x54 } },
		std::tuple{ SKSE::RUNTIME_SSE_1_7_99, Runtime::AE, std::size_t{ 0x60 } },
		std::tuple{ REL::Version{ 1, 7, 104, 0 }, Runtime::AE, std::size_t{ 0x60 } },
#endif
#ifdef ENABLE_SKYRIM_VR
		std::tuple{ SKSE::RUNTIME_VR_1_4_15, Runtime::VR, std::size_t{ 0x50 } },
#endif
	};
}

TEST_CASE("BSGraphics::State/InsideFrame", "[unit][graphics-state]")
{
	const auto [version, runtime, offset] = GENERATE(Catch::Generators::from_range(kRuntimeCases));
	CAPTURE(version.string());
	REQUIRE(REL::Module::mock(version, runtime, L"StateTest.exe", 0x1000));
	const SKSE::stl::scope_exit reset{ [] { REL::Module::reset(); } };

	alignas(RE::BSGraphics::State) std::array<std::byte, 0x200> storage{};
	auto*                                                       state = reinterpret_cast<RE::BSGraphics::State*>(storage.data());
#ifdef ENABLE_SKYRIM_AE
	auto& insideFrame = state->GetInsideFrame();
#else
	auto& insideFrame = state->insideFrame;
#endif
	CHECK(reinterpret_cast<std::byte*>(&insideFrame) == storage.data() + offset);
	storage[offset] = std::byte{ 1 };
	CHECK(insideFrame);
	insideFrame = false;
	CHECK(storage[offset] == std::byte{ 0 });
	insideFrame = true;
	for (std::size_t index = 0; index < storage.size(); ++index) {
		CAPTURE(index);
		CHECK(storage[index] == (index == offset ? std::byte{ 1 } : std::byte{ 0 }));
	}
}
