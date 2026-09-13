#pragma once

namespace RE
{
	struct __declspec(novtable) IXAudio2EngineCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI_IXAudio2EngineCallback;

		// add
		virtual void OnProcessingPassStart() = 0;                // 00
		virtual void OnProcessingPassEnd() = 0;                  // 01
		virtual void OnCriticalError(std::int32_t a_error) = 0;  // 02
	};
}
