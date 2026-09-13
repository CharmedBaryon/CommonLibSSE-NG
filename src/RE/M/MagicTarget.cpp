#include "RE/M/MagicTarget.h"

#include "RE/A/ActiveEffect.h"
#include "RE/A/Actor.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTList.h"
#include "RE/E/EffectSetting.h"

namespace RE
{
	bool MagicTarget::DispelEffect(MagicItem* a_spell, BSPointerHandle<Actor>& a_caster, ActiveEffect* a_effect)
	{
		using func_t = decltype(&MagicTarget::DispelEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33721, 34505) };
		return func(this, a_spell, a_caster, a_effect);
	}

#if defined(ENABLE_SKYRIM_VR)
	TESObjectREFR* MagicTarget::GetTargetStatsObject()
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::GetTargetStatsObject)>(0x2, 0x2, this);
	}

	[[nodiscard]] bool MagicTarget::MagicTargetIsActor() const
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::MagicTargetIsActor)>(0x3, 0x3, this);
	}

	[[nodiscard]] bool MagicTarget::IsInvulnerable()
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::IsInvulnerable)>(0x4, 0x4, this);
	}

	void MagicTarget::InvalidateCommandedActorEffect(ActiveEffect* a_effect)
	{
		REL::RelocateVirtual<decltype(&MagicTarget::InvalidateCommandedActorEffect)>(0x5, 0x5, this, a_effect);
	}

	bool MagicTarget::CanAddActiveEffect()
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::CanAddActiveEffect)>(0x6, 0x6, this);
	}

	BSSimpleList<ActiveEffect*>* MagicTarget::GetActiveEffectList()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			// VR: Build a thread-local snapshot using VisitActiveEffects
			static thread_local std::vector<ActiveEffect*>  effectsVec{};
			static thread_local BSSimpleList<ActiveEffect*> activeEffects{};

			effectsVec.clear();
			activeEffects.clear();

			VisitActiveEffects([&](ActiveEffect* ae) -> BSContainer::ForEachResult {
				if (ae) {
					effectsVec.push_back(ae);
				}
				return BSContainer::ForEachResult::kContinue;
			});

			for (auto it = effectsVec.rbegin(); it != effectsVec.rend(); ++it) {
				activeEffects.push_front(*it);
			}

			return &activeEffects;
		} else {
			// SE/AE: Call the pure virtual function via vtable
			return REL::RelocateVirtual<decltype(&MagicTarget::GetActiveEffectList)>(0x07, 0x07, this);
		}
	}

	void MagicTarget::EffectAdded(ActiveEffect* a_effect)
	{
		REL::RelocateVirtual<decltype(&MagicTarget::EffectAdded)>(0x8, 0x8, this, a_effect);
	}

	void MagicTarget::EffectRemoved(ActiveEffect* a_effect)
	{
		REL::RelocateVirtual<decltype(&MagicTarget::EffectRemoved)>(0x9, 0x9, this, a_effect);
	}

	float MagicTarget::CheckResistance(MagicItem* a_magicItem, Effect* a_effect, TESBoundObject* a_object)
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::CheckResistance)>(0xa, 0xa, this, a_magicItem, a_effect, a_object);
	}

	bool MagicTarget::CheckAbsorb(Actor* a_actor, MagicItem* a_magicItem, const Effect* a_effect)
	{
		return REL::RelocateVirtual<decltype(&MagicTarget::CheckAbsorb)>(0xb, 0xb, this, a_actor, a_magicItem, a_effect);
	}

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

	Actor* MagicTarget::GetTargetAsActor()
	{
		if (MagicTargetIsActor()) {
			return reinterpret_cast<Actor*>(this);
		}

		return nullptr;
	}

	bool MagicTarget::HasEffectWithArchetype(Archetype a_type)
	{
		auto effects = GetActiveEffectList();
		if (!effects) {
			return false;
		}

		EffectSetting* setting = nullptr;
		for (auto& effect : *effects) {
			setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				return true;
			}
		}
		return false;
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
