#pragma once

#include "RE/T/ThirdPersonState.h"

#include "REL/Common.h"

namespace RE
{
	class HorseCameraState : public ThirdPersonState
	{
	public:
		inline static constexpr auto RTTI = RTTI_HorseCameraState;
		inline static constexpr auto VTABLE = VTABLE_HorseCameraState;

		~HorseCameraState() override;  // 00

		// override (ThirdPersonState)
		void Begin() override;  // 01
		void End() override;    // 02
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void Unk_03() override;  // 03 - VR only
#else
		void Unk_03();  // 03 - Multi-runtime
#endif
#ifndef SKYRIM_CROSS_VR
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 06/07
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 07/08
		void Revert(BGSLoadFormBuffer* a_buf) override;    // 08/09
#endif
		void SetCameraHandle(RefHandle& a_handle) SKYRIM_REL_VR_OVERRIDE;        // 09/0A - { return; }
		void Unk_0A(void) SKYRIM_REL_VR_OVERRIDE;                                // 0A/0B - { return; }
		void ProcessWeaponDrawnChange(bool a_drawn) SKYRIM_REL_VR_OVERRIDE;      // 0B/0C
		bool GetFreeRotationMode() const SKYRIM_REL_VR_OVERRIDE;                 // 0C/0D
		void SetFreeRotationMode(bool a_weaponSheathed) SKYRIM_REL_VR_OVERRIDE;  // 0D/0E
#ifndef SKYRIM_CROSS_VR
		void UpdateRotation() override;  // 0E/0F
#endif
		void HandleLookInput(const NiPoint2& a_input) SKYRIM_REL_VR_OVERRIDE;  // 0F/10

		// members
		ObjectRefHandle horseRefHandle;         // E8
		float           horseCurrentDirection;  // EC
		std::uint64_t   unkF0;                  // F0
	};
	STATIC_ASSERT_SIZE(HorseCameraState, 0xF8);
}
