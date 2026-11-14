#include "catch2/catch_all.hpp"

#include "RE/Skyrim.h"

TEST_CASE("FormType/std::to_string")
{
	SECTION("Sample types")
	{
		CHECK(std::to_string(RE::FormType::ActorCharacter) == "ACHR");
		CHECK(std::to_string(RE::FormType::Ammo) == "AMMO");
	}
	SECTION("Less than valid types")
	{
		CHECK(std::to_string(RE::FormType::None) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(std::to_string(RE::FormType::Max) == "NONE");
	}
}

#ifdef FMT_VERSION
TEST_CASE("FormType/fmt::format")
{
	SECTION("Sample types")
	{
		CHECK(fmt::format("{}", RE::FormType::ActorCharacter) == "ACHR");
		CHECK(fmt::format("{}", RE::FormType::Ammo) == "AMMO");
	}
	SECTION("Less than valid types")
	{
		CHECK(fmt::format("{}", RE::FormType::None) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(fmt::format("{}", RE::FormType::Max) == "NONE");
	}
}
#endif

TEST_CASE("FormType/std::format")
{
	SECTION("Sample types")
	{
		CHECK(std::format("{}", RE::FormType::ActorCharacter) == "ACHR");
		CHECK(std::format("{}", RE::FormType::Ammo) == "AMMO");
	}
	SECTION("Less than valid types")
	{
		CHECK(std::format("{}", RE::FormType::None) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(std::format("{}", RE::FormType::Max) == "NONE");
	}
}
