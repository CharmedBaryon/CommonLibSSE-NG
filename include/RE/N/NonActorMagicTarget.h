#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/M/MagicTarget.h"

namespace RE
{
	class ActiveEffect;
	class TESObjectREFR;

	class NonActorMagicTarget :
		public BSExtraData,  // 00
		public MagicTarget   // 10
	{
	public:
		inline static constexpr auto RTTI = RTTI_NonActorMagicTarget;
		inline static constexpr auto VTABLE = VTABLE_NonActorMagicTarget;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kNonActorMagicTarget;

		~NonActorMagicTarget() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kNonActorMagicTarget; }

		// override (MagicTarget)
		bool                         AddTarget(AddTargetData& a_targetData) override;  // 01
		TESObjectREFR*               GetTargetStatsObject() override;                  // 02 - { return targetObject; }
		bool                         CanAddActiveEffect() override;                    // 06 - { return true; }
		BSSimpleList<ActiveEffect*>* GetActiveEffectList() override;                   // 07 - { return &activeEffects; }

		// members
		TESObjectREFR*              targetObject;   // 28
		BSSimpleList<ActiveEffect*> activeEffects;  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NonActorMagicTarget) == 0x40);
}
