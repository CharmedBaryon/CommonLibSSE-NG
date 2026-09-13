#pragma once

#include "RE/N/NiPoint2.h"
#include "RE/N/NiQuaternion.h"
#include "RE/T/TESCameraState.h"

#include "REL/Common.h"

namespace RE
{
	class TweenMenuCameraState : public TESCameraState
	{
	public:
		inline static constexpr auto RTTI = RTTI_TweenMenuCameraState;
		inline static constexpr auto VTABLE = VTABLE_TweenMenuCameraState;

		~TweenMenuCameraState() override;  // 00

		// override (TESCameraState)
		void Begin() override;  // 01
		void End() override;    // 02
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
		NiQuaternion  intialRotation;   // 20
		float         initialFOV;       // 30
		NiPoint2      currentAddedRot;  // 34
		NiPoint2      targetAddedRot;   // 3C
		float         currentAddedFOV;  // 44
		float         targetAddedFOV;   // 48
		bool          endingState;      // 4C
		std::uint8_t  pad4D;            // 4D
		std::uint16_t pad4E;            // 4E
	};
	static_assert(sizeof(TweenMenuCameraState) == 0x50);
}
