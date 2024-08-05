#pragma once

namespace RE
{
	class hkpSolverResults
	{
	public:
		// members
		float impulse;  // 00
		float data;     // 04
	};
	static_assert(sizeof(hkpSolverResults) == 0x08);
}
