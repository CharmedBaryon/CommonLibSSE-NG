#pragma once

#include "RE/B/BSAudioMonitor.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	namespace BSResource
	{
		struct ID;
	}

	class BSGameSound;
	class BSIReverbType;
	class BSAudioListener;

	class BSAudio
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAudio;

		virtual ~BSAudio();  // 00

		// add
		virtual bool                     Init(REX::W32::HWND* a_wnd);                                                     // 01
		virtual void                     Shutdown();                                                                      // 02
		virtual BSGameSound*             GetGameSound(const BSResource::ID& a_resourceID) = 0;                            // 03
		virtual void                     ReleaseGameSound(BSGameSound* a_gameSound) = 0;                                  // 04
		virtual const BSFixedString&     GetSystemName() = 0;                                                             // 05
		virtual void                     PostGameSoundUpdates();                                                          // 06
		virtual void                     ApplyReverbType(const BSIReverbType* a_reverbType, std::uint32_t a_tickLength);  // 07
		virtual std::uint32_t            CreateMonitor();                                                                 // 08
		virtual void                     ReleaseMonitor(std::uint32_t a_monitor);                                         // 09
		virtual BSAudioMonitor::Receiver GetReceiver(std::uint32_t a_monitor);                                            // 0A

		// members
		std::uint64_t    unk08;          // 08
		BSAudioListener* audioListener;  // 10
	};
	static_assert(sizeof(BSAudio) == 0x18);
}
