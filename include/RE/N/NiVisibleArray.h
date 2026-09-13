#pragma once

namespace RE
{
	class BSGeometry;

	class NiVisibleArray
	{
	public:
		BSGeometry**  array;          // 00
		std::uint32_t currentSize;    // 08
		std::uint32_t allocatedSize;  // 0C
		std::uint32_t growBy;         // 10
	};
}