#include "RE/T/TESValueForm.h"

#include "RE/A/AlchemyItem.h"
#include "RE/M/MagicItem.h"
#include "RE/RTTI.h"
#include "RE/T/TESForm.h"

namespace RE
{
	std::int32_t TESValueForm::GetFormValue(const TESForm* a_form)
	{
		if (const auto valueForm = skyrim_cast<const TESValueForm*>(a_form)) {
			return valueForm->value;
		}

		if (const auto magicItem = skyrim_cast<const MagicItem*>(a_form)) {
			return static_cast<std::int32_t>(magicItem->CalculateMagickaCost(nullptr));
		}

		return -1;
	}
}
