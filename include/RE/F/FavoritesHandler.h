#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct FavoritesHandler : public MenuEventHandler
	{
	public:
		inline static auto RTTI = RTTI_FavoritesHandler;

		~FavoritesHandler() override;  // 00

		// override
		bool CanProcess(InputEvent* a_event) override;      // 01
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05
	};
	static_assert(sizeof(FavoritesHandler) == 0x10);
}
