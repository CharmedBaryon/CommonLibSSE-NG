#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	class BSSoundInfo
	{
	public:
		TES_HEAP_REDEFINE_NEW();

		// members
		std::uint32_t id;                            // 00
		float         frequency;                     // 04
		float         volume;                        // 08
		std::uint32_t type;                          // 0C
		std::uint32_t duration;                      // 10
		bool          isPlaying;                     // 14
		std::byte     pad15[3];                      // 15
		std::uint32_t playbackPositionMilliseconds;  // 18
		std::byte     pad1C[4];                      // 1C
		BSSoundInfo*  next;                          // 20
	};
	static_assert(sizeof(BSSoundInfo) == 0x28);

	struct FreeSoundInfoStack
	{
	public:
		// members
		BSSoundInfo* top;  // 0
	};
	static_assert(sizeof(FreeSoundInfoStack) == 0x8);
}
