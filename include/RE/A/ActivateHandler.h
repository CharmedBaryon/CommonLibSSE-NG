#pragma once

#include "RE/H/HeldStateHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct ActivateHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActivateHandler;
		inline static constexpr auto VTABLE = VTABLE_ActivateHandler;

		~ActivateHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		constexpr inline void SetHeldButtonActionSuccess(bool a_success) noexcept
		{
			heldButtonActionSuccess = a_success;
		}

		// members
		std::uint8_t  unk18;                    // 18
		std::uint8_t  unk19;                    // 19
		bool          heldButtonActionSuccess;  // 1A
		bool          disabled;                 // 1B
		std::uint32_t unk1C;                    // 1C

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			float         unk68;  // 68
			std::uint32_t unk6C;  // 6C
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x68);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 68
#endif
	};
	STATIC_ASSERT_SIZE(ActivateHandler, 0x20, 0x20, 0x70, 0x20);
}
