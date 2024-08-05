#include "RE/M/Misc.h"

#include "RE/B/BSTCreateFactoryManager.h"
#include "RE/B/BSTDerivedCreator.h"
#include "RE/G/GameSettingCollection.h"
#include "RE/I/INIPrefSettingCollection.h"
#include "RE/I/INISettingCollection.h"
#include "RE/I/InterfaceStrings.h"
#include "RE/M/MessageBoxData.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/Setting.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	bool LookupReferenceByHandle_ActorImpl(const RefHandle& a_handle, NiPointer<Actor>& a_refrOut)
	{
		using func_t = decltype(&LookupReferenceByHandle_ActorImpl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12204, 12332) };
		return func(a_handle, a_refrOut);
	}

	bool LookupReferenceByHandle_RefrImpl(const RefHandle& a_handle, NiPointer<TESObjectREFR>& a_refrOut)
	{
		using func_t = decltype(&LookupReferenceByHandle_RefrImpl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12204, 12332) };
		return func(a_handle, a_refrOut);
	}

	void CreateMessage(const char* a_message, IMessageBoxCallback* a_callback, std::uint32_t a_arg3, std::uint32_t a_arg4, std::uint32_t a_arg5, const char* a_buttonText, const char* a_secondaryButtonText)
	{
		using func_t = decltype(&CreateMessage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51420, 52269) };
		return func(a_message, a_callback, a_arg3, a_arg4, a_arg5, a_buttonText, a_secondaryButtonText);
	}

	void CreateRefHandle(RefHandle& a_handleOut, TESObjectREFR* a_refTo)
	{
		using func_t = decltype(&CreateRefHandle);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12193, 12326) };
		return func(a_handleOut, a_refTo);
	}

	void DebugNotification(const char* a_notification, const char* a_soundToPlay, bool a_cancelIfAlreadyQueued)
	{
		using func_t = decltype(&DebugNotification);
		static REL::Relocation<func_t> func{ RELOCATION_ID(52050, 52933) };
		return func(a_notification, a_soundToPlay, a_cancelIfAlreadyQueued);
	}

	void DebugMessageBox(const char* a_message)
	{
		CreateMessage(a_message, nullptr, 0, 4, 10, GameSettingCollection::GetSingleton()->GetSetting("sOk")->GetString(), nullptr);
	}

	float GetArmorFinalRating(RE::InventoryEntryData* a_armorEntryData, float a_armorPerks, float a_skillMultiplier)
	{
		using func_t = decltype(&GetArmorFinalRating);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15779, 16017) };
		return func(a_armorEntryData, a_armorPerks, a_skillMultiplier);
	}

	std::uint32_t GetDurationOfApplicationRunTime()
	{
		REL::Relocation<std::uint32_t*> runtime{ RELOCATION_ID(523662, 410201) };
		return *runtime;
	}

	Setting* GetINISetting(const char* a_name)
	{
		Setting* setting = nullptr;

		auto iniPrefs = INIPrefSettingCollection::GetSingleton();
		setting = iniPrefs ? iniPrefs->GetSetting(a_name) : nullptr;
		if (!setting) {
			auto ini = INISettingCollection::GetSingleton();
			setting = ini ? ini->GetSetting(a_name) : nullptr;
		}
		return setting;
	}

	float GetSecondsSinceLastFrame()
	{
		REL::Relocation<float*> seconds{ RELOCATION_ID(523660, 410199) };
		return *seconds;
	}

	bool LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<Actor>& a_refrOut)
	{
		return LookupReferenceByHandle_ActorImpl(a_handle, a_refrOut);
	}

	bool LookupReferenceByHandle(const RefHandle& a_handle, NiPointer<TESObjectREFR>& a_refrOut)
	{
		return LookupReferenceByHandle_RefrImpl(a_handle, a_refrOut);
	}

	void PlaySound(const char* a_editorID)
	{
		using func_t = decltype(&PlaySound);
		static REL::Relocation<func_t> func{ RELOCATION_ID(52054, 52939) };
		return func(a_editorID);
	}

	void ShakeCamera(float a_strength, const NiPoint3& a_position, float a_duration)
	{
		using func_t = decltype(&ShakeCamera);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32275, 33012) };
		return func(a_strength, a_position, a_duration);
	}
}
