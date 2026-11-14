#include "RE/B/BGSRefAlias.h"

#include "RE/A/Actor.h"
#include "RE/F/FormTraits.h"
#include "RE/T/TESQuest.h"

namespace RE
{
	TESObjectREFR* BGSRefAlias::GetReference() const
	{
		TESObjectREFR* ref = nullptr;
		const auto     owner = owningQuest;
		if (owner) {
			auto       handle = owner->GetAliasedRef(aliasID);
			const auto refPtr = handle.get();
			ref = refPtr.get();
		}
		return ref;
	}

	Actor* BGSRefAlias::GetActorReference() const
	{
		const auto ref = GetReference();
		return ref ? ref->As<Actor>() : nullptr;
	}

	void BGSRefAlias::ForceRefTo(TESObjectREFR* a_ref)
	{
		if (!a_ref) {
			return;
		}

		const auto owner = owningQuest;
		if (owner) {
			owner->ForceRefIntoAlias(aliasID, a_ref);
		}
	}
}
