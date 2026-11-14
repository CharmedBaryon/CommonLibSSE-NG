#pragma once

#include "REL/Common.h"
#include "REX/W32/BASE.h"

namespace RE
{
	class BSThread
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSThread;
		inline static constexpr auto VTABLE = VTABLE_BSThread;

		virtual ~BSThread();  // 00

		// add
		virtual std::uint32_t ThreadProc();  // 01 - { return 0; }
		virtual void          Unk_02(void);  // 02 - { return; }

		// members
		REX::W32::CRITICAL_SECTION lock;           // 08
		void*                      thread;         // 30
		void*                      ownerThread;    // 38
		std::uint32_t              threadID;       // 40
		std::uint32_t              ownerThreadID;  // 44
		bool                       initialized;    // 48
		std::uint8_t               pad49;          // 49
		std::uint16_t              pad4A;          // 4A
		std::uint32_t              pad4C;          // 4C
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint8_t  unkVr50;  // 50 - written by the VR constructor
		std::uint8_t  padVr51;  // 51
		std::uint16_t padVr52;  // 52
		std::uint32_t padVr54;  // 54
#endif
	};
	STATIC_ASSERT_SIZE(BSThread, 0x50, 0x58);
}
