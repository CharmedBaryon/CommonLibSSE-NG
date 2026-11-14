#pragma once

#include "RE/A/AudioDefs.h"
#include "RE/I/IUnknown.h"

namespace RE
{
	using BOOL = std::int32_t;

	inline constexpr auto XAPO_REGISTRATION_STRING_LENGTH = 256;

#pragma pack(push, 1)

	struct XAPO_REGISTRATION_PROPERTIES
	{
		REX::W32::CLSID clsid;                                           // 000
		wchar_t         friendlyName[XAPO_REGISTRATION_STRING_LENGTH];   // 010
		wchar_t         copyrightInfo[XAPO_REGISTRATION_STRING_LENGTH];  // 210
		std::uint32_t   majorVersion;                                    // 410
		std::uint32_t   minorVersion;                                    // 414
		std::uint32_t   flags;                                           // 418
		std::uint32_t   minInputBufferCount;                             // 41C
		std::uint32_t   maxInputBufferCount;                             // 420
		std::uint32_t   minOutputBufferCount;                            // 424
		std::uint32_t   maxOutputBufferCount;                            // 428
	};
	static_assert(sizeof(XAPO_REGISTRATION_PROPERTIES) == 0x42C);

	struct XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS
	{
		const WAVEFORMATEX* format;         // 00
		std::uint32_t       maxFrameCount;  // 08
	};
	static_assert(sizeof(XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS) == 0xC);

	enum class XAPO_BUFFER_FLAGS
	{
		XAPO_BUFFER_SILENT,
		XAPO_BUFFER_VALID,
	};

	struct XAPO_PROCESS_BUFFER_PARAMETERS
	{
		void*             buffer;           // 00
		XAPO_BUFFER_FLAGS bufferFlags;      // 08
		std::uint32_t     validFrameCount;  // 0C
	};
	static_assert(sizeof(XAPO_PROCESS_BUFFER_PARAMETERS) == 0x10);

	struct __declspec(novtable) IXAPO : public IUnknown
	{
	public:
		inline static constexpr auto RTTI = RTTI_IXAPO;

		// add
		virtual std::int32_t  GetRegistrationProperties(XAPO_REGISTRATION_PROPERTIES** a_registrationProperties) = 0;                                                                                                                                                                  // 03
		virtual std::int32_t  IsInputFormatSupported(const WAVEFORMATEX* a_outputFormat, const WAVEFORMATEX* a_requestedInputFormat, WAVEFORMATEX** a_supportedInputFormat) = 0;                                                                                                       // 04
		virtual std::int32_t  IsOutputFormatSupported(const WAVEFORMATEX* a_inputFormat, const WAVEFORMATEX* a_requestedOutputFormat, WAVEFORMATEX** a_supportedOutputFormat) = 0;                                                                                                     // 05
		virtual std::int32_t  Initialize(const void* a_data, std::uint32_t a_dataByteSize) = 0;                                                                                                                                                                                        // 06
		virtual void          Reset() = 0;                                                                                                                                                                                                                                             // 07
		virtual std::int32_t  LockForProcess(std::uint32_t a_inputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_inputLockedParameters, std::uint32_t a_outputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_outputLockedParameters) = 0;  // 08
		virtual void          UnlockForProcess() = 0;                                                                                                                                                                                                                                  // 09
		virtual void          Process(std::uint32_t a_inputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS* a_InputProcessParameters, std::uint32_t a_outputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS* a_outputProcessParameters, BOOL a_isEnabled) = 0;       // 0A
		virtual std::uint32_t CalcInputFrames(std::uint32_t a_outputFrameCount) = 0;                                                                                                                                                                                                   // 0B
		virtual std::uint32_t CalcOutputFrames(std::uint32_t a_inputFrameCount) = 0;                                                                                                                                                                                                   // 0C
	};
	static_assert(sizeof(IXAPO) == 0x8);

#pragma pack(pop)
}
