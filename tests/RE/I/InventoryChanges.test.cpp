#include "catch2/catch_all.hpp"

#include "RE/G/GetWornMaskVisitor.h"
#include "RE/I/InventoryChanges.h"

// Regression test for a link failure: IItemChangeVisitor declared a virtual
// destructor without defining it, so any consumer deriving its own visitor
// (the library's own supported usage pattern) failed to link at the
// destructor call.
namespace
{
	class TestVisitor : public RE::InventoryChanges::IItemChangeVisitor
	{
	public:
		RE::BSContainer::ForEachResult Visit(RE::InventoryEntryData*) override
		{
			return RE::BSContainer::ForEachResult::kContinue;
		}
	};
}

TEST_CASE("InventoryChanges/IItemChangeVisitor derived class links and destructs", "[.]")
{
	TestVisitor visitor;
	SUCCEED();
}

TEST_CASE("InventoryChanges/GetWornMaskVisitor links and destructs", "[.]")
{
	RE::GetWornMaskVisitor visitor{ nullptr };
	SUCCEED();
}
