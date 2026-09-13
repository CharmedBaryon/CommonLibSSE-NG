#pragma once

#include "RE/I/IUnknown.h"
#include "RE/X/XAudio2.h"

namespace RE
{
	struct IXAudio2EngineCallback;
	struct IXAudio2MasteringVoice;
	struct IXAudio2SourceVoice;
	struct IXAudio2SubmixVoice;
	struct IXAudio2VoiceCallback;
	using WAVEFORMATEX = struct tWAVEFORMATEX;

	struct __declspec(novtable) IXAudio2 : public IUnknown
	{
	public:
		virtual std::int32_t GetDeviceCount(std::uint32_t* a_count) = 0;  // 03

		virtual std::int32_t GetDeviceDetails(std::uint32_t a_index, XAUDIO2_DEVICE_DETAILS* a_details) = 0;  // 04

		virtual std::int32_t Initialize(
			std::uint32_t     a_flags,
			XAUDIO2_PROCESSOR a_XAudio2Processor = XAUDIO2_DEFAULT_PROCESSOR) = 0;  // 05

		virtual std::int32_t RegisterForCallbacks(IXAudio2EngineCallback* a_callback) = 0;  // 06

		virtual void UnregisterForCallbacks(IXAudio2EngineCallback* a_callback) = 0;  // 07

		virtual std::int32_t CreateSourceVoice(
			IXAudio2SourceVoice**       a_sourceVoice,
			const WAVEFORMATEX*         a_sourceFormat,
			std::uint32_t               a_flags = 0,
			float                       a_maxFrequencyRatio = XAUDIO2_DEFAULT_FREQ_RATIO,
			IXAudio2VoiceCallback*      a_callback = nullptr,
			const XAUDIO2_VOICE_SENDS*  a_sendList = nullptr,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) = 0;  // 08

		virtual std::int32_t CreateSubmixVoice(
			IXAudio2SubmixVoice**       a_submixVoice,
			std::uint32_t               a_inputChannels,
			std::uint32_t               a_inputSampleRate,
			std::uint32_t               a_flags = 0,
			std::uint32_t               a_processingStage = 0,
			const XAUDIO2_VOICE_SENDS*  a_sendList = nullptr,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) = 0;  // 09

		virtual std::int32_t CreateMasteringVoice(
			IXAudio2MasteringVoice**    a_masteringVoice,
			std::uint32_t               a_inputChannels = XAUDIO2_DEFAULT_CHANNELS,
			std::uint32_t               a_inputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
			std::uint32_t               a_flags = 0,
			std::uint32_t               a_deviceIndex = 0,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) = 0;  // 0A

		virtual std::int32_t StartEngine() = 0;  // 0B

		virtual void StopEngine() = 0;  // 0C

		virtual std::int32_t CommitChanges(std::uint32_t a_operationSet) = 0;  // 0D

		virtual void GetPerformanceData(XAUDIO2_PERFORMANCE_DATA* a_perfData) = 0;  // 0E

		virtual void SetDebugConfiguration(
			const XAUDIO2_DEBUG_CONFIGURATION* a_debugConfiguration,
			void*                              a_reserved = nullptr) = 0;  // 0F
	};
}
