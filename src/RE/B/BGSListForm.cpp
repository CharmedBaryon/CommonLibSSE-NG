#include "RE/B/BGSListForm.h"

namespace RE
{
	void BGSListForm::AddForm(TESForm* a_form)
	{
		using func_t = decltype(&BGSListForm::AddForm);
		static REL::Relocation<func_t> func{ RELOCATION_ID(20470, 20913) };
		return func(this, a_form);
	}

	bool BGSListForm::ContainsOnlyType(FormType a_formType) const
	{
		bool result = true;
		ForEachForm([&](const TESForm* a_form) {
			if (a_form->GetFormType() != a_formType) {
				result = false;
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}

	bool BGSListForm::HasForm(const TESForm* a_form) const
	{
		if (!a_form) {
			return false;
		}

		auto ptrIt = std::find(forms.begin(), forms.end(), a_form);
		if (ptrIt != forms.end()) {
			return true;
		}

		if (!scriptAddedTempForms) {
			return false;
		}

		auto idIt = std::find(scriptAddedTempForms->begin(), scriptAddedTempForms->end(), a_form->formID);
		return idIt != scriptAddedTempForms->end();
	}

	bool BGSListForm::HasForm(FormID a_formID) const
	{
		auto form = TESForm::LookupByID(a_formID);
		return HasForm(form);
	}

	void BGSListForm::ForEachForm(std::function<BSContainer::ForEachResult(TESForm*)> a_callback) const
	{
		for (const auto& form : forms) {
			if (form && a_callback(form) == BSContainer::ForEachResult::kStop) {
				return;
			}
		}
		if (scriptAddedTempForms) {
			for (const auto& addedFormID : *scriptAddedTempForms) {
				const auto addedForm = TESForm::LookupByID(addedFormID);
				if (addedForm && a_callback(addedForm) == BSContainer::ForEachResult::kStop) {
					return;
				}
			}
		}
	}
}
