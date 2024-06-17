#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class InvisibilityEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_InvisibilityEffect;
		inline static constexpr auto VTABLE = VTABLE_InvisibilityEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;                     // 04
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 0A
		virtual void Revert(BGSLoadFormBuffer* a_buf) override;          // 0B
		virtual ~InvisibilityEffect();                                   // 13
		virtual void Start() override;                                   // 14
		virtual void Finish() override;                                  // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(InvisibilityEffect) == 0x98);
}
