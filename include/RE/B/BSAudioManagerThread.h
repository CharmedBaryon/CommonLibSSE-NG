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

		void*         semaphore1;  // 50
		void*         semaphore2;  // 58
		bool          unk60;       // 60
		bool          unk61;       // 61
		std::byte     pad62[2];    // 62
		std::uint32_t sleepTime;   // 64
	};
	static_assert(sizeof(BSAudioManagerThread) == 0x68);
}
