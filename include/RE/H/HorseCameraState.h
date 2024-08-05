#pragma once

#include "RE/T/ThirdPersonState.h"

namespace RE
{
	class NiNode;

	class HorseCameraState : public ThirdPersonState
	{
	public:
		inline static constexpr auto RTTI = RTTI_HorseCameraState;
		inline static constexpr auto VTABLE = VTABLE_HorseCameraState;

		~HorseCameraState() override;  // 00

		// override (ThirdPersonState)
		void Begin() override;                                     // 01
		void End() override;                                       // 02
		void SaveGame(BGSSaveFormBuffer* a_buf) override;          // 06
		void LoadGame(BGSLoadFormBuffer* a_buf) override;          // 07
		void Revert(BGSLoadFormBuffer* a_buf) override;            // 08
		void SetCameraHandle(RefHandle& a_handle) override;        // 09 - { return; }
		void Unk_0A(void) override;                                // 0A - { return; }
		void ProcessWeaponDrawnChange(bool a_drawn) override;      // 0B
		bool GetFreeRotationMode() const override;                 // 0C
		void SetFreeRotationMode(bool a_weaponSheathed) override;  // 0D
		void HandleLookInput(const NiPoint2& a_input) override;    // 0F

		// members
		ObjectRefHandle horseRefHandle;         // E8
		float           horseCurrentDirection;  // EC
		std::uint64_t   unkF0;                  // F0
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(HorseCameraState) == 0x110);
#else
	static_assert(sizeof(HorseCameraState) == 0xF8);
#endif
}
