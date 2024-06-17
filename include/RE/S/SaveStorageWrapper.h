#pragma once

#include "RE/B/BSMemStorage.h"

namespace RE
{
	class SaveStorageWrapper : public BSMemStorage
	{
	public:
		inline static constexpr auto RTTI = RTTI_SaveStorageWrapper;
		inline static constexpr auto VTABLE = VTABLE_SaveStorageWrapper;

		~SaveStorageWrapper() override;  // 00

		// override BSMemStorage
		std::size_t              GetSize() const override;                                                       // 01
		std::size_t              GetPosition() const override;                                                   // 02
		BSStorageDefs::ErrorCode Seek(std::size_t a_offset, BSStorageDefs::SeekMode a_seekMode) const override;  // 03
		BSStorageDefs::ErrorCode Read(std::size_t a_numBytes, std::byte* a_bytes) const override;                // 04
		BSStorageDefs::ErrorCode Write(std::size_t a_numBytes, const std::byte* a_bytes) override;               // 05

		// members
		std::uint64_t unk30;  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SaveStorageWrapper) == 0x38);
}
