#include "catch2/catch_all.hpp"

#include "REL/REL.h"
#include "SKSE/SKSE.h"

using namespace REL::literals;
using namespace SKSE;

namespace
{
	constinit PluginDeclaration WithAddressLibrary({ .Version = "1.2.3.4"_v,
		.Name = "Plugin",
		.RuntimeCompatibility = VersionIndependence::AddressLibrary });

	constinit PluginDeclaration ForSpecificRuntimes({ .Version = "1.2.3.4"_v,
		.Name = "Plugin",
		.RuntimeCompatibility = { "1.5.97.0"_v, "1.6.353.0"_v } });

	SKSEPluginInfo(.Version = "1.2.3.4"_v,
		.Name = "Plugin")
}

TEST_CASE("PluginDeclaration/ConstinitDeclaration")
{
	SECTION("With address library")
	{
		CHECK(std::string(WithAddressLibrary.GetName()) == "Plugin");
		CHECK(WithAddressLibrary.GetVersion() == "1.2.3.4"_v);
		CHECK(WithAddressLibrary.GetRuntimeCompatibility().IsVersionIndependent());
		CHECK(WithAddressLibrary.GetRuntimeCompatibility().UsesAddressLibrary());
		CHECK(!WithAddressLibrary.GetRuntimeCompatibility().UsesSignatureScanning());
	}
	SECTION("With specific runtime compatibility")
	{
		CHECK(std::string(ForSpecificRuntimes.GetName()) == "Plugin");
		CHECK(ForSpecificRuntimes.GetVersion() == "1.2.3.4"_v);
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().IsVersionIndependent());
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().UsesAddressLibrary());
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().UsesSignatureScanning());
		CHECK(static_cast<REL::Version>(ForSpecificRuntimes.GetRuntimeCompatibility().GetCompatibleRuntimeVersions()[0]) == "1.5.97.0"_v);
		CHECK(static_cast<REL::Version>(ForSpecificRuntimes.GetRuntimeCompatibility().GetCompatibleRuntimeVersions()[1]) == "1.6.353.0"_v);
	}
	SECTION("Declared with SKSEPluginInfo")
	{
		CHECK(std::string(SKSEPlugin_Version.GetName()) == "Plugin");
		CHECK(SKSEPlugin_Version.GetVersion() == "1.2.3.4"_v);
	}
}

TEST_CASE("PluginDeclaration/GetSingleton")
{
	CHECK(PluginDeclaration::GetSingleton() == &SKSEPlugin_Version);
}
