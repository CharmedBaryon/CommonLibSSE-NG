#pragma once

#include "RE/H/HeldStateHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct SprintHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_SprintHandler;
		inline static constexpr auto VTABLE = VTABLE_SprintHandler;

		~SprintHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			std::uint32_t unk60;     // 60
			std::uint8_t  unk64;     // 64
			std::uint8_t  pad65[3];  // 65
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x60);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 60
#endif
	};
	STATIC_ASSERT_SIZE(SprintHandler, 0x18, 0x68);
}
