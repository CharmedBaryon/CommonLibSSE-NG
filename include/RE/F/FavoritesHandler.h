#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	class VrWandTouchpadPositionEvent;

	struct FavoritesHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_FavoritesHandler;
		inline static constexpr auto VTABLE = VTABLE_FavoritesHandler;

		~FavoritesHandler() override;  // 00

		// override
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessKinect(KinectEvent* a_event) override;  // 02 (VR 05)
		bool ProcessButton(ButtonEvent* a_event) override;  // 05 (VR 08)
#endif
#if defined(EXCLUSIVE_SKYRIM_VR)
		bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event) override;  // VR 03
#endif
	};
	static_assert(sizeof(FavoritesHandler) == 0x10);
}
