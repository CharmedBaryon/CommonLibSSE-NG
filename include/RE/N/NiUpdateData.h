#pragma once

namespace RE
{
	class NiUpdateData
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kDirty = 1 << 0,
			kDisableCollision = 1 << 13
		};

		float                             time;   // 0
		REX::EnumSet<Flag, std::uint32_t> flags;  // 4
	};
	static_assert(sizeof(NiUpdateData) == 0x8);
}
