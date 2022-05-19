#include "catch.hpp"

#include "REL/Relocation.h"
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
		CHECK(WithAddressLibrary.GetName() == "Plugin");
		CHECK(WithAddressLibrary.GetVersion() == "1.2.3.4"_v);
		CHECK(WithAddressLibrary.GetRuntimeCompatibility().IsVersionIndependent());
		CHECK(WithAddressLibrary.GetRuntimeCompatibility().UsesAddressLibrary());
		CHECK(!WithAddressLibrary.GetRuntimeCompatibility().UsesSignatureScanning());
	}
	SECTION("With specific runtime compatibility")
	{
		CHECK(ForSpecificRuntimes.GetName() == "Plugin");
		CHECK(ForSpecificRuntimes.GetVersion() == "1.2.3.4"_v);
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().IsVersionIndependent());
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().UsesAddressLibrary());
		CHECK(!ForSpecificRuntimes.GetRuntimeCompatibility().UsesSignatureScanning());
		CHECK(static_cast<REL::Version>(ForSpecificRuntimes.GetRuntimeCompatibility().GetCompatibleRuntimeVersions()[0]) == "1.5.97.0"_v);
		CHECK(static_cast<REL::Version>(ForSpecificRuntimes.GetRuntimeCompatibility().GetCompatibleRuntimeVersions()[1]) == "1.6.353.0"_v);
	}
	SECTION("Declared with SKSEPluginInfo")
	{
		CHECK(SKSEPlugin_Version.GetName() == "Plugin");
		CHECK(SKSEPlugin_Version.GetVersion() == "1.2.3.4"_v);
	}
}
