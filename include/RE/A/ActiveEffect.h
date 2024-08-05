#pragma once

#include "RE/A/ActiveEffectReferenceEffectController.h"
#include "RE/B/BSContainer.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTList.h"
#include "RE/M/MagicSystem.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class Actor;
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class EffectSetting;
	class MagicItem;
	class MagicTarget;
	class NiNode;
	class NiPoint3;
	class ReferenceEffect;
	class TESBoundObject;
	struct Effect;

	class ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActiveEffect;
		inline static constexpr auto VTABLE = VTABLE_ActiveEffect;
		inline static constexpr auto VMTYPEID = static_cast<VMTypeID>(142);

		class ForEachHitEffectVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_ActiveEffect__ForEachHitEffectVisitor;
			inline static constexpr auto VTABLE = VTABLE_ActiveEffect__ForEachHitEffectVisitor;

			virtual ~ForEachHitEffectVisitor();  // 00

			// add
			virtual BSContainer::ForEachResult operator()(ReferenceEffect* a_hitEffect) = 0;  // 01
		};

		enum class Flag
		{
			kHasConditions = 1 << 7,
			kEnchanting = 1 << 8,
			kRecovers = 1 << 9,
			kDual = 1 << 12,
			kInactive = 1 << 15,
			kDispelled = 1 << 18
		};

		enum class ConditionStatus
		{
			kNA = static_cast<std::underlying_type_t<ConditionStatus>>(-1),
			kFalse = 0,
			kTrue = 1,
		};

		// add
		virtual void           AdjustForPerks(Actor* a_caster, MagicTarget* a_target);    // 00
		virtual void           OnAdd(MagicTarget* a_target);                              // 01
		virtual void           OnRemove();                                                // 02 - { return; }
		virtual TESObjectREFR* GetVisualsTarget();                                        // 03 - { return target ? target->GetTargetStatsObject() : 0; }
		virtual void           Update(float a_delta);                                     // 04 - { return; }
		virtual void           EvaluateConditions(float a_delta, bool a_forceUpdate);     // 05
		virtual bool           IsCausingHealthDamage();                                   // 06 - { return 0; }
		virtual void           SetLocation(const NiPoint3& a_location);                   // 07 - { return; }
		virtual void           SaveGame(BGSSaveFormBuffer* a_buf);                        // 08
		virtual void           LoadGame(BGSLoadFormBuffer* a_buf);                        // 09
		virtual void           FinishLoadGame(BGSLoadFormBuffer* a_buf);                  // 0A
		virtual void           Revert(BGSLoadFormBuffer* a_buf);                          // 0B - { castingSource = 4; }
		virtual std::int32_t   Compare(ActiveEffect* a_otherEffect);                      // 0C
		virtual void           HandleEvent(const BSFixedString& a_eventName);             // 0D - { return; }
		virtual void           SwitchAttachedRoot(NiNode* a_root, NiNode* a_attachRoot);  // 0E - { return; }
		virtual void           HandleQueuedStart();                                       // 0F - { return; }
		virtual bool           ShouldDispelOnDeath() const;                               // 10 - { return effect->baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoDeathDispel); }
		virtual bool           GetAllowMultipleCastingSourceStacking();                   // 11 - { return 0; }
		virtual void           ClearTargetImpl();                                         // 12 - { return; }

		virtual ~ActiveEffect();  // 13

		virtual void  Start();                                                   // 14 - { return; }
		virtual void  Finish();                                                  // 15 - { return; }
		virtual bool  CanFinish();                                               // 16
		virtual bool  CheckCustomSkillUseConditions() const;                     // 17 - { return 1; }
		virtual float GetCustomSkillUseMagnitudeMultiplier(float a_mult) const;  // 18 - { return 1.0; }

		void                               Dispel(bool a_force);
		[[nodiscard]] EffectSetting*       GetBaseObject() noexcept;
		[[nodiscard]] const EffectSetting* GetBaseObject() const noexcept;
		NiPointer<Actor>                   GetCasterActor() const;
		float                              GetMagnitude() const;
		Actor*                             GetTargetActor();
		const Actor*                       GetTargetActor() const;

		ActiveEffectReferenceEffectController            hitEffectController;  // 08
		BSSoundHandle                                    persistentSound;      // 28
		ActorHandle                                      caster;               // 34
		NiPointer<NiNode>                                sourceNode;           // 38
		MagicItem*                                       spell;                // 40
		Effect*                                          effect;               // 48
		MagicTarget*                                     target;               // 50
		TESBoundObject*                                  source;               // 58
		BSSimpleList<ReferenceEffect*>*                  hitEffects;           // 60
		MagicItem*                                       displacementSpell;    // 68
		float                                            elapsedSeconds;       // 70
		float                                            duration;             // 74
		float                                            magnitude;            // 78
		stl::enumeration<Flag, std::uint32_t>            flags;                // 7C
		stl::enumeration<ConditionStatus, std::uint32_t> conditionStatus;      // 80
		std::uint16_t                                    usUniqueID;           // 84
		std::uint16_t                                    pad86;                // 86
		MagicSystem::CastingSource                       castingSource;        // 88
		std::uint32_t                                    pad8C;                // 8C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActiveEffect) == 0x90);
}
