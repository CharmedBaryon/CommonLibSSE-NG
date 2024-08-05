#pragma once

namespace RE
{
	class TESObjectCELL;

	struct TESCellFullyLoadedEvent
	{
	public:
		// members
		TESObjectCELL* cell;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESCellFullyLoadedEvent) == 0x8);
}
