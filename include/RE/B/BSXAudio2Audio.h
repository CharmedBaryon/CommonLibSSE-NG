#pragma once

#include "RE/A/AudioDefs.h"
#include "RE/B/BSAudio.h"
#include "RE/C/CXAPOBase.h"
#include "RE/X/X3DAudio.h"

namespace RE
{
	struct IXAudio2;
	struct IXAudio2MasteringVoice;
	struct IXAudio2SubmixVoice;

	class BSXAudio2Audio : public BSAudio
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXAudio2Audio;

		~BSXAudio2Audio() override;  // 00

		// override (BSAudio)
		bool                     Init(REX::W32::HWND* a_wnd) override;                                                     // 01
		void                     Shutdown() override;                                                                      // 02
		BSGameSound*             GetGameSound(const BSResource::ID& a_resourceID) override;                                // 03
		void                     ReleaseGameSound(BSGameSound* a_gameSound) override;                                      // 04
		const BSFixedString&     GetSystemName() override;                                                                 // 05
		void                     ApplyReverbType(const BSIReverbType* a_reverbType, std::uint32_t a_tickLength) override;  // 07
		std::uint32_t            CreateMonitor() override;                                                                 // 08
		void                     ReleaseMonitor(std::uint32_t a_monitor) override;                                         // 09
		BSAudioMonitor::Receiver GetReceiver(std::uint32_t a_monitor) override;                                            // 0A

		// members
		WAVEFORMATEXTENSIBLE    outputFormat;     // 18
		std::uint32_t           unk44;            // 44
		std::uint64_t           unk48;            // 48
		IXAudio2*               XAudio;           // 50
		IXAudio2MasteringVoice* masteringVoice;   // 58
		X3DAUDIO_HANDLE         X3DAudioHandle;   // 60
		std::uint32_t           speakerChannels;  // 74
	};
	static_assert(sizeof(BSXAudio2Audio) == 0x78);

	class MonitorAPO : public CXAPOBase
	{
	public:
		inline static constexpr auto RTTI = RTTI___MonitorAPO;

		~MonitorAPO() override;  // 0E

		// override (CXAPOBase)
		std::int32_t LockForProcess(std::uint32_t a_inputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_inputLockedParameters, std::uint32_t a_outputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_outputLockedParameters) override;  // 08
		void         Process(std::uint32_t a_inputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS* a_InputProcessParameters, std::uint32_t a_outputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS* a_outputProcessParameters, BOOL a_isEnabled) override;       // 0A

		// members
		std::uint32_t numChannels;  // 30
		float         amplitude;    // 34
	};
	static_assert(sizeof(MonitorAPO) == 0x38);

	struct XAudio2Monitor
	{
	public:
		// members
		MonitorAPO*          monitorAPO;   // 00
		IXAudio2SubmixVoice* submixVoice;  // 08
	};
	static_assert(sizeof(XAudio2Monitor) == 0x10);
}
