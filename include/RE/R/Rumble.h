#pragma once

namespace RE
{
	// It looks like this is a non-singleton static class in Skyrim SE, vs a singleton class in FO4
	class Rumble
	{
		static void DisableRumble();

	private:
		KEEP_FOR_RE()
	};
}