#pragma once

#include <cstddef>
#include <cstdint>

#include "RE/B/BSShaderRenderTargets.h"
#include "RE/R/RenderTargetProperties.h"
#include "RE/R/RendererShadowState.h"

namespace RE
{
	namespace BSGraphics
	{
		class RenderTargetManager
		{
		public:
			[[nodiscard]] static RenderTargetManager* GetSingleton()
			{
				static REL::Relocation<RenderTargetManager**> singleton{ RELOCATION_ID(524970, 411451) };
				return *singleton;
			}

			void CreateCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, const CubeMapRenderTargetProperties& a_properties);
			void CreateDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, const DepthStencilTargetProperties& a_properties);
			void SetCurrentCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_faceIndex, bool a_updateViewport);
			void SetCurrentDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_slice);

#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
			// Both runtimes are compiled in: dispatch by REL::Module::IsAE(), not #ifdef.
			[[nodiscard]] inline DepthStencilTargetProperties* GetDepthStencilTargetData() noexcept
			{
				return &REL::RelocateMember<DepthStencilTargetProperties>(this, 0xC78, 0xCB0);
			}
			[[nodiscard]] inline CubeMapRenderTargetProperties* GetCubeMapRenderTargetData() noexcept
			{
				return &REL::RelocateMember<CubeMapRenderTargetProperties>(this, 0xD38, 0xD70);
			}
#endif

			// members
			RenderTargetProperties renderTargetData[RENDER_TARGET::kTOTAL];  // 000
#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
			// Placeholder sized to the larger (AE) layout; real access goes through
			// GetDepthStencilTargetData()/GetCubeMapRenderTargetData() above, not these
			// members directly.
			std::byte runtimeDataPlaceholder[0x104];  // C78
#else
#	ifdef ENABLE_SKYRIM_AE
			std::byte                     padC78[0x38];                                                 // C78
#	endif
			DepthStencilTargetProperties  depthStencilTargetData[RENDER_TARGETS_DEPTHSTENCIL::kTOTAL];  // C78, CB0
			CubeMapRenderTargetProperties cubeMapRenderTargetData[RENDER_TARGETS_CUBEMAP::kTOTAL];      // D38, D70
#endif
		};

#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
		static_assert(sizeof(RenderTargetManager) == 0xD7C);
#elif defined(ENABLE_SKYRIM_AE)
		static_assert(sizeof(RenderTargetManager) == 0xD7C);
#else
		static_assert(sizeof(RenderTargetManager) == 0xD44);
#endif
	}
}
