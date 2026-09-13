#include "RE/C/CombatAnimation.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, ANIM a_anim)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, ANIM);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43235, 44436) };
		auto                           combatAnimation = func(this, a_actor, a_anim);
		stl::emplace_vtable<CombatAnimation>(combatAnimation);
		return combatAnimation;
	}

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, TESObjectREFR*, ANIM);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43236, 44437) };
		return func(this, a_actor, a_target, a_anim);
	}

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, BGSAction* a_action)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, BGSAction*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43237, 44438) };
		return func(this, a_actor, a_action);
	}

	CombatAnimation* CombatAnimation::Create(Actor* a_actor, ANIM a_anim)
	{
		auto combatAnimation = malloc<CombatAnimation>();
		std::memset(reinterpret_cast<void*>(combatAnimation), 0, sizeof(CombatAnimation));
		if (combatAnimation) {
			combatAnimation->Ctor(a_actor, a_anim);
		}
		return combatAnimation;
	}

	CombatAnimation* CombatAnimation::Create(Actor* a_actor, BGSAction* a_action)
	{
		auto combatAnimation = malloc<CombatAnimation>();
		std::memset(reinterpret_cast<void*>(combatAnimation), 0, sizeof(CombatAnimation));
		if (combatAnimation) {
			combatAnimation->Ctor(a_actor, a_action);
		}
		return combatAnimation;
	}

	bool CombatAnimation::Execute(Actor* a_actor, ANIM a_anim)
	{
		using func_t = bool(Actor*, ANIM);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43245, 44446) };
		return func(a_actor, a_anim);
	}

	bool CombatAnimation::Execute(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim)
	{
		using func_t = bool(Actor*, TESObjectREFR*, ANIM);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43246, 44447) };
		return func(a_actor, a_target, a_anim);
	}

	bool CombatAnimation::Check()
	{
		using func_t = decltype(&CombatAnimation::Check);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43238, 44439) };
		return func(this);
	}

	bool CombatAnimation::Execute()
	{
		using func_t = bool(CombatAnimation*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43239, 44440) };
		return func(this);
	}

	bool CombatAnimation::GetEventData(const BSFixedString& a_eventName, float& a_eventTime)
	{
		using func_t = bool(CombatAnimation*, const BSFixedString&, float&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43240, 44441) };
		return func(this, a_eventName, a_eventTime);
	}

	bool CombatAnimation::GetEventData(const BSFixedString& a_eventName, float& a_eventTime, NiPoint3& a_translation)
	{
		using func_t = bool(CombatAnimation*, const BSFixedString&, float&, NiPoint3&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43241, 44442) };
		return func(this, a_eventName, a_eventTime, a_translation);
	}

	float CombatAnimation::GetEventTime(const BSFixedString& a_eventName)
	{
		using func_t = decltype(&CombatAnimation::GetEventTime);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43243, 44444) };
		return func(this, a_eventName);
	}

	float CombatAnimation::GetLength()
	{
		using func_t = decltype(&CombatAnimation::GetLength);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43244, 44445) };
		return func(this);
	}

	bool CombatAnimation::GetTranslation(NiPoint3& a_translation)
	{
		using func_t = decltype(&CombatAnimation::GetTranslation);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43242, 44443) };
		return func(this, a_translation);
	}

	bool CombatAnimation::LoadClipData()
	{
		using func_t = decltype(&CombatAnimation::LoadClipData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43247, 44448) };
		return func(this);
	}
}
