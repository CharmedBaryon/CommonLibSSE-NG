#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiQuaternion.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class NiNode;

	class PlayerCameraTransitionState : public TESCameraState
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerCameraTransitionState;
		inline static constexpr auto VTABLE = VTABLE_PlayerCameraTransitionState;

		~PlayerCameraTransitionState() override;  // 00

		// override (TESCameraState)
		void Begin() override;                                               // 01
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04
		void GetTranslation(NiPoint3& a_translation) override;               // 05

		// members
		std::uint64_t   unk20;           // 20
		TESCameraState* transitionFrom;  // 28
		TESCameraState* transitionTo;    // 30
		std::uint16_t   unk38;           // 38
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(PlayerCameraTransitionState) == 0x40);
}
