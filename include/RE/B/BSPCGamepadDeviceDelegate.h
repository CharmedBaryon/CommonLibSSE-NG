#pragma once

#include "RE/B/BSGamepadDevice.h"

namespace RE
{
	class BSPCGamepadDeviceHandler;

	class BSPCGamepadDeviceDelegate : public BSGamepadDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPCGamepadDeviceDelegate;
		inline static constexpr auto VTABLE = VTABLE_BSPCGamepadDeviceDelegate;

		~BSPCGamepadDeviceDelegate() override;  // 00

		// override (BSGamepadDevice)
		void Initialize() override;                                          // 01 - { return; }
		void Poll(float a_timeDelta) override;                               // 02 - { return; }
		void Shutdown() override;                                            // 03 - { return; }
		void ClearInputState() override;                                     // 08 - { return; }
		void SetVibration(float a_largeMotor, float a_smallMotor) override;  // 09 - { return; }

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	BSPCGamepadDeviceHandler* gamepadDeviceHandler; /* D0 / D8 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0xD0, 0xD8);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif

	protected:
		friend class BSGamepadDeviceHandler;
		BSPCGamepadDeviceDelegate();
	};
	STATIC_ASSERT_SIZE(BSPCGamepadDeviceDelegate, 0xD8, 0xD8, 0xE0, 0x8, 0xD8);
}
#undef RUNTIME_DATA_CONTENT
