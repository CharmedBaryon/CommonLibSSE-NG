#pragma once

#include "RE/M/MemoryManager.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSAudioListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAudioListener;

		virtual ~BSAudioListener();  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
		virtual void Unk_03(void);      // 03
		virtual void Unk_04(void) = 0;  // 04
		virtual void Unk_05(void);      // 05

		TES_HEAP_REDEFINE_NEW();

		// members
		NiPoint3      listenerPosition;  // 08
		std::uint32_t unk14;             // 14
		std::uint64_t unk18;             // 18
		std::uint64_t unk20;             // 20
		std::uint64_t unk28;             // 28
		std::uint64_t unk30;             // 30
		std::uint64_t unk38;             // 38
	};
	static_assert(sizeof(BSAudioListener) == 0x40);
}
