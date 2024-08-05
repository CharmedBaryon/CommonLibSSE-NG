#pragma once

namespace RE
{
	struct TESResolveNPCTemplatesEvent
	{
	public:
		// members
		FormID        templateID;  // 00
		std::uint32_t pad04;       // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESResolveNPCTemplatesEvent) == 0x8);
}