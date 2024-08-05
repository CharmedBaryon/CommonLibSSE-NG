#pragma once

#include "RE/H/hkpCharacterState.h"

namespace RE
{
	class bhkCharacterState : public hkpCharacterState
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharacterState;
		inline static constexpr auto VTABLE = VTABLE_bhkCharacterState;

		~bhkCharacterState() override;  // 00

		// override (hkpCharacterState)
		void Update(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) override;  // 06
		void Change(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) override;  // 07

		// add
		virtual void Unk_08(void) = 0;  // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkCharacterState) == 0x10);
}
