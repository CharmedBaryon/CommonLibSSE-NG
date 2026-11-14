#pragma once

namespace RE
{
#pragma pack(push, 1)

	struct tWAVEFORMATEX
	{
		std::uint16_t wFormatTag;       // 00 - Integer identifier of the format
		std::uint16_t nChannels;        // 02 - Number of audio channels
		std::uint32_t nSamplesPerSec;   // 04 - Audio sample rate
		std::uint32_t nAvgBytesPerSec;  // 08 - Bytes per second (possibly approximate)
		std::uint16_t nBlockAlign;      // 0C - Size in bytes of a sample block (all channels)
		std::uint16_t wBitsPerSample;   // 0E - Size in bits of a single per-channel sample
		std::uint16_t cbSize;           // 10 - Bytes of extra data appended to this struct
	};
	static_assert(sizeof(tWAVEFORMATEX) == 0x12);
	using WAVEFORMATEX = tWAVEFORMATEX;

	struct WAVEFORMATEXTENSIBLE
	{
		WAVEFORMATEX Format;  // 00 - Base WAVEFORMATEX data
		union                 // 12
		{
			std::uint16_t wValidBitsPerSample;  // Valid bits in each sample container
			std::uint16_t wSamplesPerBlock;     // Samples per block of audio data; valid if wBitsPerSample=0 (but rarely used).
			std::uint16_t wReserved;            // Zero if neither case above applies.
		} Samples;
		std::uint32_t  dwChannelMask;  // 14 - Positions of the audio channels
		REX::W32::GUID SubFormat;      // 18 - Format identifier GUID
	};

#pragma pack(pop)
}
