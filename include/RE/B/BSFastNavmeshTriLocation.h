#pragma once

#include <cstdint>

namespace RE
{
	class BSNavmesh;

	class BSFastNavmeshTriLocation
	{
	public:
		virtual ~BSFastNavmeshTriLocation();  // 00

		// members
		BSNavmesh*    navMesh;   // 08 - VR confirmed
		std::uint16_t triIndex;  // 10 - VR confirmed
		std::uint16_t pad12;     // 12
		std::uint32_t pad14;     // 14
	};
}
