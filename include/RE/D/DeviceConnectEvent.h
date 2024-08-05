#pragma once

#include "RE/I/InputEvent.h"

namespace RE
{
	class DeviceConnectEvent : public InputEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_DeviceConnectEvent;
		inline static constexpr auto VTABLE = VTABLE_DeviceConnectEvent;

		~DeviceConnectEvent() override;  // 00

		void Init(INPUT_DEVICE a_device, bool a_connected)
		{
			device = a_device;
			connected = a_connected;
		}

		// members
		bool          connected;  // 18
		std::uint8_t  pad19;      // 19
		std::uint16_t pad1A;      // 1A
		std::uint32_t pad1C;      // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DeviceConnectEvent) == 0x20);
}
