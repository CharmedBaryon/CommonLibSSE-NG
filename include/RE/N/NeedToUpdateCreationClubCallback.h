#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class NeedToUpdateCreationClubCallback : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI_NeedToUpdateCreationClubCallback;
		inline static constexpr auto VTABLE = VTABLE_NeedToUpdateCreationClubCallback;

		~NeedToUpdateCreationClubCallback() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  // 01
	};
	static_assert(sizeof(NeedToUpdateCreationClubCallback) == 0x10);
}
