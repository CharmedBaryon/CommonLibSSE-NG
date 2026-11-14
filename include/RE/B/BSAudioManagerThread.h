#pragma once

#include "RE/B/BSThread.h"

namespace RE
{
	class BSAudioManagerThread : public BSThread
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAudioManagerThread;
		inline static constexpr auto VTABLE = VTABLE_BSAudioManagerThread;

		~BSAudioManagerThread() override;  // 00

		// override (BSThread)
		std::uint32_t ThreadProc() override;  // 01

		// members

		void*         semaphore1;  // 50, 58
		void*         semaphore2;  // 58, 60
		bool          unk60;       // 60, 68
		bool          unk61;       // 61, 69
		std::byte     pad62[2];    // 62, 6A
		std::uint32_t sleepTime;   // 64, 6C
	};
	STATIC_ASSERT_SIZE(BSAudioManagerThread, 0x68, 0x70);
}
