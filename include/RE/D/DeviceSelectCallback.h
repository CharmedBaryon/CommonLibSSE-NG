#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class DeviceSelectCallback : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___DeviceSelectCallback;
		inline static constexpr auto VTABLE = VTABLE___DeviceSelectCallback;

		~DeviceSelectCallback() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  // 01 - { return; }
	};
	static_assert(sizeof(DeviceSelectCallback) == 0x10);
}
