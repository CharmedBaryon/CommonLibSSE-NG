#include "RE/S/ScriptEventSourceHolder.h"

#include "RE/T/TESActivateEvent.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/T/TESPerkEntryRunEvent.h"
#include "RE/T/TESSpellCastEvent.h"

namespace RE
{
	ScriptEventSourceHolder* ScriptEventSourceHolder::GetSingleton()
	{
		using func_t = decltype(&ScriptEventSourceHolder::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14108, 14298) };
		return func();
	}

	void ScriptEventSourceHolder::SendActivateEvent(const NiPointer<TESObjectREFR>& a_objectActivated, const NiPointer<TESObjectREFR>& a_actionRef)
	{
		const TESActivateEvent e{
			a_objectActivated,
			a_actionRef
		};

		this->SendEvent(&e);
	}

	void ScriptEventSourceHolder::SendOpenCloseEvent(const NiPointer<TESObjectREFR>& a_ref, const NiPointer<TESObjectREFR>& a_activeRef, bool a_isOpened)
	{
		using func_t = decltype(&ScriptEventSourceHolder::SendOpenCloseEvent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14190, 14299) };
		return func(this, a_ref, a_activeRef, a_isOpened);
	}

	void ScriptEventSourceHolder::SendPerkEntryRunEvent(FormID a_perkFormID, std::uint16_t a_perkEntryID, const NiPointer<TESObjectREFR>& a_targetRef, const NiPointer<TESObjectREFR>& a_perkOwner)
	{
		const TESPerkEntryRunEvent e{
			a_targetRef,
			a_perkOwner,
			a_perkFormID,
			a_perkEntryID
		};

		this->SendEvent(&e);
	}

	void ScriptEventSourceHolder::SendSpellCastEvent(const NiPointer<TESObjectREFR>& a_object, FormID a_formID)
	{
		const TESSpellCastEvent e{
			a_object,
			a_formID
		};

		this->SendEvent(&e);
	}
}
