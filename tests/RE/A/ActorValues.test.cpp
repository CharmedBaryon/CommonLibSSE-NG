#include "catch2/catch_all.hpp"

#include "RE/A/ActorValueList.h"

TEST_CASE("ActorValue/std::to_string", "[.][e2e]")
{
	REQUIRE(REL::Module::inject());
	SECTION("Sample types")
	{
		CHECK(std::to_string(RE::ActorValue::kAlchemyModifier) == "AlchemyModifier");
		CHECK(std::to_string(RE::ActorValue::kHeavyArmor) == "HeavyArmor");
	}
	SECTION("Less than valid types")
	{
		CHECK(std::to_string(RE::ActorValue::kNone) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(std::to_string(RE::ActorValue::kTotal) == "NONE");
	}
	REL::Module::reset();
}

#ifdef FMT_VERSION
TEST_CASE("ActorValue/fmt::format", "[.][e2e]")
{
	REQUIRE(REL::Module::inject());
	SECTION("Sample types")
	{
		CHECK(fmt::format("{}", RE::ActorValue::kAlchemyModifier) == "AlchemyModifier");
		CHECK(fmt::format("{}", RE::ActorValue::kHeavyArmor) == "HeavyArmor");
	}
	SECTION("Less than valid types")
	{
		CHECK(fmt::format("{}", RE::ActorValue::kNone) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(fmt::format("{}", RE::ActorValue::kTotal) == "NONE");
	}
	REL::Module::reset();
}
#endif

TEST_CASE("ActorValue/std::format", "[.][e2e]")
{
	REQUIRE(REL::Module::inject());
	SECTION("Sample types")
	{
		CHECK(std::format("{}", std::to_string(RE::ActorValue::kAlchemyModifier)) == "AlchemyModifier");
		CHECK(std::format("{}", std::to_string(RE::ActorValue::kHeavyArmor)) == "HeavyArmor");
	}
	SECTION("Less than valid types")
	{
		CHECK(std::format("{}", std::to_string(RE::ActorValue::kNone)) == "NONE");
	}
	SECTION("Greater than valid types")
	{
		CHECK(std::format("{}", std::to_string(RE::ActorValue::kTotal)) == "NONE");
	}
	REL::Module::reset();
}
