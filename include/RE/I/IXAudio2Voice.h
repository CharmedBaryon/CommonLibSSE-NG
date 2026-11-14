#pragma once

#include "RE/X/XAudio2.h"

namespace RE
{
	struct __declspec(novtable) IXAudio2Voice
	{
	public:
		virtual void GetVoiceDetails(XAUDIO2_VOICE_DETAILS* a_voiceDetails) = 0;  // 00

		virtual std::int32_t SetOutputVoices(const XAUDIO2_VOICE_SENDS* a_sendList) = 0;  // 01

		virtual std::int32_t SetEffectChain(const XAUDIO2_EFFECT_CHAIN* a_effectChain) = 0;  // 02

		virtual std::int32_t EnableEffect(
			std::uint32_t a_effectIndex,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 03

		virtual std::int32_t DisableEffect(
			std::uint32_t a_effectIndex,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 04

		virtual void GetEffectState(std::uint32_t a_effectIndex, BOOL* a_enabled) = 0;  // 05

		virtual std::int32_t SetEffectParameters(
			std::uint32_t a_effectIndex,
			const void*   a_parameters,
			std::uint32_t a_parametersByteSize,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 06

		virtual std::int32_t GetEffectParameters(
			std::uint32_t a_effectIndex,
			void*         a_parameters,
			std::uint32_t a_parametersByteSize) = 0;  // 07

		virtual std::int32_t SetFilterParameters(
			const XAUDIO2_FILTER_PARAMETERS* a_parameters,
			std::uint32_t                    a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 08

		virtual void GetFilterParameters(XAUDIO2_FILTER_PARAMETERS* a_parameters) = 0;  // 09

		virtual std::int32_t SetOutputFilterParameters(
			IXAudio2Voice*                   a_destinationVoice,
			const XAUDIO2_FILTER_PARAMETERS* a_parameters,
			std::uint32_t                    a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 0A

		virtual void GetOutputFilterParameters(
			IXAudio2Voice*             a_destinationVoice,
			XAUDIO2_FILTER_PARAMETERS* a_parameters) = 0;  // 0B

		virtual std::int32_t SetVolume(
			float         a_volume,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 0C

		virtual void GetVolume(float* a_volume) = 0;  // 0D

		virtual std::int32_t SetChannelVolumes(
			std::uint32_t a_channels, const float* a_volumes,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 0E

		virtual void GetChannelVolumes(std::uint32_t a_channels, float* a_volumes) = 0;  // 0F

		virtual std::int32_t SetOutputMatrix(
			IXAudio2Voice* a_destinationVoice,
			std::uint32_t a_sourceChannels, std::uint32_t a_destinationChannels,
			const float*  a_levelMatrix,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 10

		virtual void GetOutputMatrix(
			IXAudio2Voice* a_destinationVoice,
			std::uint32_t a_sourceChannels, std::uint32_t a_destinationChannels,
			float* a_levelMatrix) = 0;  // 11

		virtual void DestroyVoice() = 0;  // 12
	};

	struct __declspec(novtable) IXAudio2SourceVoice : public IXAudio2Voice
	{
	public:
		virtual std::int32_t Start(std::uint32_t a_flags = 0, std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 13

		virtual std::int32_t Stop(std::uint32_t a_flags = 0, std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 14

		virtual std::int32_t SubmitSourceBuffer(const XAUDIO2_BUFFER* a_buffer, const XAUDIO2_BUFFER_WMA* a_bufferWMA = nullptr) = 0;  // 15

		virtual std::int32_t FlushSourceBuffers() = 0;  // 16

		virtual std::int32_t Discontinuity() = 0;  // 17

		virtual std::int32_t ExitLoop(std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 18

		virtual void GetState(XAUDIO2_VOICE_STATE* a_voiceState) = 0;  // 19

		virtual std::int32_t SetFrequencyRatio(
			float         a_ratio,
			std::uint32_t a_operationSet = XAUDIO2_COMMIT_NOW) = 0;  // 1A

		virtual void GetFrequencyRatio(float* a_ratio) = 0;  // 1B

		virtual std::int32_t SetSourceSampleRate(std::uint32_t a_newSourceSampleRate) = 0;  // 1C
	};

	struct __declspec(novtable) IXAudio2SubmixVoice : public IXAudio2Voice
	{
	public:
	};

	struct __declspec(novtable) IXAudio2MasteringVoice : public IXAudio2Voice
	{
	public:
	};
}
