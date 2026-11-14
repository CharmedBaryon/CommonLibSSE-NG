#pragma once

#include "RE/P/PlayerInputHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct ShoutHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ShoutHandler;
		inline static constexpr auto VTABLE = VTABLE_ShoutHandler;

		~ShoutHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		// members
		std::uint64_t unk10;  // 10
		std::uint64_t unk18;  // 18

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			std::uint8_t unk20;     // 20
			std::uint8_t pad21[7];  // 21
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x20);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 20
#endif
	};
	STATIC_ASSERT_SIZE(ShoutHandler, 0x20, 0x28);
}
