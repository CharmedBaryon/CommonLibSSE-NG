#include <iostream>

// Include CommonLib headers that contain STATIC_ASSERT_SIZE calls
// The key test is that these headers compile without errors when CommonLib is consumed as a dependency
#include "RE/A/Actor.h"
#include "RE/M/MapMenu.h"
#include "RE/N/NiNode.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/R/RaceSexMenu.h"
#include "RE/T/TESObjectREFR.h"

// This test validates that CommonLib's internal STATIC_ASSERT_SIZE macros compile correctly
// when the library is used as a dependency (via add_subdirectory).
//
// THE ACTUAL ISSUE:
// When Community Shaders (or any consumer) added CommonLib via add_subdirectory(), the build
// failed with errors like:
//   "error C2338: STATIC_ASSERT_SIZE requires at least 2 arguments: ClassName and Size"
//   "error C2065: 'RTTI_PlayerCharacter': undeclared identifier"
//   "error C2653: 'stl': is not a class or namespace name"
//
// These errors were in CommonLib's OWN headers (PlayerCharacter.h, Actor.h, RaceSexMenu.h, etc.),
// NOT in the consumer's code. The consumer wasn't using STATIC_ASSERT_SIZE at all!
//
// Without /Zc:preprocessor, the variadic macro dispatcher in REL/Common.h doesn't work
// with MSVC's traditional preprocessor, causing all STATIC_ASSERT_SIZE calls to fail.
//
// IMPORTANT: Consumer code must use CommonLib's PCH (SKSE/SKSE.h and RE/Skyrim.h) to get
// the necessary RTTI macros, namespace definitions, and literal operators.

int main()
{
	std::cout << "CommonLib consumer integration test\n";
	std::cout << "====================================\n\n";

	std::cout << "Testing that CommonLib headers compile when used as a dependency...\n";
	std::cout << "All headers included successfully!\n\n";

	// These are CommonLib's classes - the static_asserts are in CommonLib's headers
	// If /Zc:preprocessor was missing, the #include statements above would have failed to compile
	std::cout << "CommonLib class sizes (validated by STATIC_ASSERT_SIZE in headers):\n";
	std::cout << "  PlayerCharacter: " << sizeof(RE::PlayerCharacter) << " bytes\n";
	std::cout << "  Actor: " << sizeof(RE::Actor) << " bytes\n";
	std::cout << "  RaceSexMenu: " << sizeof(RE::RaceSexMenu) << " bytes\n";
	std::cout << "  MapMenu: " << sizeof(RE::MapMenu) << " bytes\n";
	std::cout << "  NiNode: " << sizeof(RE::NiNode) << " bytes\n";
	std::cout << "  TESObjectREFR: " << sizeof(RE::TESObjectREFR) << " bytes\n";

	std::cout << "\n✓ Test PASSED: CommonLib's STATIC_ASSERT_SIZE macros compiled successfully\n";
	std::cout << "✓ /Zc:preprocessor flag is working correctly\n";
	std::cout << "✓ Consumer code doesn't need to know about STATIC_ASSERT_SIZE macro\n";

	return 0;
}
