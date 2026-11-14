#pragma once

#include "RE/B/BSCullingProcess.h"
#include "REL/Relocation.h"

namespace RE
{
	class BSGeometryListCullingProcess : public BSCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGeometryListCullingProcess;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGeometryListCullingProcess;
		inline static constexpr auto VTABLE = VTABLE_BSGeometryListCullingProcess;

		[[nodiscard]] static BSTArray<BSGeometryListCullingProcess*>& GetGlobalCullingProcesses() noexcept
		{
			static REL::Relocation<BSTArray<BSGeometryListCullingProcess*>*> processes{ RELOCATION_ID(528077, 415022) };
			return *processes;
		}

		// override (BSCullingProcess)
		const NiRTTI* GetRTTI() const override;  // 00

		~BSGeometryListCullingProcess() override;  // 15

		void AppendNonAccum(BSGeometry& a_geometry, std::int32_t a_alphaGroupIndex) override;  // 19

		// members
		std::uint32_t unk301F8;                // 301F8 - nonzero makes the SE/AE AppendNonAccum call shaderProperty->SetLightState
		bool          occlusionCullingActive;  // 301FC - only the VR binary touches this; padding on SE/AE
		bool          forceDrawAll;            // 301FD - only the VR binary touches this; padding on SE/AE
		std::uint8_t  pad301FE[2];             // 301FE
	};
	static_assert(sizeof(BSGeometryListCullingProcess) == 0x30200);
}
