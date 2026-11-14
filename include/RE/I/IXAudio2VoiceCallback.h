#pragma once

namespace RE
{
	struct __declspec(novtable) IXAudio2VoiceCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI_IXAudio2VoiceCallback;

		// add
		virtual void OnVoiceProcessingPassStart(std::uint32_t a_bytesRequired) = 0;  // 00
		virtual void OnVoiceProcessingPassEnd() = 0;                                 // 01
		virtual void OnStreamEnd() = 0;                                              // 02
		virtual void OnBufferStart(void* a_bufferContext) = 0;                       // 03
		virtual void OnBufferEnd(void* a_bufferContext) = 0;                         // 04
		virtual void OnLoopEnd(void* a_bufferContext) = 0;                           // 05
		virtual void OnVoiceError(void* a_bufferContext, std::int32_t a_error) = 0;  // 06
	};
}
