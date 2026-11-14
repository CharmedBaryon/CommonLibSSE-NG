#include "catch2/catch_all.hpp"

#include "RE/M/MenuEventHandler.h"
#include "RE/M/MenuEventHandlerEx.h"

namespace
{
	class TestHandler : public RE::MenuEventHandlerEx
	{
	public:
		bool CanProcess(RE::InputEvent*) override { return true; }
		bool ProcessButton(RE::ButtonEvent*) override { return true; }
	};
}

TEST_CASE("MenuEventHandlerEx derived class links and destructs", "[.]")
{
	TestHandler           h;
	RE::MenuEventHandler* handler = h.Handler();
	REQUIRE(handler != nullptr);
	CHECK(handler->CanProcess(nullptr));
	CHECK(handler->ProcessButton(nullptr));
}
