#pragma once

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkbPoweredRagdollControlData
	{
	public:
		// members
		float maxForce = 50.0f;                     // 00
		float tau = 0.8f;                           // 04
		float damping = 1.0f;                       // 08
		float proportionalRecoveryVelocity = 2.0f;  // 0C
		float constantRecoveryVelocity = 1.0f;      // 10
	};
}
