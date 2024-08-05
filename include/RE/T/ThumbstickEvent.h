#pragma once

#include "RE/I/IDEvent.h"

namespace RE
{
	class ThumbstickEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_ThumbstickEvent;
		inline static constexpr auto VTABLE = VTABLE_ThumbstickEvent;

		struct InputTypes
		{
			enum InputType : std::uint32_t
			{
				kLeftThumbstick = 0x0B,
				kRightThumbstick = 0x0C
			};
		};
		using InputType = InputTypes::InputType;

		void Init(InputType a_id, float a_xValue, float a_yValue)
		{
			Init(a_id, INPUT_DEVICE::kGamepad, a_xValue, a_yValue, ""sv);
		}

		void Init(InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue)
		{
			Init(a_id, a_device, a_xValue, a_yValue, ""sv);
		}

		void Init(InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue, const RE::BSFixedString& a_userEvent)
		{
			xValue = a_xValue;
			yValue = a_yValue;
			device = a_device;
			idCode = a_id;
			userEvent = a_userEvent;
		}

		[[nodiscard]] bool IsLeft() const;
		[[nodiscard]] bool IsRight() const;
		[[nodiscard]] bool IsOffHand() const;
		[[nodiscard]] bool IsMainHand() const;

		// members
		float xValue;  // 28
		float yValue;  // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ThumbstickEvent) == 0x30);
}
