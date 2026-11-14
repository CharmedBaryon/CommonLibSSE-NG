#pragma once

#include "RE/P/PlayerInputHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct ReadyWeaponHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ReadyWeaponHandler;
		inline static constexpr auto VTABLE = VTABLE_ReadyWeaponHandler;

		~ReadyWeaponHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			std::uint8_t unk10;     // 10
			std::uint8_t pad11[7];  // 11
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x10);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 10
#endif
	};
	STATIC_ASSERT_SIZE(ReadyWeaponHandler, 0x10, 0x18);
}
