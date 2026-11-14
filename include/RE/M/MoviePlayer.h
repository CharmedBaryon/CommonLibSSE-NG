#pragma once

#include "RE/B/BSAtomic.h"

namespace RE
{
	class Movie;

	class MoviePlayer
	{
	public:
		inline static constexpr auto RTTI = RTTI_MoviePlayer;
		inline static constexpr auto VTABLE = VTABLE_MoviePlayer;

		virtual ~MoviePlayer();  // 00

		// add
		virtual void          MuteAudio() = 0;              // 01
		virtual void          UnmuteAudio() = 0;            // 02
		virtual void          PauseMusic() = 0;             // 03
		virtual void          UnPauseMusic() = 0;           // 04
		virtual void          SuspendAudioThread() = 0;     // 05
		virtual void          ResumeAudioThread() = 0;      // 06
		virtual void          LockRenderer() = 0;           // 07
		virtual void          UnlockRenderer() = 0;         // 08
		virtual float         GetScreenWidth() = 0;         // 09
		virtual float         GetScreenHeight() = 0;        // 0A
		virtual bool          IsRendererInsideFrame() = 0;  // 0B
		virtual std::uint64_t GetMainThreadID() = 0;        // 0C
		virtual void          Unk_0D(void);                 // 0D

		// members
		void*         movieLoadingThreadHandle;       // 08
		void*         sequenceThreadHandle;           // 10
		Movie*        currentMovie;                   // 18
		Movie*        pausedMovie;                    // 20
		Movie*        threadLoadedMovie;              // 28
		bool          useThreadLoadedMovie;           // 30
		std::uint8_t  pad31;                          // 31
		std::uint16_t pad32;                          // 32
		std::uint32_t pad34;                          // 34
		void*         threadLoadCallback;             // 38
		bool          waitingForSequenceToEnd;        // 40
		bool          stopSequence;                   // 41
		bool          letterBoxedSequence;            // 42
		bool          loop;                           // 43
		std::int32_t  currentSequenceThreadPriority;  // 44
		BSSemaphore   openBinkSemaphore;              // 48
		bool          binkOpenSignaled;               // 50
		bool          streamingInstallComplete;       // 51
		std::uint16_t pad52;                          // 52
		std::uint32_t pad54;                          // 54
	};
	static_assert(sizeof(MoviePlayer) == 0x58);
}
