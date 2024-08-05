#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct FavoritesHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_FavoritesHandler;
		inline static constexpr auto VTABLE = VTABLE_FavoritesHandler;

		~FavoritesHandler() override;  // 00

		// override
		bool CanProcess(InputEvent* a_event) override;      // 01
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FavoritesHandler) == 0x10);
}
