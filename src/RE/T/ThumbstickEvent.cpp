#include "RE/T/ThumbstickEvent.h"

namespace RE
{
	bool ThumbstickEvent::IsLeft(void) const
	{
		return idCode == InputType::kLeftThumbstick;
	}

	bool ThumbstickEvent::IsRight(void) const
	{
		return idCode == InputType::kRightThumbstick;
	}

	bool ThumbstickEvent::IsOffHand() const
	{
		return IsLeft();
	}

	bool ThumbstickEvent::IsMainHand() const
	{
		return IsRight();
	}
}
