#pragma once

#include "RE/H/HeldStateHandler.h"
#include "REL/RuntimeDataAccessors.h"

#ifdef ENABLE_SKYRIM_VR
namespace RE
{
	struct TeleportHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_TeleportHandler;

		~TeleportHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#	ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#	endif

		// VR members; the accessor is always valid because the class only exists on VR
		struct VR_RUNTIME_DATA
		{
			std::uint64_t unk_60;  // 60
			std::uint64_t unk_68;  // 68
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x60);
#	ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 60
#	endif
	};
	STATIC_ASSERT_SIZE(TeleportHandler, SIZE_UNDEFINED, SIZE_UNDEFINED, 0x70, 0x18);

}
#endif
