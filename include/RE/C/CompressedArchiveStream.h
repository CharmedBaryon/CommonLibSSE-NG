#pragma once

#include "RE/A/ArchiveStream.h"

namespace RE
{
	namespace BSResource
	{
		class CompressedArchiveStream : public ArchiveStream
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__CompressedArchiveStream;
			inline static constexpr auto VTABLE = VTABLE_BSResource__CompressedArchiveStream;

			struct Data
			{
				std::uint64_t unk00;                  // 00
				std::uint32_t compressedEndOffset;    // 08
				std::uint32_t decompressedOffset;     // 0C
				std::uint32_t decompressedEndOffset;  // 10
				std::uint32_t decompressedSize;       // 14
				void*         decompressedBuffer;     // 18
				std::uint64_t unk20;                  // 20
			};
			static_assert(sizeof(Data) == 0x28);

			~CompressedArchiveStream() override;  // 00

			// override (ArchiveStream)
			ErrorCode     DoOpen() override;                                                                        // 01
			void          DoClose() override;                                                                       // 02
			void          DoClone(BSTSmartPointer<Stream>& a_out) const override;                                   // 05
			ErrorCode     DoRead(void* a_buffer, std::uint64_t a_toRead, std::uint64_t& a_read) const override;     // 06
			ErrorCode     DoSeek(std::uint64_t a_toSeek, SeekMode a_mode, std::uint64_t& a_sought) const override;  // 08
			ErrorCode     DoCreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const override;                  // 0B
			std::uint32_t DoGetSize() const override;                                                               // 0C

			// members
			Data*         data;       // 28
			std::uint32_t totalRead;  // 30
			std::uint32_t unk34;      // 34
		};
#ifdef ENABLE_SKYRIM_AE
		static_assert(sizeof(CompressedArchiveStream) == 0x40);
#else
		static_assert(sizeof(CompressedArchiveStream) == 0x38);
#endif
	}
}
