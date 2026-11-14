#pragma once

#ifdef ENABLE_SKYRIM_VR
#	include "RE/H/HeldStateHandler.h"
#	include "RE/N/NiPoint3.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct VrSwimHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_VrSwimHandler;
		inline static constexpr auto VTABLE = VTABLE_VrSwimHandler;

		~VrSwimHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01

		// VR members; the class only exists on VR, so the accessor is always valid.
		// Hand index 0 is the left wand node and 1 the right wand node (ProcessButton
		// picks the node by it); each stroke ring holds 5 samples per hand.
		struct VR_RUNTIME_DATA
		{
			NiPoint3     lastHandLocalPos[2];    // 60 - wand node local position at the last held-button tick
			NiPoint3     strokeSamples[10];      // 78 - [hand * 5 + ring slot], (last - current) per tick
			std::int32_t handRingIndex[2];       // F0 - ring cursor per hand, cycles 0-4
			float        handLastStrokeTime[2];  // F8 - compared against gTimeManager smoothedRunTimeMS
			bool         handSwimActive[2];      // 100
			std::uint8_t pad102[6];              // 102
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x60);
#	ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 60
#	endif
	};
	STATIC_ASSERT_SIZE(VrSwimHandler, SIZE_UNDEFINED, SIZE_UNDEFINED, 0x108, 0x18);
}
#endif
