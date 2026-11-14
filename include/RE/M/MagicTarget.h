#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSLocklessSimpleList.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/EffectArchetypes.h"
#include "RE/M/MagicSystem.h"
#include "RE/N/NiPoint3.h"
#ifdef ENABLE_SKYRIM_VR
#	include "RE/B/BSContainer.h"
#endif

namespace RE
{
	namespace ActiveEffectFactory
	{
		struct CheckTargetArgs;
	}

	class Actor;
	class ActiveEffect;
	class BGSKeyword;
	class EffectItem;
	class EffectSetting;
	class MagicItem;
	class TESBoundObject;
	class TESObjectREFR;
	struct Effect;

	struct Effect;

	class MagicTarget
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicTarget;
		inline static constexpr auto VTABLE = VTABLE_MagicTarget;

		using Archetype = EffectArchetypes::ArchetypeID;

		class ForEachActiveEffectVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_MagicTarget__ForEachActiveEffectVisitor;
			inline static constexpr auto VTABLE = VTABLE_MagicTarget__ForEachActiveEffectVisitor;

			virtual ~ForEachActiveEffectVisitor(){};  // 00

			// add
			virtual BSContainer::ForEachResult Accept(ActiveEffect* a_effect) = 0;  // 01
		};
		static_assert(sizeof(ForEachActiveEffectVisitor) == 0x8);

		class IPostCreationModification
		{
		public:
			inline static constexpr auto RTTI = RTTI_MagicTarget__IPostCreationModification;

			virtual ~IPostCreationModification();  // 00

			// add
			virtual void ModifyActiveEffect(ActiveEffect* a_effect) = 0;  // 01
		};
		static_assert(sizeof(IPostCreationModification) == 0x8);

		class ResultsCollector
		{
		public:
			MagicTarget*  target;       // 00
			Actor*        caster;       // 08
			MagicItem*    magicItem;    // 10
			std::uint16_t immunities;   // 18
			std::uint16_t nonTrivials;  // 1A
			std::uint32_t pad1C;        // 1C
		};
		static_assert(sizeof(ResultsCollector) == 0x20);

		struct SpellDispelData
		{
			MagicItem*                    spell;         // 00
			BSPointerHandle<Actor>        caster;        // 08
			std::uint32_t                 pad0C;         // 0C
			BSTSmartPointer<ActiveEffect> activeEffect;  // 10
			SpellDispelData*              next;          // 18
		};
		static_assert(sizeof(SpellDispelData) == 0x20);

		struct AddTargetData
		{
			bool CheckAddEffect(ActiveEffectFactory::CheckTargetArgs& a_args, float a_resistance);

			// members
			TESObjectREFR*             caster;                // 00
			MagicItem*                 magicItem;             // 08
			Effect*                    effect;                // 10
			TESBoundObject*            source;                // 18
			IPostCreationModification* postCreationCallback;  // 20
			ResultsCollector*          resultsCollector;      // 28
			NiPoint3                   explosionPoint;        // 30
			float                      magnitude;             // 3C
			float                      power;                 // 40
			MagicSystem::CastingSource castingSource;         // 44
			bool                       areaTarget;            // 48
			bool                       dualCasted;            // 49
			std::uint16_t              pad4A;                 // 4A
			std::uint32_t              pad4C;                 // 4C
		};
		static_assert(sizeof(AddTargetData) == 0x50);

		virtual ~MagicTarget();  // 00

		// add
		virtual bool               AddTarget(AddTargetData& a_targetData);                  // 01
		virtual TESObjectREFR*     GetTargetStatsObject();                                  // 02 - { return false; }
		[[nodiscard]] virtual bool MagicTargetIsActor() const;                              // 03 - { return false; }
		virtual bool               IsInvulnerable();                                        // 04 - { return false; }
		virtual void               InvalidateCommandedActorEffect(ActiveEffect* a_effect);  // 05 - { return; }
		virtual bool               CanAddActiveEffect() = 0;                                // 06
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() = 0;  // 07
#else
		// Slot 07 exists on every runtime: SE/AE return a BSSimpleList, VR a BSLocklessSimpleList<ActiveEffect*> (see GetVRActiveEffectList).
		virtual void* GetActiveEffectListNative() = 0;  // 07
#endif
		virtual void  EffectAdded(ActiveEffect* a_effect);                                                  // 08 - { return; }
		virtual void  EffectRemoved(ActiveEffect* a_effect);                                                // 09 - { return; }
		virtual float CheckResistance(MagicItem* a_magicItem, Effect* a_effect, TESBoundObject* a_object);  // 0A - { return 1.0; }
		virtual bool  CheckAbsorb(Actor* a_actor, MagicItem* a_magicItem, const Effect* a_effect);          // 0B - { return false; }
		bool          DispelEffect(MagicItem* a_spell, BSPointerHandle<Actor>& a_caster, ActiveEffect* a_effect = nullptr);
#if defined(SKYRIM_CROSS_VR)
		// SE/AE's persistent list; nullptr on VR, whose list is a BSLocklessSimpleList (see GetVRActiveEffectList).
		// Exclusive VR builds only have GetVRActiveEffectList().
		[[nodiscard]] BSSimpleList<ActiveEffect*>* GetActiveEffectList();
#endif
#if defined(ENABLE_SKYRIM_VR)
		// VR's persistent list; nullptr when not running on VR.
		[[nodiscard]] BSLocklessSimpleList<ActiveEffect*>* GetVRActiveEffectList();
		void                                               DispelEffectsWithArchetype(Archetype a_type, bool a_force);
#endif
		Actor* GetTargetAsActor();
		bool   HasEffectWithArchetype(Archetype a_type);
		bool   HasMagicEffect(EffectSetting* a_effect);
		bool   HasMagicEffectWithKeyword(BGSKeyword* a_keyword, MagicItem** a_spellOut);
		void   VisitEffects(ForEachActiveEffectVisitor& visitor);

		// Visitor helpers over the active effect list. They run the engine's own walk (VisitEffects), which is
		// the same function on every runtime and is the only walk that is correct on VR: VR's list uses the
		// engine's shared_ptr spin lock, which a plugin cannot reliably take itself.
		class GetEffectCount : public MagicTarget::ForEachActiveEffectVisitor
		{
		public:
			GetEffectCount() :
				m_count(0) {}

			virtual BSContainer::ForEachResult Accept(ActiveEffect* /*effect*/) override  // suppress c4100 error
			{
				m_count++;
				return BSContainer::ForEachResult::kContinue;
			}

			std::uint32_t GetCount() const { return m_count; }

		private:
			std::uint32_t m_count;
		};

		class GetNthEffect : public MagicTarget::ForEachActiveEffectVisitor
		{
		public:
			GetNthEffect(std::uint32_t n) :
				m_result(nullptr), m_n(n), m_count(0) {}

			virtual BSContainer::ForEachResult Accept(ActiveEffect* effect) override
			{
				if (m_count == m_n) {
					m_result = effect;
					return BSContainer::ForEachResult::kStop;
				}
				m_count++;
				return BSContainer::ForEachResult::kContinue;
			}

			ActiveEffect* GetResult() { return m_result; }

		private:
			ActiveEffect* m_result;
			std::uint32_t m_n;
			std::uint32_t m_count;
		};

		class EffectVisitor : public MagicTarget::ForEachActiveEffectVisitor
		{
		public:
			EffectVisitor(std::function<BSContainer::ForEachResult(ActiveEffect*)> func) :
				m_functor(func) {}

			virtual BSContainer::ForEachResult Accept(ActiveEffect* effect) override
			{
				return m_functor(effect);
			}

		protected:
			std::function<BSContainer::ForEachResult(ActiveEffect*)> m_functor;
		};

		/**
		 * @brief Call a_func for each active effect, on every runtime (return kStop to end early).
		 *
		 * Unlike the engine's own list, the walk is not locked on SE/AE, and on VR the ActiveEffect objects are
		 * not refcounted: another thread can unlink or delete an effect while it runs. Finish with the effect
		 * inside the callback and copy out plain data (base effect, flags); do not keep the ActiveEffect*,
		 * call into script, or nest a walk on the same target. ActiveEffect::Dispel only flags the effect, so
		 * it is safe to call from the callback.
		 */
		void VisitActiveEffects(std::function<BSContainer::ForEachResult(ActiveEffect*)> func)
		{
			EffectVisitor visitor(func);
			VisitEffects(visitor);
		}

		void ForEachActiveEffect(MagicTarget::ForEachActiveEffectVisitor& visitor)
		{
			VisitEffects(visitor);
		}

		// members
		SpellDispelData* postUpdateDispelList;  // 08
		std::uint16_t    pad10;                 // 10
		std::uint16_t    pad12;                 // 12
		std::uint32_t    pad14;                 // 14
	};
	static_assert(sizeof(MagicTarget) == 0x18);
}
