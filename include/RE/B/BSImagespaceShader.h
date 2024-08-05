#pragma once

#include "RE/B/BSShader.h"
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

		~BSImagespaceShader() override;  // 00

		// override (BSShader)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override;  // 02
		void ShutDown() override;                                                           // 03
		bool IsActive() override;                                                           // 06
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;                         // 07
		bool RestoreRenderStates(ImageSpaceEffectParam* a_param) override;                  // 09

		// add
		virtual void Unk_0A(void);  // 0A - { return; }
		virtual void Unk_0B(void);  // 0B - { return; }
		virtual void Unk_0C(void);  // 0C
		virtual void Unk_0D(void);  // 0D
		virtual void Unk_0E(void);  // 0E

		// members
		BSFixedString           name;                // 120
		BSFixedString           originalShaderName;  // 128
		std::uint64_t           unk130;              // 130
		BSTArray<BSFixedString> vsConstantNames;     // 138
		BSTArray<BSFixedString> psConstantNames;     // 150
		BSTArray<BSFixedString> samplerNames;        // 158
		BSTArray<BSFixedString> unk180;              // 180
		BSComputeShader*        computeShader;       // 198
		bool                    unk1A0;              // 1A0
		bool                    isComputeShader;     // 1A1
	};
	static_assert(sizeof(BSImagespaceShader) == 0x1A8);
}
