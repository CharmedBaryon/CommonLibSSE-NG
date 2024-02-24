#pragma once

#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiTexture.h"
#include "RE/R/RenderTargetData.h"
#include "RE/T/TextureFileFormat.h"

#include "REX/W32/D3D11_3.h"
#include "REX/W32/USER32.h"

namespace RE
{
	namespace BSGraphics
	{
		struct RendererWindow
		{
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

		struct RendererData
		{
			std::uint32_t                      adapter;                                              // 0000
			REX::W32::DXGI_RATIONAL            desiredRefreshRate;                                   // 0004
			REX::W32::DXGI_RATIONAL            actualRefreshRate;                                    // 000C
			REX::W32::DXGI_MODE_SCALING        scaleMode;                                            // 0014
			REX::W32::DXGI_MODE_SCANLINE_ORDER scanlineOrdering;                                     // 0018
			std::uint32_t                      isNotWindowed;                                        // 001C
			bool                               fullScreen;                                           // 0020
			bool                               borderlessDisplay;                                    // 0021
			bool                               readOnlyDepth;                                        // 0022
			bool                               instantiated;                                         // 0023
			bool                               requestedWindowSizeChange;                            // 0024
			std::uint32_t                      newWidth;                                             // 0028
			std::uint32_t                      newHeight;                                            // 002C
			std::uint32_t                      presentInterval;                                      // 0030
			REX::W32::ID3D11Device*            forwarder;                                            // 0038
			REX::W32::ID3D11DeviceContext*     context;                                              // 0040
			RendererWindow                     renderWindows[32];                                    // 0048
			RenderTargetData                   renderTargets[RENDER_TARGET::kTOTAL];                 // 0A48
			DepthStencilData                   depthStencils[RENDER_TARGET_DEPTHSTENCIL::kTOTAL];    // 1FA8
			CubemapRenderTargetData            cubemapRenderTargets[RENDER_TARGET_CUBEMAP::kTOTAL];  // 26C8
			Texture3DTargetData                texture3DRenderTargets[RENDER_TARGET_3D::kTOTAL];     // 2708
			float                              clearColor[4];                                        // 2768
			std::uint8_t                       clearStencil;                                         // 2778
			REX::W32::CRITICAL_SECTION         lock;                                                 // 2780
			const char*                        className;                                            // 27A8
			REX::W32::HINSTANCE                hInstance;                                            // 27B0
		};
		static_assert(offsetof(RendererData, lock) == 0x2780);

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
			uint32_t width;   // 00
			uint32_t height;  // 04
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

			[[nodiscard]] static RendererData*           GetRendererData();
			[[nodiscard]] static ScreenSize              GetScreenSize();
			[[nodiscard]] static REX::W32::ID3D11Device* GetDevice();
			[[nodiscard]] static RendererWindow*         GetCurrentRenderWindow();

		private:
			void Begin(std::uint32_t windowID);
			void Init(RendererInitOSData* a_data, ApplicationWindowProperties* a_windowProps, REX::W32::HWND a_window);
			void End();
			void Shutdown();

		public:
			// members
			std::uint64_t unk00;  // 00
			std::uint64_t unk08;  // 08
			RendererData  data;   // 10
		};
	}
}
