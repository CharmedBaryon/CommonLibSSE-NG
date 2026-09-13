#pragma once

#include "RE/B/BSInputDevice.h"

namespace RE
{
	class BSMouseDevice : public BSInputDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMouseDevice;
		inline static constexpr auto VTABLE = VTABLE_BSMouseDevice;

		~BSMouseDevice() override;  // 00

		// add
		virtual void Reinitialize(void);  // 09 - { return; }

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	bool backgroundMouse; /* 70 / 78 */
			RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x70, 0x78);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif

	protected:
		friend class BSInputDeviceFactory;
		BSMouseDevice();
	};
	STATIC_ASSERT_SIZE(BSMouseDevice, 0x78, 0x78, 0x80, 0x8);
}
#undef RUNTIME_DATA_CONTENT
