#include "RE/M/Misc.h"

#include "RE/A/ActorValues.h"
#include "RE/G/GameSettingCollection.h"
#include "RE/I/INIPrefSettingCollection.h"
#include "RE/I/INISettingCollection.h"
#include "RE/M/MessageBoxMenu.h"
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

	void CreateRefHandle(RefHandle& a_handleOut, TESObjectREFR* a_refTo)
	{
		using func_t = decltype(&CreateRefHandle);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12193, 12326) };
		return func(a_handleOut, a_refTo);
	}

	void DebugMessageBox(const char* a_message)
	{
		MessageBoxMenu::Create(a_message, nullptr, 0, 4, 10, GameSettingCollection::GetSingleton()->GetSetting("sOk")->GetString());
	}

	float GetArmorFinalRating(RE::InventoryEntryData* a_armorEntryData, float a_armorPerks, float a_skillMultiplier)
	{
		using func_t = decltype(&GetArmorFinalRating);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15779, 16017) };
		return func(a_armorEntryData, a_armorPerks, a_skillMultiplier);
	}

	std::uint32_t GetDurationOfApplicationRunTime()
	{
		static REL::Relocation<std::uint32_t*> runtime{ RELOCATION_ID(523662, 410201) };
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
		static REL::Relocation<float*> seconds{ RELOCATION_ID(523660, 410199) };
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

	bool RandomBoolChance(float chance)
	{
		using func_t = decltype(&RandomBoolChance);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26009, 0) };
		return func(chance);
	}

	void ShakeCamera(float a_strength, const NiPoint3& a_position, float a_duration)
	{
		using func_t = decltype(&ShakeCamera);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32275, 33012) };
		return func(a_strength, a_position, a_duration);
	}

	void FlashHUDMeter(ActorValue a_actorValue)
	{
		using func_t = decltype(&FlashHUDMeter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51907, 52845) };
		return func(a_actorValue);
	}
}
