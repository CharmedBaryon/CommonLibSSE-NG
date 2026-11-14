#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	enum class ActorValue;
	class Actor;
	class IMessageBoxCallback;
	template <class T>
	class NiPointer;
	class Setting;
	class TESObjectREFR;
	class TESForm;
	class InventoryEntryData;

	void          CreateRefHandle(RefHandle& a_handleOut, TESObjectREFR* a_refTo);
	void          DebugMessageBox(const char* a_message);
	float         GetArmorFinalRating(InventoryEntryData* a_armorEntryData, float a_armorPerks, float a_skillMultiplier);
	std::uint32_t GetDurationOfApplicationRunTime();
	Setting*      GetINISetting(const char* a_name);
	float         GetSecondsSinceLastFrame();
	bool          LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<Actor>& a_refrOut);
	bool          LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<TESObjectREFR>& a_refrOut);
	void          PlaySound(const char* a_editorID);
	bool          RandomBoolChance(float chance);
	void          ShakeCamera(float a_strength, const NiPoint3& a_position, float a_duration);
	void          FlashHUDMeter(ActorValue a_av);
}
