#include "RE/B/BarterMenu.h"

namespace RE
{
	RefHandle BarterMenu::GetTargetRefHandle()
	{
		static REL::Relocation<RefHandle*> handle{ RELOCATION_ID(519283, 405823) };
		return *handle;
	}

	void BarterMenu::OpenMenu(Actor* a_targetActor)
	{
		using func_t = decltype(&BarterMenu::OpenMenu);
		static REL::Relocation<func_t> func{ RELOCATION_ID(0, 50955) };
		return func(a_targetActor);
	}

	bool BarterMenu::IsViewingVendorItems() noexcept
	{
		RE::GFxValue result;
		auto         runtimeData = GetRuntimeData();
		return (runtimeData.root.Invoke("isViewingVendorItems", &result) && result.GetBool());
	}
}
