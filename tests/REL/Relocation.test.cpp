#define CATCH2_CONFIG_MAIN
#include "catch2/catch_all.hpp"

#include "REL/REL.h"
#include "SKSE/SKSE.h"

using namespace REL::literals;

TEST_CASE("Version/DefaultConstructor")
{
	REL::Version v;
	CHECK(v[0] == 0);
	CHECK(v[1] == 0);
	CHECK(v[2] == 0);
	CHECK(v[3] == 0);
}

TEST_CASE("Version/Parts")
{
	SECTION("Major")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.major() == 1);
	}
	SECTION("Minor")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.minor() == 5);
	}
	SECTION("Patch")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.patch() == 97);
	}
	SECTION("Build")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.build() == 0);
	}
}

TEST_CASE("Version/IndexOperator")
{
	REL::Version v = SKSE::RUNTIME_SSE_1_5_97;
	CHECK(v[0] == 1);
	CHECK(v[1] == 5);
	CHECK(v[2] == 97);
	CHECK(v[3] == 0);
}

TEST_CASE("Version/Stringify")
{
	SECTION("With default separator")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.string() == "1-5-97-0");
		CHECK(SKSE::RUNTIME_SSE_1_5_97.wstring() == L"1-5-97-0");
	}
	SECTION("With char separator")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.string(".") == "1.5.97.0");
		CHECK(SKSE::RUNTIME_SSE_1_5_97.wstring(L".") == L"1.5.97.0");
	}
	SECTION("With string separator")
	{
		CHECK(SKSE::RUNTIME_SSE_1_5_97.string("..") == "1..5..97..0");
		CHECK(SKSE::RUNTIME_SSE_1_5_97.wstring(L"..") == L"1..5..97..0");
	}
}

TEST_CASE("Version/std::to_string")
{
	CHECK(std::to_string(SKSE::RUNTIME_SSE_1_5_97) == "1.5.97.0");
}

#ifdef FMT_VERSION
// NOTE: fmt has been deprecated in favor of std::format
TEST_CASE("Version/fmt::format")
{
	CHECK(fmt::format("Hello {}", SKSE::RUNTIME_SSE_1_5_97) == "Hello 1-5-97-0");
}
#endif

TEST_CASE("Version/std::format")
{
	CHECK(std::format("Hello {}", std::to_string(SKSE::RUNTIME_SSE_1_5_97)) == "Hello 1.5.97.0");
	// Test wide-character formatting to verify formatter<std::string, CharT> handles conversion
	CHECK(std::format(L"Hello {}", SKSE::RUNTIME_SSE_1_5_97) == L"Hello 1-5-97-0");
}

TEST_CASE("Version/StringConstructor")
{
	SECTION("Handles good input")
	{
		CHECK(REL::Version("3") == REL::Version{ 3 });
		CHECK(REL::Version("3.6") == REL::Version{ 3, 6 });
		CHECK(REL::Version("3.6.123") == REL::Version{ 3, 6, 123 });
		constexpr auto version = REL::Version("3.6.123.41");
		CHECK(version == REL::Version{ 3, 6, 123, 41 });
	}
	SECTION("Throws exception on too many parts")
	{
		CHECK_THROWS(REL::Version("3.6.123.41.456"));
	}
	SECTION("Throws exception on invalid character")
	{
		CHECK_THROWS(REL::Version("3.6.123.abc"));
	}
}

TEST_CASE("Version/StringLiteral")
{
	SECTION("Handles good input")
	{
		CHECK("3"_v == REL::Version{ 3 });
		CHECK("3.6"_v == REL::Version{ 3, 6 });
		CHECK("3.6.123"_v == REL::Version{ 3, 6, 123 });
		constexpr auto version = "3.6.123.41"_v;
		CHECK(version == REL::Version{ 3, 6, 123, 41 });
	}
	SECTION("Throws exception on too many parts")
	{
		CHECK_THROWS("3.6.123.41.456"_v);
	}
	SECTION("Throws exception on invalid character")
	{
		CHECK_THROWS("3.6.123.abc"_v);
	}
}

TEST_CASE("Version/NumberLiteral")
{
	CHECK(33_v == REL::Version{ 33 });
	constexpr auto version = 33.678_v;
	CHECK(version == REL::Version{ 33, 678 });
}

TEST_CASE("Version/Iterator")
{
	auto iter = SKSE::RUNTIME_SSE_1_5_97.begin();
	CHECK(*(iter++) == 1);
	CHECK(*(iter++) == 5);
	CHECK(*(iter++) == 97);
	CHECK(*(iter++) == 0);
	CHECK(iter == SKSE::RUNTIME_SSE_1_5_97.end());
}

TEST_CASE("Version/ConstIterator")
{
	auto iter = SKSE::RUNTIME_SSE_1_5_97.cbegin();
	CHECK(*(iter++) == 1);
	CHECK(*(iter++) == 5);
	CHECK(*(iter++) == 97);
	CHECK(*(iter++) == 0);
	CHECK(iter == SKSE::RUNTIME_SSE_1_5_97.cend());
}

TEST_CASE("Version/Pack")
{
	CHECK(SKSE::RUNTIME_SSE_1_5_97.pack() == 0x01050610);
	CHECK(SKSE::RUNTIME_SSE_1_6_353.pack() == 0x01061610);
	CHECK(REL::Version().pack() == 0);
}

TEST_CASE("Version/Unpack")
{
	CHECK(REL::Version::unpack(0x01050610) == SKSE::RUNTIME_SSE_1_5_97);
	CHECK(REL::Version::unpack(0x01061610) == SKSE::RUNTIME_SSE_1_6_353);
	CHECK(REL::Version::unpack(0) == REL::Version());
}

TEST_CASE("Version/Compare")
{
	CHECK(SKSE::RUNTIME_SSE_1_5_97.compare(SKSE::RUNTIME_SSE_1_6_353) == std::strong_ordering::less);
	CHECK(SKSE::RUNTIME_SSE_1_6_353.compare(SKSE::RUNTIME_SSE_1_5_97) == std::strong_ordering::greater);
	CHECK(SKSE::RUNTIME_SSE_1_5_97.compare(SKSE::RUNTIME_SSE_1_5_97) == std::strong_ordering::equal);
	CHECK(REL::Version(1, 0, 0, 0).compare(REL::Version(2, 0, 0, 0)) == std::strong_ordering::less);
	CHECK(REL::Version(1, 3, 0, 0).compare(REL::Version(0, 2, 0, 0)) == std::strong_ordering::greater);
}

#ifdef ENABLE_SKYRIM_SE
TEST_CASE("Module/SupportsSkyrimSE")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_5_97, REL::Module::Runtime::SE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\version-1-5-97-0.bin", REL::IDDB::Format::SSEv1, SKSE::RUNTIME_SSE_1_5_97));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x10f5c0);
	}
	SECTION("REL::ID gets correct address and offset")
	{
		REL::ID id(11483);
		CHECK(id.offset() == 0x10f5c0);
		CHECK(id.address() == 0x1105c0);
	}
	SECTION("REL::RelocationID gets correct address and offset")
	{
		static REL::RelocationID id(11483, 0);
		CHECK(id.offset() == 0x10f5c0);
		CHECK(id.address() == 0x1105c0);
	}
	SECTION("REL::VariantID gets correct address and offset")
	{
		REL::VariantID id(11483, 0, 0);
		CHECK(id.offset() == 0x10f5c0);
		CHECK(id.address() == 0x1105c0);
	}
	SECTION("REL::VariantOffset gets the correct address and offset")
	{
		REL::VariantOffset offset(0x10f5c0, 0, 0);
		CHECK(offset.offset() == 0x10f5c0);
		CHECK(offset.address() == 0x1105c0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}
#endif

#ifdef ENABLE_SKYRIM_AE
TEST_CASE("Module/SupportsSkyrimAE_1_6_353")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-6-353-0.bin", REL::IDDB::Format::SSEv2, SKSE::RUNTIME_SSE_1_6_353));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x10f7a0);
	}
	SECTION("REL::ID gets correct address and offset")
	{
		REL::ID id(11483);
		CHECK(id.offset() == 0x10f7a0);
		CHECK(id.address() == 0x1107a0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}

TEST_CASE("Module/SupportsSkyrimAE_1_6_629")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_629, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-6-629-0.bin", REL::IDDB::Format::SSEv2, SKSE::RUNTIME_SSE_1_6_629));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x1113f0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}

TEST_CASE("Module/SupportsSkyrimAE_1_6_1130")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_1130, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-6-1130-0.bin", REL::IDDB::Format::SSEv2, SKSE::RUNTIME_SSE_1_6_1130));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x14fbe0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}

TEST_CASE("Module/SupportsSkyrimAE_1_6_1170")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_1170, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-6-1170-0.bin", REL::IDDB::Format::SSEv2, SKSE::RUNTIME_SSE_1_6_1170));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x14fcd0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}

TEST_CASE("Module/SupportsSkyrimAE_1_6_1179_GOG")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_1179, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-6-1179-0.bin", REL::IDDB::Format::SSEv2, SKSE::RUNTIME_SSE_1_6_1179));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x14fb00);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}
#endif

#ifdef ENABLE_SKYRIM_VR
TEST_CASE("Module/SupportsSkyrimVR")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_VR_1_4_15, REL::Module::Runtime::VR, L"SkyrimVR.exe", 0x1000));
	}
	SECTION("Address Library format can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\version-1-4-15-0.csv", REL::IDDB::Format::VR, SKSE::RUNTIME_VR_1_4_15));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(11483) == 0x11fba0);
	}
	SECTION("REL::ID gets correct address and offset")
	{
		REL::ID id(11483);
		CHECK(id.offset() == 0x11fba0);
		CHECK(id.address() == 0x120ba0);
	}
	SECTION("REL::RelocationID gets correct address and offset")
	{
		static REL::RelocationID id(11483, 0);
		CHECK(id.offset() == 0x11fba0);
		CHECK(id.address() == 0x120ba0);

		id = REL::RelocationID(0, 0, 11483);
		CHECK(id.offset() == 0x11fba0);
		CHECK(id.address() == 0x120ba0);
	}
	SECTION("REL::VariantID gets correct address and offset")
	{
		REL::VariantID id(0, 0, 0x11fba0);
		CHECK(id.offset() == 0x11fba0);
		CHECK(id.address() == 0x120ba0);
	}
	SECTION("REL::VariantOffset gets the correct address and offset")
	{
		REL::VariantOffset offset(0, 0, 0x11fba0);
		CHECK(offset.offset() == 0x11fba0);
		CHECK(offset.address() == 0x120ba0);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}
#endif

TEST_CASE("IDDB/FailedIDLookup")
{
	REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_353, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	REQUIRE_THROWS(REL::IDDB::get().id2offset(0xFFFFFFFF));
}

#ifdef ENABLE_SKYRIM_AE
TEST_CASE("Module/SupportsSkyrimAE_1_7_99")
{
	SECTION("Runtime is mockable")
	{
		REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_7_99, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	}
	SECTION("Address Library format 5 can be loaded")
	{
		CHECK(REL::IDDB::inject(
			L"Data\\SKSE\\Plugins\\versionlib-1-7-99-0.bin", REL::IDDB::Format::SSEv5, SKSE::RUNTIME_SSE_1_7_99));
	}
	SECTION("Lookup by ID returns the correct offset")
	{
		CHECK(REL::IDDB::get().id2offset(1) == 0x1022);
		CHECK(REL::IDDB::get().id2offset(11483) == 0x155260);
	}
	SECTION("REL::ID gets correct address and offset")
	{
		REL::ID id(11483);
		CHECK(id.offset() == 0x155260);
		CHECK(id.address() == 0x156260);
	}
	SECTION("ID database and module can be reset")
	{
		REL::Module::reset();
	}
}

TEST_CASE("IDDB/BackwardCompatAutoDetect")
{
	// A single build must keep loading every format it has ever supported;
	// prove format 2 still auto-detects and loads without an explicit
	// expected-format assertion, the same way real (non-test) loads work.
	REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_1170, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	REQUIRE(REL::IDDB::inject(L"Data\\SKSE\\Plugins\\versionlib-1-6-1170-0.bin", SKSE::RUNTIME_SSE_1_6_1170));
	CHECK(REL::IDDB::get().id2offset(11483) == 0x14fcd0);
	REL::Module::reset();
}

TEST_CASE("IDDB/UnsupportedFormatFailsLoudly")
{
	REQUIRE(REL::Module::mock(SKSE::RUNTIME_SSE_1_6_1170, REL::Module::Runtime::AE, L"SkyrimSE.exe", 0x1000));
	CHECK_FALSE(REL::IDDB::inject(L"Data\\SKSE\\Plugins\\version-invalid-format.bin", SKSE::RUNTIME_SSE_1_6_1170));
	// An unrecognized format never populates a usable mapping, so every lookup still fails.
	CHECK_THROWS(REL::IDDB::get().id2offset(1));
	REL::Module::reset();
}
#endif

TEST_CASE("CodeVerification/VerifyCode", "[unit]")
{
	SECTION("Basic byte verification")
	{
		// Create test data
		std::uint8_t test_data[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00 };
		auto         address = reinterpret_cast<std::uintptr_t>(test_data);

		// Test exact match
		std::uint8_t expected[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00 };
		CHECK(REL::verify_code(address, expected, sizeof(expected)));

		// Test mismatch
		std::uint8_t wrong[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x01 };
		CHECK_FALSE(REL::verify_code(address, wrong, sizeof(wrong)));

		// Test partial match
		std::uint8_t partial[] = { 0x48, 0x8B, 0x05 };
		CHECK(REL::verify_code(address, partial, sizeof(partial)));
	}

	SECTION("Empty verification (always passes)")
	{
		std::uint8_t test_data[] = { 0x48, 0x8B, 0x05 };
		auto         address = reinterpret_cast<std::uintptr_t>(test_data);

		CHECK(REL::verify_code(address, nullptr, 0));
		CHECK(REL::verify_code(address, test_data, 0));
	}
}

TEST_CASE("CodeVerification/SafeWriteWithVerification", "[unit]")
{
	SECTION("Successful verification and write")
	{
		// Create test buffer
		std::uint8_t buffer[8] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00, 0x90 };
		auto         address = reinterpret_cast<std::uintptr_t>(buffer);

		// Verify current content
		std::uint8_t expected[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00 };

		// New content to write
		std::uint8_t new_data[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		// Should succeed
		CHECK(REL::safe_write(address, new_data, sizeof(new_data), expected, sizeof(expected)));

		// Verify the write happened
		CHECK(buffer[0] == 0x90);
		CHECK(buffer[6] == 0x90);
	}

	SECTION("Failed verification prevents write")
	{
		// Create test buffer
		std::uint8_t buffer[8] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00, 0x90 };
		auto         address = reinterpret_cast<std::uintptr_t>(buffer);

		// Wrong expected content
		std::uint8_t wrong_expected[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		// New content to write
		std::uint8_t new_data[] = { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };

		// Should fail verification
		CHECK_FALSE(REL::safe_write(address, new_data, sizeof(new_data), wrong_expected, sizeof(wrong_expected)));

		// Verify the write didn't happen
		CHECK(buffer[0] == 0x48);  // Original data unchanged
		CHECK(buffer[6] == 0x00);
	}
}

TEST_CASE("CodeVerification/SafeFillWithVerification", "[unit]")
{
	SECTION("Successful verification and fill")
	{
		// Create test buffer
		std::uint8_t buffer[8] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00, 0x90 };
		auto         address = reinterpret_cast<std::uintptr_t>(buffer);

		// Verify current content (partial)
		std::uint8_t expected[] = { 0x48, 0x8B, 0x05 };

		// Should succeed
		CHECK(REL::safe_fill(address, 0xCC, 7, expected, sizeof(expected)));

		// Verify the fill happened
		CHECK(buffer[0] == 0xCC);
		CHECK(buffer[6] == 0xCC);
		CHECK(buffer[7] == 0x90);  // Beyond fill range
	}

	SECTION("Failed verification prevents fill")
	{
		// Create test buffer
		std::uint8_t buffer[8] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00, 0x90 };
		auto         address = reinterpret_cast<std::uintptr_t>(buffer);

		// Wrong expected content
		std::uint8_t wrong_expected[] = { 0x90, 0x90, 0x90 };

		// Should fail verification
		CHECK_FALSE(REL::safe_fill(address, 0xCC, 7, wrong_expected, sizeof(wrong_expected)));

		// Verify the fill didn't happen
		CHECK(buffer[0] == 0x48);  // Original data unchanged
		CHECK(buffer[6] == 0x00);
	}
}

TEST_CASE("CodeVerification/MultiplePatches", "[unit]")
{
	SECTION("All patches succeed")
	{
		CHECK(REL::CodeVerification::verify_multiple_patches(true, true, true));
	}

	SECTION("Some patches fail")
	{
		CHECK_FALSE(REL::CodeVerification::verify_multiple_patches(true, false, true));
		CHECK_FALSE(REL::CodeVerification::verify_multiple_patches(false, false, false));
	}

	SECTION("Single patch")
	{
		CHECK(REL::CodeVerification::verify_multiple_patches(true));
		CHECK_FALSE(REL::CodeVerification::verify_multiple_patches(false));
	}
}
