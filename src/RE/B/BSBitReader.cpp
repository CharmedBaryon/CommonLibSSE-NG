#include "RE/B/BSBitReader.h"

constexpr long long bitOffsetMask = 0x3F;  // 0b111111 (63)
namespace RE::BSScript
{
	std::uint32_t BSBitReader::getBitPosition(const void* instructionDataStart) const
	{
		const auto     wordPosition = (reinterpret_cast<std::uintptr_t>(word) - reinterpret_cast<std::uintptr_t>(instructionDataStart)) * 8;
		const uint32_t instructionBitPosition = static_cast<uint32_t>(bitOffset + wordPosition);
		return instructionBitPosition;
	}

	void BSBitReader::seek(const void* instructionStart, const std::uint32_t offset)
	{
		const auto wordOffset = offset >> 6;
		const auto instructionWordPointer = ((std::uintptr_t)instructionStart) + (wordOffset * 8);

		word = reinterpret_cast<uint64_t const*>(instructionWordPointer);
		bitOffset = offset & 0x3F;

		// Seek to a given offset, should return that offset when fetched later
		assert(getBitPosition(instructionStart) == offset);
	}

	std::uint64_t BSBitReader::readRawBits(const std::size_t count)
	{
		assert(count < 0x40);
		assert(bitOffset < 0x40);
		std::uint64_t       result{ 0 };
		const std::uint64_t bitMask = (std::uint64_t{ 1 } << count) - 1;

		// Ingest all bits for the current word, truncating bits behind the bitOffset (reader head)
		result = *word >> (bitOffset & bitOffsetMask);
		if (bitOffset + count > 0x40) {
			// Read crosses into the next word boundary, gather remaining bits from the next word
			result += (word[1] << ((0x40 - bitOffset) & bitOffsetMask));
		}

		// Finally, chop off all unwanted bits
		result &= bitMask;

		// Update reader head position
		// Move word boundary in 64-bit increments of the bitOffset
		word = &word[(bitOffset + count) >> 6];
		// Move bitOffset by count, rolling over from 64
		bitOffset = (bitOffset + count) & bitOffsetMask;

		return result;
	}
}
