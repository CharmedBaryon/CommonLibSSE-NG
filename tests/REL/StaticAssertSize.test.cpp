#include "catch2/catch_all.hpp"

#include "REL/Relocation.h"

// Test that STATIC_ASSERT_SIZE macro compiles correctly with various argument counts
// This validates that /Zc:preprocessor is enabled and the variadic macro dispatcher works

namespace
{
	// Test class with known size
	struct TestClass1
	{
		std::uint64_t a;
		std::uint32_t b;
	};

	// 2 args: ClassName, Size (same for all runtimes)
	STATIC_ASSERT_SIZE(TestClass1, 0x10);

	struct TestClass2
	{
		std::uint64_t a;
		std::uint32_t b;
		std::uint32_t c;
	};

	// 3 args: ClassName, FlatSize, VRSize
	STATIC_ASSERT_SIZE(TestClass2, 0x10, 0x10);

	struct TestClass3
	{
		std::uint64_t a;
		std::uint64_t b;
	};

	// 4 args: ClassName, SESize, AESize, VRSize
	STATIC_ASSERT_SIZE(TestClass3, 0x10, 0x10, 0x10);

	struct TestClass4
	{
		std::uint64_t a;
		std::uint64_t b;
		std::uint32_t c;
	};

	// 5 args: ClassName, SESize, AESize, VRSize, AllSize
	STATIC_ASSERT_SIZE(TestClass4, 0x18, 0x18, 0x18, 0x18);

	struct TestClass5
	{
		std::uint64_t a;
		std::uint64_t b;
		std::uint64_t c;
	};

	// 6 args: ClassName, SESize, AESize, VRSize, AllSize, FlatSize
	STATIC_ASSERT_SIZE(TestClass5, 0x18, 0x18, 0x18, 0x18, 0x18);
}

TEST_CASE("STATIC_ASSERT_SIZE/VariadicMacroDispatch")
{
	SECTION("2 arguments compile")
	{
		// If this test compiles, the 2-arg variant works
		CHECK(sizeof(TestClass1) == 0x10);
	}

	SECTION("3 arguments compile")
	{
		// If this test compiles, the 3-arg variant works
		CHECK(sizeof(TestClass2) == 0x10);
	}

	SECTION("4 arguments compile")
	{
		// If this test compiles, the 4-arg variant works
		CHECK(sizeof(TestClass3) == 0x10);
	}

	SECTION("5 arguments compile")
	{
		// If this test compiles, the 5-arg variant works
		CHECK(sizeof(TestClass4) == 0x18);
	}

	SECTION("6 arguments compile")
	{
		// If this test compiles, the 6-arg variant works
		CHECK(sizeof(TestClass5) == 0x18);
	}
}

TEST_CASE("STATIC_ASSERT_SIZE/PreprocessorConformance")
{
	// This test validates that /Zc:preprocessor is enabled
	// Without it, the variadic macro dispatcher fails and all STATIC_ASSERT_SIZE
	// calls incorrectly route to _STATIC_ASSERT_SIZE_1, causing compile errors

	SECTION("Macro expands correctly")
	{
		// The fact that this file compiles proves the preprocessor is working
		// If /Zc:preprocessor is missing, compilation fails with:
		// "STATIC_ASSERT_SIZE requires at least 2 arguments: ClassName and Size"
		CHECK(true);
	}
}
