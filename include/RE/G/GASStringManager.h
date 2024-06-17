#pragma once

#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GRefCountBase.h"
#include "RE/G/GStringHash.h"

namespace RE
{
	struct GASString
	{
	public:
		const char*   str;       // 00
		GASString*    next;      // 08
		std::int32_t  refCount;  // 10
		std::int32_t  hash;      // 14
		std::uint32_t size;      // 18
		std::uint32_t pad1C;     // 1C
	};

	class GASStringManager : public GRefCountBase<GASStringManager, GFxStatMovieViews::kGFxStatMV_ActionScript_Mem>
	{
	public:
		~GASStringManager() override;  // 00

		// members
		GStringHash<GASString> unk10;  // 10
		GMemoryHeap*           heap;   // 18
		std::uint64_t          unk20;  // 20
		void*                  unk28;  // 28
		std::uint64_t          unk30;  // 30
		std::uint64_t          unk38;  // 38
		std::uint64_t          unk40;  // 40
		std::uint64_t          unk48;  // 48
		std::uint64_t          unk50;  // 50
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASStringManager) == 0x58);
}
