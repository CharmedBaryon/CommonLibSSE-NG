#pragma once

#include "RE/G/GASStringBuiltinManager.h"
#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GRefCountBaseNTS.h"

namespace RE
{
	class GASGlobalObject;
	class GFxMovieRoot;

	class GASGlobalContext :
		public GRefCountBaseNTS<GASGlobalContext, GFxStatMovieViews::kGFxStatMV_ActionScript_Mem>,  // 000
		public GASStringBuiltinManager                                                              // 010
	{
	public:
		~GASGlobalContext() override;

		// members
		std::uint64_t    unk500;        // 500
		std::uint64_t    unk508;        // 508
		std::uint64_t    unk510;        // 510
		GFxMovieRoot*    unk518;        // 518
		GMemoryHeap*     heap;          // 520
		std::uint64_t    unk528;        // 528
		std::uint64_t    unk530;        // 530
		std::uint64_t    unk538;        // 538
		std::uint64_t    unk540;        // 540
		std::uint64_t    unk548;        // 548
		GASGlobalObject* globalObject;  // 550
		std::uint64_t    unk558;        // 558
		std::uint64_t    unk560;        // 560
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASGlobalContext) == 0x568);
}
