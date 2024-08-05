#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IDEvent.h"
#include "RE/I/InputEvent.h"
#include "RE/M/MemoryManager.h"
#include "RE/V/VRWandEvent.h"

namespace RE
{
	class ButtonEvent :
#if defined(EXCLUSIVE_SKYRIM_VR)
		public VRWandEvent
#else
		public IDEvent
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_ButtonEvent;
		inline static constexpr auto VTABLE = VTABLE_ButtonEvent;

		~ButtonEvent() override;  // 00

		[[nodiscard]] float Value() const noexcept { return this->GetRuntimeData().value; }
		[[nodiscard]] float HeldDuration() const noexcept { return this->GetRuntimeData().heldDownSecs; }
		[[nodiscard]] bool  IsPressed() const noexcept { return Value() > 0.0F; }
		[[nodiscard]] bool  IsRepeating() const noexcept { return HeldDuration() > 0.0F; }
		[[nodiscard]] bool  IsDown() const noexcept { return IsPressed() && (HeldDuration() == 0.0F); }
		[[nodiscard]] bool  IsHeld() const noexcept { return IsPressed() && IsRepeating(); }
		[[nodiscard]] bool  IsUp() const noexcept { return (Value() == 0.0F) && IsRepeating(); }

		static ButtonEvent* Create(INPUT_DEVICE a_inputDevice, const BSFixedString& a_userEvent, uint32_t a_idCode, float a_value, float a_heldDownSecs)
		{
			{
				auto buttonEvent = malloc<ButtonEvent>(sizeof(ButtonEvent));
				std::memset(reinterpret_cast<void*>(buttonEvent), 0, sizeof(ButtonEvent));
				if (buttonEvent) {
					stl::emplace_vtable<ButtonEvent>(buttonEvent);
					buttonEvent->device = a_inputDevice;
					buttonEvent->eventType = INPUT_EVENT_TYPE::kButton;
					buttonEvent->next = nullptr;
					buttonEvent->userEvent = a_userEvent;
					buttonEvent->idCode = a_idCode;
					buttonEvent->GetRuntimeData().value = a_value;
					buttonEvent->GetRuntimeData().heldDownSecs = a_heldDownSecs;
				}
				return buttonEvent;
			}
		}

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT     \
	float value;        /* 00 */ \
	float heldDownSecs; /* 04 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);
		//members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 28, 30
#endif
		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x28, 0x30);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x28, 0x30);
		}

		[[nodiscard]] VRWandEvent* AsVRWandEvent() noexcept
		{
			if (!REL::Module::IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<VRWandEvent>(this, 0, 0);
		}

		[[nodiscard]] const VRWandEvent* AsVRWandEvent() const noexcept
		{
			return const_cast<ButtonEvent*>(this)->AsVRWandEvent();
		}

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(ButtonEvent) == 0x30);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ButtonEvent) == 0x38);
#else
	static_assert(sizeof(ButtonEvent) == 0x28);
#endif
}
#undef RUNTIME_DATA_CONTENT
