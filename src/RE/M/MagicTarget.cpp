#include "RE/M/MagicTarget.h"

#include "RE/A/ActiveEffect.h"
#include "RE/A/Actor.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTList.h"
#include "RE/E/EffectSetting.h"
#include "RE/F/FormTraits.h"

namespace RE
{
	bool MagicTarget::DispelEffect(MagicItem* a_spell, BSPointerHandle<Actor>& a_caster, ActiveEffect* a_effect)
	{
		using func_t = decltype(&MagicTarget::DispelEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33721, 34505) };
		return func(this, a_spell, a_caster, a_effect);
	}

#if defined(SKYRIM_CROSS_VR)
	BSSimpleList<ActiveEffect*>* MagicTarget::GetActiveEffectList()
	{
		// VR's list is a BSLocklessSimpleList: there is no BSSimpleList to hand out
		if (REL::Module::IsVR()) {
			return nullptr;
		}
		return static_cast<BSSimpleList<ActiveEffect*>*>(GetActiveEffectListNative());
	}
#endif

#if defined(ENABLE_SKYRIM_VR)
	BSLocklessSimpleList<ActiveEffect*>* MagicTarget::GetVRActiveEffectList()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return static_cast<BSLocklessSimpleList<ActiveEffect*>*>(GetActiveEffectListNative());
		} else {
			return nullptr;
		}
	}
#endif

#if defined(ENABLE_SKYRIM_VR)
	void MagicTarget::DispelEffectsWithArchetype(Archetype a_type, bool a_force)
	{
		std::vector<RE::ActiveEffect*> queued;
		VisitActiveEffects([&](ActiveEffect* effect) {
			const auto setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				queued.push_back(effect);
			}
			return BSContainer::ForEachResult::kContinue;
		});

		for (const auto& effect : queued) {
			effect->Dispel(a_force);
		}
	}
#endif

	// this is a base subobject at a runtime-dependent offset in Actor; a cast cannot
	// recover the actor, the object's own override does.
	Actor* MagicTarget::GetTargetAsActor()
	{
		const auto ref = GetTargetStatsObject();
		return ref ? ref->As<Actor>() : nullptr;
	}

	bool MagicTarget::HasEffectWithArchetype(Archetype a_type)
	{
		bool found = false;
		VisitActiveEffects([&](ActiveEffect* a_effect) {
			const auto setting = a_effect ? a_effect->GetBaseObject() : nullptr;
			found = setting && setting->HasArchetype(a_type);
			return found ? BSContainer::ForEachResult::kStop : BSContainer::ForEachResult::kContinue;
		});
		return found;
	}

	bool MagicTarget::HasMagicEffect(EffectSetting* a_effect)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33733, 34517) };
		return func(this, a_effect);
	}

	bool MagicTarget::HasMagicEffectWithKeyword(BGSKeyword* a_keyword, MagicItem** a_spellOut)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffectWithKeyword);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33734, 34518) };
		return func(this, a_keyword, a_spellOut);
	}

	void MagicTarget::VisitEffects(ForEachActiveEffectVisitor& visitor)
	{
		using func_t = decltype(&MagicTarget::VisitEffects);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33756, 34540) };
		return func(this, visitor);
	}
}
