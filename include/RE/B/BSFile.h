#pragma once

#include "RE/B/BSString.h"
#include "RE/N/NiFile.h"

#include "REX/W32/BASE.h"

namespace RE
{
	class BSFile : public NiFile
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFile;
		inline static constexpr auto VTABLE = VTABLE_BSFile;

		~BSFile() override;  // 00

		// override (NiFile)
		void          seek(std::int32_t a_numBytes) override;                     // 02
		void          set_endian_swap(bool a_doSwap) override;                    // 05
		void          seek(std::int32_t a_offset, std::int32_t a_from) override;  // 06
		std::uint32_t size() const override;                                      // 07

		// add
		virtual bool          Open(std::uint64_t a_unused, bool a_textMode);                                 // 08
		virtual bool          OpenFromFile(std::FILE* a_file);                                               // 09
		virtual std::uint32_t UpdateFileSize();                                                              // 0A - re-measures the file and caches it in fileSize
		virtual std::uint32_t ReadString(BSString& a_out, std::uint32_t a_maxLen);                           // 0B
		virtual std::uint32_t ReadWString(void* a_out, std::uint32_t a_maxLen);                              // 0C - a_out is a wide string object
		virtual std::uint32_t ReadUntil(char* a_buffer, std::uint32_t a_maxLen, std::uint16_t a_delimiter);  // 0D
		virtual void          WriteString(const BSString& a_str, bool a_includeNull);                        // 0E
		virtual std::uint32_t WriteWString(const void* a_str, bool a_includeNull);                           // 0F - a_str is a wide string object
		virtual bool          FileExists();                                                                  // 10 - _access(fileName, 0) != -1
		virtual std::uint32_t ReadBytes(void* a_buffer, std::uint32_t a_bytes);                              // 11
		virtual std::uint32_t WriteBytes(const void* a_buffer, std::uint32_t a_bytes);                       // 12

		// members
		bool          useAuxBuffer;                  // 048
		std::uint8_t  pad049;                        // 049
		std::uint16_t pad04A;                        // 04A
		std::uint32_t pad04C;                        // 04C
		char*         auxBuffer;                     // 050
		std::int32_t  auxTrueFilePos;                // 058
		std::uint32_t auxBufferMinIndex;             // 05C
		std::uint32_t auxBufferMaxIndex;             // 060
		char          fileName[REX::W32::MAX_PATH];  // 064
		std::uint32_t result;                        // 168
		std::uint32_t ioSize;                        // 16C
		std::uint32_t trueFilePos;                   // 170
		std::uint32_t fileSize;                      // 174
		bool          virtualAlloc;                  // 178
		std::uint8_t  unk179;                        // 179
		std::uint16_t unk17A;                        // 17A
	};
	static_assert(sizeof(BSFile) == 0x180);
}
