#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTaskletData.h"

namespace RE
{
	class BSWin32TaskletData : public BSTaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32TaskletData;
		inline static constexpr auto VTABLE = VTABLE_BSWin32TaskletData;

		~BSWin32TaskletData() override;  // 00

		// members
		std::uint64_t          unk10;     // 10
		std::uint32_t          unk18;     // 18
		BSNonReentrantSpinLock taskLock;  // 1C
		BSWin32TaskletData*    unk20;     // 20
	};
	static_assert(sizeof(BSWin32TaskletData) == 0x28);
}
