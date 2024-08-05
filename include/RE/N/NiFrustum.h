#pragma once

namespace RE
{
	class NiFrustum
	{
	public:
		// members
		float fLeft;    // 00
		float fRight;   // 04
		float fTop;     // 08
		float fBottom;  // 0C
		float fNear;    // 10
		float fFar;     // 14
		bool  bOrtho;   // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiFrustum) == 0x1C);
}
