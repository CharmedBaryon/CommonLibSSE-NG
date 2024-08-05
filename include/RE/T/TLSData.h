#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct TLSData
	{
		inline static constexpr uint32_t CACHED_EXTRA_DATA_SIZE = (static_cast<uint32_t>(ExtraDataType::kResourcesPreload) + 1);
		std::uint8_t                     unk000[0x10];                             // 000
		std::uint32_t                    stateCounter;                             // 010 - on GetExtraData(), this gets checked against the GlobalStateCounter, which is incremented every time extra data is changed or removed; if they're not equal, then the following cached extra data is zeroed-out and recached
		std::uint32_t                    pad014;                                   // 014
		ExtraDataList*                   cachedExtraDataList;                      // 018
		BSExtraData*                     cachedExtraData[CACHED_EXTRA_DATA_SIZE];  // 020 - ExtraData types up to kResourcesPreload (0xB5) are cached
		std::uint8_t                     unk5D0[0x30];                             // 5D0
		bool                             consoleMode;                              // 600
		std::uint8_t                     unk601[0x167];                            // 601
		std::uint32_t                    taskFlag;                                 // 768 -- unknown enum
																				   // ... many others ...
	private:
		KEEP_FOR_RE()
	};
	static_assert(offsetof(TLSData, consoleMode) == 0x600);
	static_assert(offsetof(TLSData, taskFlag) == 0x768);

	inline static TLSData* GetStaticTLSData()
	{
		REL::Relocation<std::uint32_t*> tlsIndex{ RELOCATION_ID(528600, 415542) };
		auto                            tlsDataArray = reinterpret_cast<TLSData**>(__readgsqword(0x58));
		return tlsDataArray[*tlsIndex];
	}
}
