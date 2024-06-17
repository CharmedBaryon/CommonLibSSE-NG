#pragma once

#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GRefCountBase.h"

namespace RE
{
	class GASActionBufferData :
		public GRefCountBase<GASActionBufferData, GFxStatMovieData::kGFxStatMD_ActionOps_Mem>
	{
	public:
		~GASActionBufferData() override;  // 00

		// members
		void*         buffer;  // 10
		std::uint64_t size;    // 18
		std::uint32_t unk20;   // 20
		std::uint32_t pad24;   // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASActionBufferData) == 0x28);
}
