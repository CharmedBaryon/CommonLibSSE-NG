#pragma once

#include "RE/T/ThirdPersonState.h"

#include "REL/Common.h"

namespace RE
{
	class DragonCameraState : public ThirdPersonState
	{
	public:
		inline static constexpr auto RTTI = RTTI_DragonCameraState;
		inline static constexpr auto VTABLE = VTABLE_DragonCameraState;

		~DragonCameraState() override;  // 00

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
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03/04
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04/05
		void GetTranslation(NiPoint3& a_translation) override;               // 05/06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;                    // 06/07
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                    // 07/08
		void Revert(BGSLoadFormBuffer* a_buf) override;                      // 08/09

		void SetCameraHandle(RefHandle& a_handle) override;        // 09/0A - { return; }
		void Unk_0A(void) override;                                // 0A/0B - { return; }
		void ProcessWeaponDrawnChange(bool a_drawn) override;      // 0B/0C
		bool GetFreeRotationMode() const override;                 // 0C/0D
		void SetFreeRotationMode(bool a_weaponSheathed) override;  // 0D/0E
		void UpdateRotation();                                     // 0E/0F
		void HandleLookInput(const NiPoint2& a_input) override;    // 0F/10

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;  // 04
#endif

		ObjectRefHandle dragonHandle;      // 0E8
		std::uint32_t   unkEC;             // 0EC - bool?
		std::uint32_t   unkF0;             // 0F0 - bool?
		std::uint32_t   unkF4;             // 0F4 - float?
		bool            lockedOnTarget;    // 0F8
		std::uint8_t    padF9[3];          // 0F9
		std::uint32_t   unkFC;             // 0FC - float?
		std::uint32_t   unk100;            // 100
		std::uint32_t   unk104;            // 104 - float?
		std::uint32_t   unk108;            // 108
		ObjectRefHandle targetLockHandle;  // 10C
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(DragonCameraState) == 0x110);
#endif
}
