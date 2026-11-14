#pragma once

#include "RE/X/XAPO.h"

namespace RE
{
#pragma pack(push, 8)

	class __declspec(novtable) CXAPOBase : public IXAPO
	{
	public:
		inline static constexpr auto RTTI = RTTI_CXAPOBase;

		// override (IXAPO)
		std::int32_t  QueryInterface(REX::W32::REFIID a_riid, void** a_interface) override;                                                                                                                                                                                         // 00
		std::uint32_t AddRef() override;                                                                                                                                                                                                                                            // 01
		std::uint32_t Release() override;                                                                                                                                                                                                                                           // 02
		std::int32_t  GetRegistrationProperties(XAPO_REGISTRATION_PROPERTIES** a_registrationProperties) override;                                                                                                                                                                  // 03
		std::int32_t  IsInputFormatSupported(const WAVEFORMATEX* a_outputFormat, const WAVEFORMATEX* a_requestedInputFormat, WAVEFORMATEX** a_supportedInputFormat) override;                                                                                                       // 04
		std::int32_t  IsOutputFormatSupported(const WAVEFORMATEX* a_inputFormat, const WAVEFORMATEX* a_requestedOutputFormat, WAVEFORMATEX** a_supportedOutputFormat) override;                                                                                                     // 05
		std::int32_t  Initialize(const void* a_data, std::uint32_t a_dataByteSize) override;                                                                                                                                                                                        // 06
		void          Reset() override;                                                                                                                                                                                                                                             // 07
		std::int32_t  LockForProcess(std::uint32_t a_inputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_inputLockedParameters, std::uint32_t a_outputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_outputLockedParameters) override;  // 08
		void          UnlockForProcess() override;                                                                                                                                                                                                                                  // 09
		void          Process(std::uint32_t a_inputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS* a_InputProcessParameters, std::uint32_t a_outputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS* a_outputProcessParameters, BOOL a_isEnabled) override;       // 0A
		std::uint32_t CalcInputFrames(std::uint32_t a_outputFrameCount) override;                                                                                                                                                                                                   // 0B
		std::uint32_t CalcOutputFrames(std::uint32_t a_inputFrameCount) override;                                                                                                                                                                                                   // 0C

		// add
		virtual std::int32_t ValidateFormatDefault(WAVEFORMATEX* a_format, BOOL a_overwrite);  // 0D
		virtual ~CXAPOBase();                                                                  // 0E

		[[nodiscard]] const XAPO_REGISTRATION_PROPERTIES* GetRegistrationPropertiesInternal() const noexcept { return registrationProperties; }
		[[nodiscard]] BOOL                                IsLocked() const noexcept { return isLocked; }

		// members
		const XAPO_REGISTRATION_PROPERTIES* registrationProperties;  // 08 - pointer to registration properties of the XAPO, set via constructor
		void*                               fnMatrixMixFunction;     // 10 - optimal matrix function pointer, used for thru processing
		float*                              matrixCoefficients;      // 18 - matrix coefficient table, used for thru processing
		std::uint32_t                       srcFormatType;           // 20 - input format type, used for thru processing
		BOOL                                isScalarMatrix;          // 24 - true if matrixCoefficients is diagonal matrix with all main diagonal entries equal, i.e. fnMatrixMixFunction only used for type conversion (no channel conversion), used for thru processing
		BOOL                                isLocked;                // 28 - true if XAPO locked via CXAPOBase.LockForProcess
		std::int32_t                        referenceCount;          // 2C - COM reference count, must be aligned for atomic operations
	};
	static_assert(sizeof(CXAPOBase) == 0x30);

#pragma pack(pop)
}
