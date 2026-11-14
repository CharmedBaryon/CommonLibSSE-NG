#include "RE/L/LockpickingMenu.h"

#include "RE/T/TESObjectREFR.h"

namespace RE
{
	TESObjectREFRPtr LockpickingMenu::GetTargetReference()
	{
		static REL::Relocation<TESObjectREFRPtr*> refptr{ RELOCATION_ID(519716, 406271) };
		return *refptr;
	}

	std::int32_t LockpickingMenu::GetCurrentLockDifficulty()
	{
		static REL::Relocation<std::int32_t*> difficulty{ RELOCATION_ID(510072, 382910) };
		return *difficulty;
	}

	void LockpickingMenu::OpenMenu(RE::TESObjectREFR* a_target)
	{
		using func_t = decltype(&LockpickingMenu::OpenMenu);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51080, 51959) };
		return func(a_target);
	}
}
