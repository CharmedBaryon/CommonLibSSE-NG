#pragma once

#include "RE/B/bhkCharacterState.h"

namespace RE
{
	class bhkCharacterStateClimbing : public bhkCharacterState
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharacterStateClimbing;
		inline static constexpr auto VTABLE = VTABLE_bhkCharacterStateClimbing;

		~bhkCharacterStateClimbing() override;  // 00

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;  // 03 - { return kClimbing; }
		void                  Unk_08(void) override;     // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkCharacterStateClimbing) == 0x10);
}
