#pragma once

#include "RE/B/bhkCharacterState.h"

namespace RE
{
	class bhkCharacterStateJumping : public bhkCharacterState
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharacterStateJumping;
		inline static constexpr auto VTABLE = VTABLE_bhkCharacterStateJumping;

		~bhkCharacterStateJumping() override;  // 00

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;  // 03 - { return kJumping; }
		void                  Unk_08(void) override;     // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkCharacterStateJumping) == 0x10);
}
