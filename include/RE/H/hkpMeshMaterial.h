#pragma once

namespace RE
{
	class hkpMeshMaterial
	{
	public:
		//members
		std::uint32_t filterInfo;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpMeshMaterial) == 0x4);
}
