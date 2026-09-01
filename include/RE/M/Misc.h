#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;
	class IMessageBoxCallback;
	template <class T>
	class NiPointer;
	class Setting;
	class TESBoundObject;
	class TESObjectREFR;
	class TESForm;
	class InventoryEntryData;

	void          CreateMessage(const char* a_message, IMessageBoxCallback* a_callback, std::uint32_t a_arg3, std::uint32_t a_arg4, std::uint32_t a_arg5, const char* a_buttonText, const char* a_secondaryButtonText);
	void          CreateRefHandle(RefHandle& a_handleOut, TESObjectREFR* a_refTo);
	void          DebugNotification(const char* a_notification, const char* a_soundToPlay = 0, bool a_cancelIfAlreadyQueued = true);
	void          DebugMessageBox(const char* a_message);
	float         GetArmorFinalRating(InventoryEntryData* a_armorEntryData, float a_armorPerks, float a_skillMultiplier);
	std::uint32_t GetDurationOfApplicationRunTime();
	Setting*      GetINISetting(const char* a_name);
	float         GetSecondsSinceLastFrame();
	bool          LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<Actor>& a_refrOut);
	bool          LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<TESObjectREFR>& a_refrOut);
	void          PlaySound(const char* a_editorID);
	void          SendInventoryUpdateMessage(TESObjectREFR* a_refr, const TESBoundObject* a_item = nullptr);
	void          ShakeCamera(float a_strength, const NiPoint3& a_position, float a_duration);
}
