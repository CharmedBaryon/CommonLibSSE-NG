#include "RE/B/BGSOpenCloseForm.h"

namespace RE
{
	auto BGSOpenCloseForm::GetOpenState(const TESObjectREFR* a_ref)
		-> OPEN_STATE
	{
		using func_t = decltype(&BGSOpenCloseForm::GetOpenState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14180, 14288) };
		return func(a_ref);
	}

	void BGSOpenCloseForm::SetOpenState(TESObjectREFR* a_ref, bool a_open, bool a_snap)
	{
		using func_t = decltype(&BGSOpenCloseForm::SetOpenState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14179, 14287) };
		return func(a_ref, a_open, a_snap);
	}
}
