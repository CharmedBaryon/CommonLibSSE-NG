#pragma once

#include "RE/N/NiTArray.h"

namespace RE
{
	class BSTriShape;
	class ImageSpaceManager;
	class ImageSpaceEffectParam;
	class ImageSpaceTexture;

	class ImageSpaceEffect
	{
	public:
		class EffectInput;

		inline static constexpr auto RTTI = RTTI_ImageSpaceEffect;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceEffect;

		virtual ~ImageSpaceEffect();  // 00

		// add
		virtual void Render(BSTriShape* a_shape, ImageSpaceEffectParam* a_param);          // 01
		virtual void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param);  // 02 - { return; }
		virtual void ShutDown();                                                           // 03 - { return; }
		virtual void BorrowTextures(ImageSpaceEffectParam* a_param);                       // 04 - { return; }
		virtual void ReturnTextures();                                                     // 05 - { return; }
		virtual bool IsActive();                                                           // 06
		virtual bool UpdateParams(ImageSpaceEffectParam* a_param);                         // 07 - { return 0; }
		virtual bool SetRenderStates(ImageSpaceEffectParam* a_param);                      // 08 - { return 0; }
		virtual bool RestoreRenderStates(ImageSpaceEffectParam* a_param);                  // 09 - { return 0; }

		// members
		bool                                              active;          // 08
		bool                                              unk09;           // 09
		std::uint16_t                                     pad0A;           // 0A
		std::uint32_t                                     pad0C;           // 0C
		NiTPrimitiveArray<ImageSpaceEffect*>              effects;         // 10
		NiTPrimitiveArray<ImageSpaceEffectParam*>         effectParams;    // 28
		NiTPrimitiveArray<ImageSpaceTexture*>             effectTextures;  // 40
		NiTPrimitiveArray<ImageSpaceEffect::EffectInput*> effectInputs;    // 58
		NiTPrimitiveArray<std::int32_t>                   unk70;           // 70
		bool                                              unk88;           // 88
		std::uint8_t                                      pad89;           // 89
		std::uint16_t                                     pad8A;           // 8A
		std::uint32_t                                     pad8C;           // 8C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceEffect) == 0x90);
}
