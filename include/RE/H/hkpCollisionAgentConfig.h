#pragma once

namespace RE
{
	struct hkpCollisionAgentConfig
	{
	public:
		// members
		float         iterativeLinearCastEarlyOutDistance;  // 0
		std::int32_t  iterativeLinearCastMaxIterations;     // 4
		std::uint64_t pad8;                                 // 8
	};
	static_assert(sizeof(hkpCollisionAgentConfig) == 0x10);
}
