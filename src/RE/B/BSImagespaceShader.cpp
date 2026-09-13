#include "RE/B/BSImagespaceShader.h"

namespace RE
{
	void BSImagespaceShader::DispatchCopySubRegion()
	{
		using func_t = decltype(&BSImagespaceShader::DispatchCopySubRegion);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100496, 107217) };
		return func(this);
	}

	RENDER_TARGET BSImagespaceShader::RenderSSAO(RENDER_TARGET a_inputRenderTarget, RENDER_TARGET a_outputRenderTarget)
	{
		using func_t = decltype(&BSImagespaceShader::RenderSSAO);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100520, 107245) };
		return func(this, a_inputRenderTarget, a_outputRenderTarget);
	}

	RENDER_TARGET BSImagespaceShader::RenderSnowSSS(RENDER_TARGET a_inputRenderTarget, RENDER_TARGET a_outputRenderTarget)
	{
		using func_t = decltype(&BSImagespaceShader::RenderSnowSSS);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100537, 107267) };
		return func(this, a_inputRenderTarget, a_outputRenderTarget);
	}
}
