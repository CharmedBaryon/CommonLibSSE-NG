#pragma once

#include "RE/A/AudioDefs.h"
#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	namespace BSResource
	{
		class StreamBase;
	}

	template <class T>
	class BSAudioDataSrc :
		public BSIntrusiveRefCounted  // 08
	{
	public:
		virtual ~BSAudioDataSrc();  // 00

		// members
		std::uint32_t           flags;   // 0C
		BSResource::StreamBase* stream;  // 10
	};

	class BSXAudio2DataSrc : public BSAudioDataSrc<BSXAudio2DataSrc>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXAudio2DataSrc;

		struct StreamPacket
		{
		public:
			// members
			std::uint32_t size;            // 00000
			std::uint32_t dataOffset;      // 00004
			std::uint32_t unk00008[0x40];  // 00008
			std::byte     data[0x10000];   // 00108
			std::uint64_t unk10108;        // 10108
			std::uint32_t unk10110;        // 10110
			std::uint32_t unk10114;        // 10114
			std::uint64_t unk10118;        // 10118
			std::uint64_t unk10120;        // 10120
			std::byte*    unk10128;        // 10128
		};
		static_assert(sizeof(StreamPacket) == 0x10130);

		~BSXAudio2DataSrc() override;  // 00

		// members
		std::uint64_t  unk18;                         // 18
		WAVEFORMATEX   format;                        // 20
		std::uint16_t  unk32;                         // 32
		std::uint32_t  unk34;                         // 34
		std::uint32_t  unk38;                         // 38
		std::uint32_t  unk3C;                         // 3C
		std::uint32_t  unk40;                         // 40
		std::uint32_t  unk44;                         // 44
		std::uint64_t  unk48;                         // 48
		std::uint64_t  unk50;                         // 50
		std::uint64_t  unk58;                         // 58
		std::uint32_t  unk60;                         // 60
		std::uint32_t  sourceBytes;                   // 64
		std::uint32_t  unk68;                         // 68
		std::uint32_t  unk6C;                         // 6C
		std::uint64_t  unk70;                         // 70
		std::uint32_t  unk78;                         // 78
		std::byte      pad7C[4];                      // 7C
		std::uint64_t  unk80;                         // 80
		std::uint32_t  unk88;                         // 88
		std::uint32_t  pad8C;                         // 8C
		std::uint64_t  unk90;                         // 90
		std::uint32_t  unk98;                         // 98
		std::uint32_t  unk9C;                         // 9C
		std::uint64_t  unkA0;                         // A0
		std::uint32_t* decodedPacketCumulativeBytes;  // A8
		std::uint32_t  audioBytes;                    // B0
		std::byte      padB4[4];                      // B4
		std::byte*     audioData;                     // B8
	};
	static_assert(sizeof(BSAudioDataSrc<BSXAudio2DataSrc>) == 0x18);
	static_assert(sizeof(BSXAudio2DataSrc) == 0xC0);
}
