#include "RE/B/BookMenu.h"

#include "RE/E/ExtraDataList.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	TESObjectBOOK* BookMenu::GetTargetForm()
	{
		REL::Relocation<TESObjectBOOK**> book{ RELOCATION_ID(519295, 405835) };
		return *book;
	}

	TESObjectREFR* BookMenu::GetTargetReference()
	{
		REL::Relocation<TESObjectREFRPtr*> refptr{ RELOCATION_ID(519300, 405840) };
		return refptr->get();
	}

	void BookMenu::OpenBookMenu(const BSString& a_description, const ExtraDataList* a_extraList, TESObjectREFR* a_ref, TESObjectBOOK* a_book, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos)
	{
		using func_t = decltype(&BookMenu::OpenBookMenu);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50122, 51053) };
		return func(a_description, a_extraList, a_ref, a_book, a_pos, a_rot, a_scale, a_useDefaultPos);
	}
}
