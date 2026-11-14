#include "catch2/catch_all.hpp"

#include "RE/H/HeldStateHandler.h"
#include "RE/P/PlayerInputHandler.h"

#ifdef EXCLUSIVE_SKYRIM_VR

namespace
{
	struct SlotProbe : RE::PlayerInputHandler
	{
		int hit{ -1 };

		bool CanProcess(RE::InputEvent*) override { return true; }
		void ProcessVrWandTouchpadSwipe(RE::VrWandTouchpadSwipeEvent*, RE::PlayerControlsData*) override { hit = 2; }
		void ProcessVrWandTouchpadPosition(RE::VrWandTouchpadPositionEvent*, RE::PlayerControlsData*) override { hit = 3; }
		void ProcessThumbstick(RE::ThumbstickEvent*, RE::PlayerControlsData*) override { hit = 4; }
		void ProcessMouseMove(RE::MouseMoveEvent*, RE::PlayerControlsData*) override { hit = 5; }
		void ProcessButton(RE::ButtonEvent*, RE::PlayerControlsData*) override { hit = 6; }
	};

	struct HeldSlotProbe : RE::HeldStateHandler
	{
		int hit{ -1 };

		bool CanProcess(RE::InputEvent*) override { return true; }
		void UpdateHeldStateActive(const RE::ButtonEvent*) override { hit = 7; }
		void SetHeldStateActive(bool) override { hit = 8; }
	};

	template <class T>
	int CallSlot(T& a_object, std::size_t a_slot)
	{
		using Fn = void (*)(void*, void*, void*);
		auto vtbl = *reinterpret_cast<void***>(&a_object);
		reinterpret_cast<Fn>(vtbl[a_slot])(&a_object, nullptr, nullptr);
		return a_object.hit;
	}
}

TEST_CASE("PlayerInputHandler VR virtual slots follow the dispatcher order")
{
	SlotProbe probe;
	for (std::size_t slot = 2; slot <= 6; ++slot) {
		CHECK(CallSlot(probe, slot) == static_cast<int>(slot));
	}

	HeldSlotProbe held;
	CHECK(CallSlot(held, 7) == 7);
	CHECK(CallSlot(held, 8) == 8);
}

#endif
