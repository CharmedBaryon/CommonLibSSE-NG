#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class SandBoxActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_SandBoxActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_SandBoxActorPackageData;

		// Entry in the `entries` array below. Save/load (Func6_140714390) reads a RefHandle then three
		// uint32 fields per 0x10-byte element; Func7_140714630 checks handle==0 and state against 2/3.
		struct Entry
		{
			ObjectRefHandle handle;  // 00
			std::uint32_t   state;   // 04
			std::uint32_t   unk08;   // 08
			std::uint32_t   unk0C;   // 0C
		};
		static_assert(sizeof(Entry) == 0x10);

		~SandBoxActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// members
		std::uint32_t   unk08;     // 08
		std::uint32_t   unk0C;     // 0C - default 0xFFFFFFFF (index/id sentinel)
		std::uint32_t   unk10;     // 10
		ObjectRefHandle target14;  // 14
		std::uint64_t   unk18;     // 18
		std::uint32_t   unk20;     // 20 - default 0xFFFFFFFF (index/id sentinel)
		std::uint32_t   pad24;     // 24
		BSTArray<Entry> entries;   // 28
		std::uint32_t   unk40;     // 40
		std::uint32_t   unk44;     // 44 - default 1
		std::uint32_t   pad48;     // 48
		ObjectRefHandle target4C;  // 4C
		std::uint8_t    unk50;     // 50 - default 0x7F
		std::uint8_t    pad51[3];  // 51
		ObjectRefHandle target54;  // 54
		std::uint32_t   pad58;     // 58
		std::uint32_t   unk5C[2];  // 5C - misaligned uint64 write in the binary; split to avoid compiler padding
		std::uint32_t   unk64;     // 64
		std::uint32_t   unk68;     // 68 - default 0xFFFFFFFF (index/id sentinel)
		std::uint8_t    unk6C[7];  // 6C - default all 0x80 (sentinel array)
		std::uint8_t    pad73[5];  // 73
	};
	static_assert(sizeof(SandBoxActorPackageData) == 0x78);
}
