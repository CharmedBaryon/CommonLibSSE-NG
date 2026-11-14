#pragma once

#ifdef ENABLE_SKYRIM_VR
#	include "RE/P/PlayerInputHandler.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct DragonRidingHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_DragonRidingHandler;
		inline static constexpr auto VTABLE = VTABLE_DragonRidingHandler;

		~DragonRidingHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01

		// VR members; the class only exists on VR, so the accessor is always valid.
		struct VR_RUNTIME_DATA
		{
			bool         dragonRidingActive;  // 10 - latched by the trigger/thumbstick virtuals
			std::uint8_t pad11[7];            // 11
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x10);
#	ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 10
#	endif
	};
	STATIC_ASSERT_SIZE(DragonRidingHandler, SIZE_UNDEFINED, SIZE_UNDEFINED, 0x18, 0x10);
}
#endif
