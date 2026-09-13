#include "RE/R/Renderer.h"

#include "RE/R/RendererShadowState.h"
#include "RE/S/State.h"

namespace RE
{
	namespace BSGraphics
	{
		Renderer* Renderer::GetSingleton() noexcept
		{
			static REL::Relocation<Renderer*> singleton{ RELOCATION_ID(524907, 411393) };
			return singleton.get();
		}

		NiTexture::RendererData* Renderer::CreateRenderTexture(std::uint32_t a_width, std::uint32_t a_height)
		{
			using func_t = decltype(&Renderer::CreateRenderTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75507, 77299) };
			return func(this, a_width, a_height);
		}

		void Renderer::SaveRenderTargetToFile(RENDER_TARGET a_renderTarget, const char* a_filePath, BSGraphics::TextureFileFormat a_textureFileFormat)
		{
			using func_t = decltype(&Renderer::SaveRenderTargetToFile);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75522, 77316) };
			return func(this, a_renderTarget, a_filePath, a_textureFileFormat);
		}

		void Renderer::Init(RendererInitOSData* a_data, ApplicationWindowProperties* a_windowProps, REX::W32::HWND a_window)
		{
			using func_t = decltype(&Renderer::Init);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75445, 77226) };
			return func(this, a_data, a_windowProps, a_window);
		}

		void Renderer::Begin(std::uint32_t a_windowID)
		{
			using func_t = decltype(&Renderer::Begin);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75460, 77245) };
			return func(this, a_windowID);
		}

		void Renderer::CreateSwapChain(REX::W32::HWND* a_window, bool a_setCurrent)
		{
			using func_t = decltype(&Renderer::CreateSwapChain);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75457, 77242) };
			return func(this, a_window, a_setCurrent);
		}

		void Renderer::End()
		{
			using func_t = decltype(&Renderer::End);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75461, 77246) };
			return func(this);
		}

		void Renderer::KillWindow(std::uint32_t a_windowID)
		{
			using func_t = decltype(&Renderer::KillWindow);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75452, 77237) };
			return func(this, a_windowID);
		}

		void Renderer::Lock()
		{
			using func_t = decltype(&Renderer::Lock);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75458, 77243) };
			return func(this);
		}

		void Renderer::Unlock()
		{
			using func_t = decltype(&Renderer::Unlock);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75459, 77244) };
			return func(this);
		}

		void Renderer::ResizeWindow(std::uint32_t a_windowID, std::uint32_t a_width, std::uint32_t a_height, bool a_fullscreen, bool a_borderless)
		{
			using func_t = decltype(&Renderer::ResizeWindow);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75449, 77234) };
			return func(this, a_windowID, a_width, a_height, a_fullscreen, a_borderless);
		}

		void Renderer::RequestWindowResize(std::uint32_t a_width, std::uint32_t a_height)
		{
			using func_t = decltype(&Renderer::RequestWindowResize);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75450, 77235) };
			return func(this, a_width, a_height);
		}

		void Renderer::SetWindowPosition(std::uint32_t a_windowID, std::int32_t a_x, std::int32_t a_y)
		{
			using func_t = decltype(&Renderer::SetWindowPosition);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75448, 77233) };
			return func(this, a_windowID, a_x, a_y);
		}

		void Renderer::SetWindowActiveState(bool a_show)
		{
			using func_t = decltype(&Renderer::SetWindowActiveState);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75451, 77236) };
			return func(this, a_show);
		}

		void Renderer::WindowSizeChanged(std::uint32_t a_windowID)
		{
			using func_t = decltype(&Renderer::WindowSizeChanged);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75453, 77238) };
			return func(this, a_windowID);
		}

		void Renderer::ResetWindow(std::uint32_t a_windowID)
		{
			using func_t = decltype(&Renderer::ResetWindow);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75454, 77239) };
			return func(this, a_windowID);
		}

		void Renderer::SetRenderTarget(std::uint32_t a_renderTargetSlot, RENDER_TARGET a_renderTarget, SetRenderTargetMode a_mode, bool a_updateViewport)
		{
			using func_t = decltype(&Renderer::SetRenderTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75654, 77453) };
			return func(this, a_renderTargetSlot, a_renderTarget, a_mode, a_updateViewport);
		}

		void Renderer::UpdateViewPort(std::uint32_t a_unk1, std::uint32_t a_unk2, bool a_unk3)
		{
			using func_t = decltype(&Renderer::UpdateViewPort);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75455, 77240) };
			return func(this, a_unk1, a_unk2, a_unk3);
		}

		void Renderer::ApplyState(bool a_arg2)
		{
			using func_t = decltype(&Renderer::ApplyState);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75462, 77247) };
			return func(this, a_arg2);
		}

		void Renderer::SubmitAccumulator(NiCamera* a_camera, BSShaderAccumulator* a_accumulator, std::uint32_t a_renderFlags)
		{
			using func_t = decltype(&Renderer::SubmitAccumulator);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99789, 106436) };
			return func(a_camera, a_accumulator, a_renderFlags);
		}

		void Renderer::StartAccumulating(NiCamera* a_camera, BSShaderAccumulator* a_accumulator, std::uint32_t a_renderFlags)
		{
			using func_t = decltype(&Renderer::StartAccumulating);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99790, 106437) };
			return func(a_camera, a_accumulator, a_renderFlags);
		}

		void Renderer::FinishAccumulatingPostResolveDepth(NiCamera* a_unusedCamera, BSShaderAccumulator* a_accumulator, std::uint32_t a_renderFlags)
		{
			using func_t = decltype(&Renderer::FinishAccumulatingPostResolveDepth);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99791, 106438) };
			return func(a_unusedCamera, a_accumulator, a_renderFlags);
		}

		void Renderer::Shutdown()
		{
			using func_t = decltype(&Renderer::Shutdown);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75447, 77228) };
			return func(this);
		}

		[[nodiscard]] RendererData* Renderer::GetRendererDataSingleton()
		{
			// Location is a global pointer to the RendererData in the Renderer singleton
			static REL::Relocation<RendererData**> singleton{ RELOCATION_ID(524728, 411347) };
			return *singleton;
		}

		[[nodiscard]] ScreenSize Renderer::GetScreenSize()
		{
			const auto state = RE::BSGraphics::State::GetSingleton();
			return ScreenSize{ state->screenWidth, state->screenHeight };
		}

		[[nodiscard]] REX::W32::ID3D11Device* Renderer::GetDevice()
		{
			// Location is a global pointer to the device in the Renderer Data
			static REL::Relocation<REX::W32::ID3D11Device**> device{ RELOCATION_ID(524729, 411348) };
			return *device;
		}

		[[nodiscard]] RendererWindow* Renderer::GetCurrentRenderWindow()
		{
			// Location is a global pointer to the current renderWindow (which is not necessarily at index 0 in the renderWindows array)
			static REL::Relocation<RendererWindow**> renderWindow{ RELOCATION_ID(524730, 411349) };
			return *renderWindow;
		}

		void Renderer::PrepareVSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetVSConstantGroup(level);
			if (group.buffer != nullptr) {
				REX::W32::D3D11_MAPPED_SUBRESOURCE resource;
				deviceContext->Map(group.buffer, 0, REX::W32::D3D11_MAP_WRITE_DISCARD, 0, &resource);
				group.data = resource.data;
			}
		}

		void Renderer::PreparePSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetPSConstantGroup(level);
			if (group.buffer != nullptr) {
				REX::W32::D3D11_MAPPED_SUBRESOURCE resource;
				deviceContext->Map(group.buffer, 0, REX::W32::D3D11_MAP_WRITE_DISCARD, 0, &resource);
				group.data = resource.data;
			}
		}

		void Renderer::FlushVSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetVSConstantGroup(level);
			if (group.buffer != nullptr) {
				deviceContext->Unmap(group.buffer, 0);
			}
		}

		void Renderer::FlushPSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetPSConstantGroup(level);
			if (group.buffer != nullptr) {
				deviceContext->Unmap(group.buffer, 0);
			}
		}

		void Renderer::ApplyVSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetVSConstantGroup(level);

			static const bool isVr = REL::Module::IsVR();
			if (isVr) {
				auto&      vrData = shadowState->GetVRRuntimeData();
				auto*      buffer = group.buffer;
				const auto bufferIndex = static_cast<UINT>(level);
				if (vrData.VSConstantBuffers[bufferIndex] != buffer) {
					deviceContext->VSSetConstantBuffers(bufferIndex, 1, &group.buffer);
					vrData.VSConstantBuffers[bufferIndex] = buffer;
				}
			} else {
				deviceContext->VSSetConstantBuffers(static_cast<UINT>(level), 1, &group.buffer);
			}
		}

		void Renderer::ApplyPSConstantGroup(ConstantGroupLevel level)
		{
			auto* shadowState = RendererShadowState::GetSingleton();
			auto* deviceContext = GetSingleton()->GetRuntimeData().context;

			auto& group = shadowState->GetPSConstantGroup(level);

			static const bool isVr = REL::Module::IsVR();
			if (isVr) {
				auto&      vrData = shadowState->GetVRRuntimeData();
				auto*      buffer = group.buffer;
				const auto bufferIndex = static_cast<UINT>(level);
				if (vrData.PSConstantBuffers[bufferIndex] != buffer) {
					deviceContext->PSSetConstantBuffers(bufferIndex, 1, &group.buffer);
					vrData.PSConstantBuffers[bufferIndex] = buffer;
				}
			} else {
				deviceContext->PSSetConstantBuffers(static_cast<UINT>(level), 1, &group.buffer);
			}
		}
	}
}
