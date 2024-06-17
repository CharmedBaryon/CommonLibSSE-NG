#pragma once

#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GMutex.h"
#include "RE/G/GRefCountBase.h"

namespace RE
{
	class GFxLoadUpdateSync : public GRefCountBase<GFxLoadUpdateSync, GFxStatMovieData::kGFxStatMD_Other_Mem>
	{
	public:
		~GFxLoadUpdateSync() override;  // 00

		// members
		GMutex mutex;  // 10
		void*  unk38;  // 38
		void*  unk40;  // 40
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxLoadUpdateSync) == 0x48);
}
