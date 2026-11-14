#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class MapMenu;

	class PlacePlayerMarkerCallbackFunctor : public IMessageBoxCallback
	{
	public:
		inline constexpr static auto RTTI = RTTI___PlacePlayerMarkerCallbackFunctor;
		inline constexpr static auto VTABLE = VTABLE___PlacePlayerMarkerCallbackFunctor;

		~PlacePlayerMarkerCallbackFunctor() override;  // 00

		// override (IMessageBoxCallback)
		virtual void Run(std::uint8_t a_button) override;

		// members
		MapMenu*     mapMenu;     // 10
		std::int32_t cursorPosX;  // 18
		std::int32_t cursorPosY;  // 1C
	};
	static_assert(sizeof(PlacePlayerMarkerCallbackFunctor) == 0x20);
}
