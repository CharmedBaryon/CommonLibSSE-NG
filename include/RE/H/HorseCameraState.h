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

		virtual ~HorseCameraState();  // 00

		// override (ThirdPersonState)
		virtual void Begin() override;                                     // 01
		virtual void End() override;                                       // 02
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;          // 06
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;          // 07
		virtual void Revert(BGSLoadFormBuffer* a_buf) override;            // 08
		virtual void SetCameraHandle(RefHandle& a_handle) override;        // 09 - { return; }
		virtual void Unk_0A(void) override;                                // 0A - { return; }
		virtual void ProcessWeaponDrawnChange(bool a_drawn) override;      // 0B
		virtual bool GetFreeRotationMode() const override;                 // 0C
		virtual void SetFreeRotationMode(bool a_weaponSheathed) override;  // 0D
		virtual void HandleLookInput(const NiPoint2& a_input) override;    // 0F

		// members
		ObjectRefHandle horseRefHandle;         // E8
		float           horseCurrentDirection;  // EC
		std::uint64_t   unkF0;                  // F0
	};
	static_assert(sizeof(HorseCameraState) == 0xF8);
}
