#include "RE/T/TESRace.h"

namespace RE
{
	bool TESRace::AllowsPCDialogue() const
	{
		return data.flags.all(RACE_DATA::Flag::kAllowPCDialogue);
	}

	bool TESRace::AllowsPickpocket() const
	{
		return data.flags.all(RACE_DATA::Flag::kAllowPickpocket);
	}

	BGSHeadPart* TESRace::GetHeadPartByType(HeadPartType a_type, SEX a_sex) const
	{
		auto faceData = faceRelatedData[a_sex];
		if (faceData && faceData->headParts) {
			for (auto& headpart : *faceData->headParts) {
				if (headpart && headpart->type == a_type) {
					return headpart;
				}
			}
		}

		return nullptr;
	}

	bool TESRace::IsChildRace() const
	{
		return data.flags.all(RACE_DATA::Flag::kChild);
	}
}
