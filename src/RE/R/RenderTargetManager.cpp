#include "RE/R/RenderTargetManager.h"

namespace RE
{
	namespace BSGraphics
	{
		void RenderTargetManager::CreateCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, const CubeMapRenderTargetProperties& a_properties)
		{
			using func_t = decltype(&RenderTargetManager::CreateCubeMapRenderTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75640, 77447) };
			return func(this, a_renderTarget, a_properties);
		}

		void RenderTargetManager::CreateDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, const DepthStencilTargetProperties& a_properties)
		{
			using func_t = decltype(&RenderTargetManager::CreateDepthStencilTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75639, 77446) };
			return func(this, a_renderTarget, a_properties);
		}

		void RenderTargetManager::SetCurrentCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_faceIndex, bool a_updateViewport)
		{
			using func_t = decltype(&RenderTargetManager::SetCurrentCubeMapRenderTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75648, 77455) };
			return func(this, a_renderTarget, a_mode, a_faceIndex, a_updateViewport);
		}

		void RenderTargetManager::SetCurrentDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_slice)
		{
			using func_t = decltype(&RenderTargetManager::SetCurrentDepthStencilTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75647, 77454) };
			return func(this, a_renderTarget, a_mode, a_slice);
		}
	}
}
