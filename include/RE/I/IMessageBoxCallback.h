#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class IMessageBoxCallback : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMessageBoxCallback;
		inline static constexpr auto VTABLE = VTABLE_IMessageBoxCallback;

		virtual ~IMessageBoxCallback() = default;  // 00

		// add
		virtual void Run(std::uint8_t a_button) = 0;  // 01

		// members
		std::uint32_t pad0C;  // 0C
	};
	static_assert(sizeof(IMessageBoxCallback) == 0x10);
}
