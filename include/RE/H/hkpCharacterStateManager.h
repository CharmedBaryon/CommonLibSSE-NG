#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkpCharacterState.h"

namespace RE
{
	class hkpCharacterStateManager : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpCharacterStateManager;
		inline static constexpr auto VTABLE = VTABLE_hkpCharacterStateManager;

		~hkpCharacterStateManager() override;  // 00

		// members
		hkpCharacterState* registeredState[hkpCharacterStateType::kTotal];  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpCharacterStateManager) == 0x68);
}
