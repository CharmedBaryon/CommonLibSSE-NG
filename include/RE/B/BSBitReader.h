#pragma once

namespace RE::BSScript
{
	// Instruction reader, reads a stream of bits for an instruction stream
	struct BSBitReader
	{
		explicit BSBitReader(const void* instructionDataStart, const std::uint32_t currentOffset)
		{
			seek(instructionDataStart, currentOffset);
		}
		/**
		 * Acquire the current position, represented as a relative offset from the start of the instruction stream
		 * @param instructionDataStart The start of the instruction stream
		 * @return A relative offset from the start of the stream to the current position
		 */
		std::uint32_t getBitPosition(const void* instructionDataStart) const;

		/**
		 * Seek to a given position in the instruction stream
		 * @param instructionStart The start of the instruction stream
		 * @param offset The relative offset from the start of the stream to seek
		 */
		void seek(const void* instructionStart, std::uint32_t offset);

		/**
		 * Read X bits into the stream, moving the reader head the same amount of bits ("consuming" the bits)
		 * @example readRawBits(2) returns a 2-bit value inside the 64-bit integer, equal to the 2-bit contents read
		 * @example readRawBits(10) returns a 10-bit value inside the 64-bit integer, equal to the 10-bit contents read
		 * @param count Amount of bits to read (MUST be less than 64)
		 * @return unsigned 64-bit integer containing the bits read
		 */
		std::uint64_t readRawBits(std::size_t count);

	private:
		std::uint64_t const* word{ nullptr };  // 00 - Current 64-bit value the reader is positioned on
		std::uint64_t        bitOffset{ 0 };   // 08 - Offset within the 64-bit value - Should always be 0-63 (likely uint8_t type)
	};

	static_assert(sizeof(BSBitReader) == 0x10);
}
