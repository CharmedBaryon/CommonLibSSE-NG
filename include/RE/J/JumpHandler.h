#pragma once

#include "RE/P/PlayerInputHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct JumpHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_JumpHandler;
		inline static constexpr auto VTABLE = VTABLE_JumpHandler;

		~JumpHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			std::uint16_t unk10;  // 10
			std::uint16_t pad12;  // 12
			std::uint32_t pad14;  // 14
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x10);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 10
#endif
	};
	STATIC_ASSERT_SIZE(JumpHandler, 0x10, 0x10, 0x18, 0x10);
}
