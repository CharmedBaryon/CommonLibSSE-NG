#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/M/MoviePlayer.h"

namespace RE
{
	class InputEvent;
	struct BSMusicEvent;

	class BGSMoviePlayer :
		public MoviePlayer,                  // 00
		public BSTEventSink<InputEvent*>,    // 58
		public BSTEventSource<BSMusicEvent>  // 60
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSMoviePlayer;
		inline static constexpr auto VTABLE = VTABLE_BGSMoviePlayer;

		~BGSMoviePlayer() override;  // 00

		// override (MoviePlayer)
		void          MuteAudio() override;              // 01
		void          UnmuteAudio() override;            // 02
		void          PauseMusic() override;             // 03
		void          UnPauseMusic() override;           // 04
		void          SuspendAudioThread() override;     // 05 - { return; }
		void          ResumeAudioThread() override;      // 06 - { return; }
		void          LockRenderer() override;           // 07
		void          UnlockRenderer() override;         // 08
		float         GetScreenWidth() override;         // 09
		float         GetScreenHeight() override;        // 0A
		bool          IsRendererInsideFrame() override;  // 0B
		std::uint64_t GetMainThreadID() override;        // 0C
		void          Unk_0D(void) override;             // 0D

		// members
		std::uint8_t  unkB8;  // B8
		std::uint8_t  padB9;  // B9
		std::uint16_t padBA;  // BA
		std::uint32_t padBC;  // BC
	};
	static_assert(sizeof(BGSMoviePlayer) == 0xC0);
}
