#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiQuaternion.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

#include "REL/Common.h"

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
		void Begin() override;  // 01
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void Unk_03() override;  // 03 - VR only
#else
		void Unk_03();  // 03 - Multi-runtime
#endif
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03/04
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04/05
		void GetTranslation(NiPoint3& a_translation) override;               // 05/06

		// members
		std::uint64_t   unk20;           // 20
		TESCameraState* transitionFrom;  // 28
		TESCameraState* transitionTo;    // 30
		std::uint16_t   unk38;           // 38
	};
	static_assert(sizeof(PlayerCameraTransitionState) == 0x40);
}
