#include "RE/B/BookMenu.h"

#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTraits.h"
#include "RE/T/TESObjectBOOK.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	ExtraTextDisplayData* BookMenu::GetDisplayData()
	{
		static REL::Relocation<ExtraTextDisplayData**> displayData{ RELOCATION_ID(519293, 405833) };
		return *displayData;
	}

	ExtraDataList* BookMenu::GetExtraList()
	{
		static REL::Relocation<ExtraDataList**> extraList{ RELOCATION_ID(519294, 405834) };
		return *extraList;
	}

	TESObjectBOOK* BookMenu::GetTargetForm()
	{
		static REL::Relocation<TESObjectBOOK**> book{ RELOCATION_ID(519295, 405835) };
		return *book;
	}

	BSString& BookMenu::GetDescription()
	{
		static REL::Relocation<BSString*> description{ RELOCATION_ID(519297, 405837) };
		return *description;
	}

	TESObjectREFRPtr BookMenu::GetTargetReference()
	{
		static REL::Relocation<TESObjectREFRPtr*> refptr{ RELOCATION_ID(519300, 405840) };
		return *refptr;
	}

	NiPoint3& BookMenu::GetDisplayPosition()
	{
		static REL::Relocation<NiPoint3*> displayPosition{ RELOCATION_ID(519301, 405841) };
		return *displayPosition;
	}

	NiMatrix3& BookMenu::GetDisplayRotation()
	{
		static REL::Relocation<NiMatrix3*> displayRotation{ RELOCATION_ID(519304, 405844) };
		return *displayRotation;
	}

	float& BookMenu::GetDisplayScale()
	{
		static REL::Relocation<float*> displayScale{ RELOCATION_ID(509927, 382701) };
		return *displayScale;
	}

	void BookMenu::OpenMenuFromReference(TESObjectREFR* a_reference)
	{
		if (!a_reference || !a_reference->GetObjectReference()) {
			return;
		}

		TESObjectBOOK* book = a_reference->GetObjectReference()->As<RE::TESObjectBOOK>();

		if (!book) {
			return;
		}

		BSString desc;
		book->GetDescription(desc, nullptr);

		RE::NiMatrix3 rot{};
		rot.SetEulerAnglesXYZ(-0.05f, -0.05f, 1.50f);

		return OpenMenu_Impl(desc, &a_reference->extraList, a_reference, book, NiPoint3(), rot, 1.0f, true);
	}

	void BookMenu::OpenMenuFromReference(TESObjectREFR* a_reference, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos)
	{
		if (!a_reference || !a_reference->GetObjectReference()) {
			return;
		}

		TESObjectBOOK* book = a_reference->GetObjectReference()->As<RE::TESObjectBOOK>();

		if (!book) {
			return;
		}

		BSString desc;
		book->GetDescription(desc, nullptr);

		return OpenMenu_Impl(desc, &a_reference->extraList, a_reference, book, a_pos, a_rot, a_scale, a_useDefaultPos);
	}

	void BookMenu::OpenMenuFromBaseForm(TESObjectBOOK* a_book)
	{
		if (!a_book) {
			return;
		}

		BSString desc;
		a_book->GetDescription(desc, nullptr);

		RE::NiMatrix3 rot{};
		rot.SetEulerAnglesXYZ(-0.05f, -0.05f, 1.50f);

		return OpenMenu_Impl(desc, nullptr, nullptr, a_book, NiPoint3(), rot, 1.0f, true);
	}

	void BookMenu::OpenMenuFromBaseForm(TESObjectBOOK* a_book, const ExtraDataList* a_extraList, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos)
	{
		if (!a_book) {
			return;
		}

		BSString desc;
		a_book->GetDescription(desc, nullptr);

		return OpenMenu_Impl(desc, a_extraList, nullptr, a_book, a_pos, a_rot, a_scale, a_useDefaultPos);
	}

	void BookMenu::OpenMenu_Impl(const BSString& a_description, const ExtraDataList* a_extraList, TESObjectREFR* a_ref, TESObjectBOOK* a_book, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos)
	{
		using func_t = decltype(&BookMenu::OpenMenu_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50122, 51053) };
		return func(a_description, a_extraList, a_ref, a_book, a_pos, a_rot, a_scale, a_useDefaultPos);
	}
}
