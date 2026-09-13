#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSShader.h"
#include "RE/B/BSShaderRenderTargets.h"
#include "RE/B/BSTArray.h"
#include "RE/I/ImageSpaceEffect.h"

namespace RE
{
	class BSComputeShader;

	class BSImagespaceShader :
		public BSShader,         // 000
		public ImageSpaceEffect  // 090
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSImagespaceShader;
		inline static constexpr auto VTABLE = VTABLE_BSImagespaceShader;

		struct ShaderMacro
		{
			// members
			const char* name;        // 00
			const char* definition;  // 08
		};
		static_assert(sizeof(ShaderMacro) == 0x10);

		~BSImagespaceShader() override;  // 00

		// override (BSShader)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override;  // 02
		void ShutDown() override;                                                           // 03
		bool IsActive() override;                                                           // 06
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;                         // 07
		bool RestoreRenderStates(ImageSpaceEffectParam* a_param) override;                  // 09

		// add
		virtual void PreRender();                                                                                                      // 0A - { return; }
		virtual void PostRender();                                                                                                     // 0B - { return; }
		virtual void DispatchComputeShader(uint32_t a_threadGroupCountX, uint32_t a_threadGroupCountY, uint32_t a_threadGroupCountZ);  // 0C
#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual void FakeDispatchComputeShader(uint32_t a_threadGroupCountX, uint32_t a_threadGroupCountY, uint32_t a_threadGroupCountZ);  // VR 0D
		virtual void GetShaderMacros(ShaderMacro* a_macros);                                                                               // 0D, VR 0E
		virtual void LoadShaders();                                                                                                        // 0E
#elif defined(EXCLUSIVE_SKYRIM_FLAT)
		virtual void GetShaderMacros(ShaderMacro* a_macros);  // 0D, VR 0E
		virtual void LoadShaders();                           // 0E
#endif

		void          DispatchCopySubRegion();
		RENDER_TARGET RenderSSAO(RENDER_TARGET a_inputRenderTarget, RENDER_TARGET a_outputRenderTarget);
		RENDER_TARGET RenderSnowSSS(RENDER_TARGET a_inputRenderTarget, RENDER_TARGET a_outputRenderTarget);

		static BSImagespaceShader* Create()
		{
			auto isShader = malloc<BSImagespaceShader>();
			std::memset(reinterpret_cast<void*>(isShader), 0, sizeof(BSImagespaceShader));
			if (isShader) {
				isShader->Ctor();
			}
			return isShader;
		}

		// members
		const char*             name;                // 120
		const char*             originalShaderName;  // 128
		std::uint64_t           unk130;              // 130
		BSTArray<BSFixedString> vsConstantNames;     // 138
		BSTArray<BSFixedString> psConstantNames;     // 150
		BSTArray<BSFixedString> samplerNames;        // 158
		BSTArray<BSFixedString> uavNames;            // 180
		BSComputeShader*        computeShader;       // 198
		bool                    unk1A0;              // 1A0
		bool                    isComputeShader;     // 1A1

#ifdef SKYRIM_CROSS_VR
		void GetShaderMacros(ShaderMacro* a_macros)
		{
			REL::RelocateVirtual<decltype(&BSImagespaceShader::GetShaderMacros)>(0x0D, 0x0E, this, a_macros);
		}

		void LoadShaders()
		{
			REL::RelocateVirtual<decltype(&BSImagespaceShader::LoadShaders)>(0x0E, 0x0F, this);
		}
#endif

	private:
		BSImagespaceShader* Ctor()
		{
			using func_t = decltype(&BSImagespaceShader::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100943, 107725) };
			BSImagespaceShader*            isShader = func(this);
			stl::emplace_vtable<BSImagespaceShader>(isShader);
			return isShader;
		}
	};
	static_assert(sizeof(BSImagespaceShader) == 0x1A8);
}
