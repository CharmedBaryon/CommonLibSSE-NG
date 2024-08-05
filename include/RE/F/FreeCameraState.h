#pragma once

#include "RE/B/BSTPoint.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class NiNode;

	class FreeCameraState :
		public TESCameraState,     // 00
		public PlayerInputHandler  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_FreeCameraState;
		inline static constexpr auto VTABLE = VTABLE_FreeCameraState;

		~FreeCameraState() override;  // 00

		// override (TESCameraState)
		void Begin() override;                                               // 01
		void End() override;                                                 // 02
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04
		void GetTranslation(NiPoint3& a_translation) override;               // 05

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                          // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;  // 04

		// members
		NiPoint3         translation;        // 30
		BSTPoint2<float> rotation;           // 3C
		BSTPoint2<float> zUpDown;            // 44
		std::int16_t     verticalDirection;  // 4C
		bool             useRunSpeed;        // 4E
		bool             lockToZPlane;       // 4F
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	if defined(ENABLE_SKYRIM_AE) || defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(FreeCameraState) == 0x50);
#	else
	static_assert(sizeof(FreeCameraState) == 0x48);
#	endif
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_AE)
#else
	static_assert(sizeof(FreeCameraState) == 0x50);
#endif
}
