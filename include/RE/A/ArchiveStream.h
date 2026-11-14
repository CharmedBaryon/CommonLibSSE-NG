#pragma once

#include "RE/S/Stream.h"

namespace RE
{
	namespace BSResource
	{
		class ArchiveStream : public Stream
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__ArchiveStream;
			inline static constexpr auto VTABLE = VTABLE_BSResource__ArchiveStream;

			~ArchiveStream() override;  // 00

			// override (Stream)
			ErrorCode                   DoOpen() override;                                                                                // 01
			void                        DoClose() override;                                                                               // 02
			[[nodiscard]] std::uint64_t DoGetKey() const override;                                                                        // 03
			void                        DoClone(BSTSmartPointer<Stream>& a_out) const override;                                           // 05
			ErrorCode                   DoRead(void* a_buffer, std::uint64_t a_toRead, std::uint64_t& a_read) const override;             // 06
			ErrorCode                   DoWrite(const void* a_buffer, std::uint64_t a_toWrite, std::uint64_t& a_written) const override;  // 07
			ErrorCode                   DoSeek(std::uint64_t a_toSeek, SeekMode a_mode, std::uint64_t& a_sought) const override;          // 08
			bool                        DoGetName(BSFixedString& a_dst) const override;                                                   // 0A
			ErrorCode                   DoCreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const override;                          // 0B

			// add
			virtual std::uint32_t DoGetSize() const;  // 0C

			// members
			void*         source;         // 10
			std::uint32_t startOffset;    // 18
			std::uint32_t currentOffset;  // 1C
			BSFixedString name;           // 20
		};
#ifdef ENABLE_SKYRIM_AE
		static_assert(sizeof(ArchiveStream) == 0x30);
#else
		static_assert(sizeof(ArchiveStream) == 0x28);
#endif
	}
}
