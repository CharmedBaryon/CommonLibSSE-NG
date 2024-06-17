#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSPointerHandle.h"
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
	class Actor;
	class ActiveEffect;
	class BGSKeyword;
	class EffectItem;
	class EffectSetting;
	class MagicItem;
	class TESBoundObject;
	class TESObjectREFR;

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
			TESObjectREFR*             caster;          // 00
			MagicItem*                 magicItem;       // 08
			Effect*                    effect;          // 10
			TESBoundObject*            source;          // 18
			std::uint64_t              unk20;           // 20 - MagicCaster::PostCreationCallback
			std::uint64_t              unk28;           // 28 - MagicTarget**
			NiPoint3                   explosionPoint;  // 30
			float                      magnitude;       // 3C
			float                      unk40;           // 40
			MagicSystem::CastingSource castingSource;   // 44
			std::uint8_t               unk48;           // 48
			bool                       dualCasted;      // 49
			std::uint16_t              pad4A;           // 4A
			std::uint32_t              pad4C;           // 4C
		};
		static_assert(sizeof(AddTargetData) == 0x50);

		virtual ~MagicTarget();  // 00

		// add
		virtual bool                         AddTarget(AddTargetData& a_targetData);                                               // 01
		virtual TESObjectREFR*               GetTargetStatsObject();                                                               // 02 - { return false; }
		[[nodiscard]] virtual bool           MagicTargetIsActor() const;                                                           // 03 - { return false; }
		virtual bool                         IsInvulnerable();                                                                     // 04 - { return false; }
		virtual void                         InvalidateCommandedActorEffect(ActiveEffect* a_effect);                               // 05 - { return; }
		virtual bool                         CanAddActiveEffect() = 0;                                                             // 06
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() = 0;                                                            // 07
		virtual void                         EffectAdded(ActiveEffect* a_effect);                                                  // 08 - { return; }
		virtual void                         EffectRemoved(ActiveEffect* a_effect);                                                // 09 - { return; }
		virtual float                        CheckResistance(MagicItem* a_magicItem, Effect* a_effect, TESBoundObject* a_object);  // 0A - { return 1.0; }
		virtual bool                         CheckAbsorb(Actor* a_actor, MagicItem* a_magicItem, const Effect* a_effect);          // 0B - { return false; }

		bool DispelEffect(MagicItem* a_spell, BSPointerHandle<Actor>& a_caster, ActiveEffect* a_effect = nullptr);
#if defined(ENABLE_SKYRIM_VR)
		void DispelEffectsWithArchetype(Archetype a_type, bool a_force);
#endif
		Actor* GetTargetAsActor();
		bool   HasEffectWithArchetype(Archetype a_type);
		bool   HasMagicEffect(EffectSetting* a_effect);
		bool   HasMagicEffectWithKeyword(BGSKeyword* a_keyword, std::uint64_t a_arg2);
		void   VisitEffects(ForEachActiveEffectVisitor& visitor);

#ifdef ENABLE_SKYRIM_VR
		//VR requires a visitor to access all items
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
					return BSContainer::ForEachResult::kContinue;
				}
				m_count++;
				return BSContainer::ForEachResult::kStop;
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

		void VisitActiveEffects(std::function<BSContainer::ForEachResult(ActiveEffect*)> func)
		{
			EffectVisitor visitor(func);
			ForEachActiveEffect(visitor);
		}

		void ForEachActiveEffect(MagicTarget::ForEachActiveEffectVisitor& visitor)
		{
			using func_t = decltype(&MagicTarget::ForEachActiveEffect);
			REL::Relocation<func_t> func{ REL::ID(33756) };
			func(this, visitor);
		}
#endif

		// members
		SpellDispelData* postUpdateDispelList;  // 08
		std::uint16_t    pad12;                 // 12
		std::uint32_t    pad14;                 // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MagicTarget) == 0x18);
}
