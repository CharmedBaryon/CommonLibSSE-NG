#pragma once

#include "RE/G/GNewOverrideBase.h"

namespace RE
{
	template <std::uint32_t STAT>
	class GRefCountBaseGC : public GNewOverrideBase<STAT>
	{
	public:
		enum
		{
			kStatType = STAT
		};

		// add
		virtual void Unk_00(void);  // 00
		virtual void Unk_01(void);  // 01 - pure

		virtual ~GRefCountBaseGC();  // 02

		// members
		void*         unk08;     // 08
		std::uint32_t refCount;  // 10
		std::uint32_t pad14;     // 14
		std::uint64_t unk18;     // 18 - union
	private:
		KEEP_FOR_RE()
	};
	// size == 0x20
}
