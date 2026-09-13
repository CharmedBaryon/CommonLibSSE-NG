#pragma once

#include "RE/B/BSInputDevice.h"
#include "RE/B/BSTEvent.h"

namespace RE
{
	struct BSGamepadEvent;

	class BSGamepadDevice :
		public BSInputDevice  // 00
#ifndef SKYRIM_CROSS_VR
		,
		public BSTEventSource<BSGamepadEvent>  // 70 SE / 78 VR
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGamepadDevice;
		inline static constexpr auto VTABLE = VTABLE_BSGamepadDevice;

		~BSGamepadDevice() override;  // 00

		// override (BSInputDevice)
		bool IsEnabled() const override;  // 07 - { return connected && userIndex != -1; }

		// add
		virtual void SetVibration(float a_largeMotor, float a_smallMotor) = 0;                                              // 09
		virtual void SetDeviceLight(const std::uint32_t (&a_rgb)[3]);                                                       // 0A - { return; }
		virtual void ResetDeviceLight();                                                                                    // 0B - { return; }
		virtual bool IsRemoteController();                                                                                  // 0C - { return 0; }
		virtual void NormalizeThumbstickValue(std::int32_t a_thumbX, std::int32_t a_thumbY, float& a_xOut, float& a_yOut);  // 0D
		virtual void DoEnableListeningMode();                                                                               // 0E - { return; }

		// BSTEventSource<BSGamepadEvent> base shifts from 0x70 (SE) to 0x78 (VR).
		// In SKYRIM_CROSS_VR the base is excluded from the hierarchy; use AsBSGamepadEventSource().
		RUNTIME_CAST_ACCESSOR(BSTEventSource<BSGamepadEvent>, AsBSGamepadEventSource, 0x70, 0x78);

		// Members below shift accordingly: C8 (SE) -> D0 (VR).
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                       \
	std::int32_t  userIndex;         /* C8 / D0 */ \
	bool          connected;         /* CC / D4 */ \
	bool          listeningForInput; /* CD / D5 */ \
	std::uint16_t padCE;             /* CE / D6 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0xC8, 0xD0);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif

	protected:
		BSGamepadDevice();
	};
	STATIC_ASSERT_SIZE(BSGamepadDevice, 0xD0, 0xD0, 0xD8, 0x8, 0xD0);
}
#undef RUNTIME_DATA_CONTENT
