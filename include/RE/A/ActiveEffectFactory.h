#pragma once

#include "RE/M/MagicSystem.h"

namespace RE
{
	class Actor;
	class EffectSetting;
	class MagicItem;
	class MagicCaster;
	class MagicTarget;
	struct Effect;

	namespace ActiveEffectFactory
	{
		struct CheckTargetArgs
		{
			enum class FailReason
			{
				kOk = 0,
				kUnknown = 1,
				kLevelTooHigh = 2
			};

			MagicTarget*                         target;         // 00
			Actor*                               caster;         // 08
			float                                magnitude;      // 10
			EffectSetting*                       effectSetting;  // 18
			MagicItem*                           spell;          // 20
			bool                                 dualCast;       // 28
			REX::Enum<FailReason, std::uint32_t> failReason;     // 2C
		};
		static_assert(sizeof(CheckTargetArgs) == 0x30);

		bool CheckCast(MagicCaster* a_caster, MagicItem* a_spell, Effect* a_effect, MagicSystem::CannotCastReason& a_reason);
		void ReportAddTargetFailure(CheckTargetArgs& a_args);
	}
}
