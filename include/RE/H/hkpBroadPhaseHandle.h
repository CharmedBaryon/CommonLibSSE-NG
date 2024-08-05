#pragma once

namespace RE
{
	class hkpBroadPhaseHandle
	{
	public:
		std::uint32_t id;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpBroadPhaseHandle) == 0x4);
}
