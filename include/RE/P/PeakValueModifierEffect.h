#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class ActiveEffect;

	class PeakValueModifierEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_PeakValueModifierEffect;
		inline static constexpr auto VTABLE = VTABLE_PeakValueModifierEffect;

		// override (ActiveEffect)
		virtual void         OnAdd(MagicTarget* a_target) override;                           // 01
		virtual void         OnRemove() override;                                             // 02
		virtual void         EvaluateConditions(float a_delta, bool a_forceUpdate) override;  // 05
		virtual void         FinishLoadGame(BGSLoadFormBuffer* a_buf) override;               // 0A
		virtual std::int32_t Compare(ActiveEffect* a_otherEffect) override;                   // 0C
		virtual void         ClearTargetImpl() override;                                      // 12
		virtual ~PeakValueModifierEffect();                                                   // 13

		// members
		BSTSmartPointer<ActiveEffect> next;  // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(PeakValueModifierEffect) == 0xA0);
}
