#pragma once

#include "RE/B/BSReloadShaderI.h"
#include "RE/B/BSShader.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSComputeShader : public NiRefObject, public BSReloadShaderI
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSComputeShader;
		inline static constexpr auto VTABLE = VTABLE_BSComputeShader;

		~BSComputeShader() override;  // 00

		// override (BSReloadShaderI)
		void ReloadShaders(void* a_stream) override;  // 00

		// add
		virtual void Dispatch(uint32_t a_techniqueId, uint32_t a_threadGroupCountX, uint32_t a_threadGroupCountY, uint32_t a_threadGroupCountZ);  // 02
#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual void FakeDispatch(uint32_t a_techniqueId, uint32_t a_threadGroupCountX, uint32_t a_threadGroupCountY, uint32_t a_threadGroupCountZ);  // 03, VR Only. Instead of compiling it has a null function
#endif

		// members
		const char*                                      name;        // 18
		BSTHashMap<uint32_t, BSGraphics::ComputeShader*> shadersMap;  // 20
	};
	static_assert(sizeof(BSComputeShader) == 0x50);
}
