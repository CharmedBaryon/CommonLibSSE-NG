#pragma once

#include "RE/B/BSShader.h"
#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiTexture.h"
#include "RE/R/RenderTargetData.h"
#include "RE/T/TextureFileFormat.h"
#include <SKSE/Version.h>

#include "REX/W32/D3D11_3.h"
#include "REX/W32/USER32.h"

namespace RE
{
	namespace BSGraphics
	{
		struct RendererWindow
		{
		public:
			// members
			REX::W32::HWND                       hWnd;                   // 00
			std::int32_t                         windowX;                // 08
			std::int32_t                         windowY;                // 0C
			std::int32_t                         windowWidth;            // 10
			std::int32_t                         windowHeight;           // 14
			REX::W32::IDXGISwapChain*            swapChain;              // 18
			RENDER_TARGET                        swapChainRenderTarget;  // 20
			std::uint32_t                        unk24;                  // 24
			std::uint64_t                        unk28;                  // 28
			REX::W32::ID3D11RenderTargetView1*   renderView;             // 30
			REX::W32::ID3D11ShaderResourceView1* resourceView;           // 38
			std::uint64_t                        unk40;                  // 40
			std::uint64_t                        unk48;                  // 48
		};
		static_assert(sizeof(RendererWindow) == 0x50);

		struct RendererData2
		{
		public:
#define RENDERER_DATA2_CONTENT                                                                                       \
	CubemapRenderTargetData    cubemapRenderTargets[RENDER_TARGET_CUBEMAP::kTOTAL]; /* 26D8, VR 2E48, AE1130 2738 */ \
	Texture3DTargetData        texture3DRenderTargets[RENDER_TARGET_3D::kTOTAL];    /* 2718, VR 2E88, AE1130 2778*/  \
	float                      clearColor[4];                                       /* 2778, VR 2EE8, AE1130 27d8*/  \
	std::uint8_t               clearStencil;                                        /* 2788, VR 2EF8, AE1130 27e8*/  \
	REX::W32::CRITICAL_SECTION lock;                                                /* 2790, VR 2F00, AE1130 27f0*/  \
	const char*                className;                                           /* 27B8, VR 2F28, AE1130 2818*/  \
	REX::W32::HINSTANCE        hInstance;                                           /* 27C0, VR 2F30, AE1130 2820*/
            RENDERER_DATA2_CONTENT
		};

		struct DepthStencilRuntimeData
		{
		public:
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	define DEPTHSTENCIL_RUNTIME_DATA_CONTENT \
		DepthStencilData depthStencils[RENDER_TARGET_DEPTHSTENCIL::kTOTAL]; /* 1FB8, VR 21D0, AE1130 0x2018*/
//#elif defined(EXCLUSIVE_SKYRIM_VR)
#else
#	define DEPTHSTENCIL_RUNTIME_DATA_CONTENT \
		DepthStencilData depthStencils[RENDER_TARGET_DEPTHSTENCIL::kVRTOTAL]; /* 1FB8, VR 21D0, AE1130 0x2018*/
#endif
			DEPTHSTENCIL_RUNTIME_DATA_CONTENT
		};

		struct RendererData
		{
		public:
			// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	define RUNTIME_DATA_CONTENT                                                                             \
		std::uint32_t                      uiAdapter;                              /* 0018 */                \
		REX::W32::DXGI_RATIONAL            desiredRefreshRate;                     /* 001C - refreshRate? */ \
		REX::W32::DXGI_RATIONAL            actualRefreshRate;                      /* 0020 */                \
		REX::W32::DXGI_MODE_SCALING        scaleMode;                              /* 0024*/                 \
		REX::W32::DXGI_MODE_SCANLINE_ORDER scanlineOrdering;                       /* 0028*/                 \
		std::uint32_t                      isNotWindowed;                          /* 0034*/                 \
		bool                               fullScreen;                             /* 0038*/                 \
		bool                               borderlessDisplay;                      /* 0039*/                 \
		bool                               readOnlyDepth;                          /* 003A*/                 \
		bool                               instantiated;                           /* 003B*/                 \
		bool                               requestedWindowSizeChange;              /* 003C*/                 \
		bool                               unk25;                                  /* 003D*/                 \
		std::uint32_t                      newWidth;                               /* 0038*/                 \
		std::uint32_t                      newHeight;                              /* 0040*/                 \
		std::uint32_t                      presentInterval;                        /* 004C*/                 \
		REX::W32::ID3D11Device*            forwarder;                              /* 0050*/                 \
		REX::W32::ID3D11DeviceContext*     context;                                /* 0058*/                 \
		RendererWindow                     renderWindows[32];                      /* 0060*/                 \
		RenderTargetData                   renderTargets[RENDER_TARGET::kVRTOTAL]; /* 0A60*/
#else
#	define RUNTIME_DATA_CONTENT                                                                           \
		std::uint32_t                      uiAdapter;                            /* 0010 */                \
		REX::W32::DXGI_RATIONAL            desiredRefreshRate;                   /* 001C - refreshRate? */ \
		REX::W32::DXGI_RATIONAL            actualRefreshRate;                    /* 0020 */                \
		REX::W32::DXGI_MODE_SCALING        scaleMode;                            /* 0024*/                 \
		REX::W32::DXGI_MODE_SCANLINE_ORDER scanlineOrdering;                     /* 0028*/                 \
		std::uint32_t                      isNotWindowed;                        /* 0034*/                 \
		bool                               fullScreen;                           /* 0038*/                 \
		bool                               borderlessDisplay;                    /* 0039*/                 \
		bool                               readOnlyDepth;                        /* 003A*/                 \
		bool                               instantiated;                         /* 003B*/                 \
		bool                               requestedWindowSizeChange;            /* 003C*/                 \
		bool                               unk25;                                /* 003D*/                 \
		std::uint32_t                      newWidth;                             /* 0038*/                 \
		std::uint32_t                      newHeight;                            /* 0040*/                 \
		std::uint32_t                      presentInterval;                      /* 004C*/                 \
		REX::W32::ID3D11Device*            forwarder;                            /* 0050*/                 \
		REX::W32::ID3D11DeviceContext*     context;                              /* 0058*/                 \
		RendererWindow                     renderWindows[32];                    /* 0058*/                 \
		RenderTargetData                   renderTargets[RENDER_TARGET::kTOTAL]; /* 0A58*/
#endif
			RUNTIME_DATA_CONTENT;
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(RendererData) == 0x21B8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(RendererData) == 0x1fa8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#else
		static_assert(sizeof(RendererData) == 0x1fa8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#endif
		struct RendererInitOSData
		{
			REX::W32::HWND      hwnd;                // 00
			REX::W32::HINSTANCE instance;            // 08
			REX::W32::WNDPROC   windowProcFunction;  // 10
			REX::W32::HICON     icon;                // 18
			const char*         className;           // 20
			std::uint32_t       adapter;             // 28
			std::uint32_t       unk2C;               // 2C
		};
		static_assert(sizeof(RendererInitOSData) == 0x30);

		struct ScreenSize
		{
			std::uint32_t width;   // 00
			std::uint32_t height;  // 04
		};
		static_assert(sizeof(ScreenSize) == 0x8);

		struct ApplicationWindowProperties
		{
			ScreenSize screenSize;        // 00
			int        windowX;           // 08
			int        windowY;           // 0C
			int        refreshRate;       // 10
			int        presentInterval;   // 14
			bool       appFullScreen;     // 18
			bool       borderlessWindow;  // 19
			bool       vsync;             // 1A
		};
		static_assert(sizeof(ApplicationWindowProperties) == 0x1C);

		class Renderer
		{
		public:
			[[nodiscard]] inline RendererData& GetRuntimeData() noexcept
			{
				return REL::RelocateMember<RendererData>(this, 0x10, 0x18);
			}

			[[nodiscard]] inline const RendererData& GetRuntimeData() const noexcept
			{
				return REL::RelocateMember<RendererData>(this, 0x10, 0x18);
			}

			[[nodiscard]] inline DepthStencilRuntimeData& GetDepthStencilData() noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<DepthStencilRuntimeData>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x1FB8, 0x2018);

				return REL::RelocateMember<DepthStencilRuntimeData>(this, 0x1FB8, 0x21D0);
			}

			[[nodiscard]] inline const DepthStencilRuntimeData& GetDepthStencilData() const noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<DepthStencilRuntimeData>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x1FB8, 0x2018);
				return REL::RelocateMember<DepthStencilRuntimeData>(this, 0x1FB8, 0x21D0);
			}

			[[nodiscard]] inline RendererData2& GetRendererData() noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<RendererData2>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x26D8, 0x2738);
				return REL::RelocateMember<RendererData2>(this, 0x26D8, 0x2E48);
			}

			[[nodiscard]] inline const RendererData2& GetRendererData() const noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<RendererData2>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x26D8, 0x2738);
				return REL::RelocateMember<RendererData2>(this, 0x26D8, 0x2E48);
			}
			[[nodiscard]] inline REX::W32::CRITICAL_SECTION& GetLock() noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<REX::W32::CRITICAL_SECTION>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x2790, 0x27f0);
				return REL::RelocateMember<REX::W32::CRITICAL_SECTION>(this, 0x2790, 0x2F00);
			}

			[[nodiscard]] inline const REX::W32::CRITICAL_SECTION& GetLock() const noexcept
			{
				if (REL::Module::IsAE())
					return REL::RelocateMemberIfNewer<REX::W32::CRITICAL_SECTION>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x2790, 0x27f0);
				return REL::RelocateMember<REX::W32::CRITICAL_SECTION>(this, 0x2790, 0x2F00);
			}

			[[nodiscard]] static Renderer* GetSingleton() noexcept;

			void CreateSwapChain(REX::W32::HWND* a_window, bool a_setCurrent);
			void KillWindow(std::uint32_t a_windowID);
			void Lock();
			void Unlock();
			void ResizeWindow(std::uint32_t a_windowID, std::uint32_t a_width, std::uint32_t a_height, bool a_fullscreen, bool a_borderless);
			void RequestWindowResize(std::uint32_t a_width, std::uint32_t a_height);
			void SetWindowPosition(std::uint32_t a_windowID, std::int32_t a_x, std::int32_t a_y);
			void SetWindowActiveState(bool a_show);
			void WindowSizeChanged(std::uint32_t a_windowID);
			void ResetWindow(std::uint32_t a_windowID);
			void UpdateViewPort(std::uint32_t a_unk1, std::uint32_t a_unk2, bool a_unk3);

			[[nodiscard]] NiTexture::RendererData* CreateRenderTexture(std::uint32_t a_width, std::uint32_t a_height);
			void                                   SaveRenderTargetToFile(RENDER_TARGET a_renderTarget, const char* a_filePath, TextureFileFormat a_textureFileFormat);

			static void PrepareVSConstantGroup(ConstantGroupLevel level);
			static void PreparePSConstantGroup(ConstantGroupLevel level);
			static void FlushVSConstantGroup(ConstantGroupLevel level);
			static void FlushPSConstantGroup(ConstantGroupLevel level);
			static void ApplyVSConstantGroup(ConstantGroupLevel level);
			static void ApplyPSConstantGroup(ConstantGroupLevel level);

			[[nodiscard]] static RendererData* GetRendererDataSingleton();

			[[nodiscard]] static ScreenSize              GetScreenSize();
			[[nodiscard]] static REX::W32::ID3D11Device* GetDevice();
			[[nodiscard]] static RendererWindow*         GetCurrentRenderWindow();

			// members
			std::uint64_t unk000;      // 0000
			bool          drawStereo;  // 0008
#if defined(EXCLUSIVE_SKYRIM_FLAT)
			RUNTIME_DATA_CONTENT;  // 0010
#elif defined(EXCLUSIVE_SKYRIM_VR)
			RUNTIME_DATA_CONTENT;  // VR 18
#endif

		private:
			void Begin(std::uint32_t windowID);
			void Init(RendererInitOSData* a_data, ApplicationWindowProperties* a_windowProps, REX::W32::HWND a_window);
			void End();
			void Shutdown();
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(Renderer) == 0x21C0);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(Renderer) == 0x1FB0);
#else
		static_assert(sizeof(Renderer) == 0x10);
#endif
	}
}
#undef RUNTIME_DATA_CONTENT
#undef DEPTHSTENCIL_RUNTIME_DATA_CONTENT
#undef RENDERER_DATA2_CONTENT
