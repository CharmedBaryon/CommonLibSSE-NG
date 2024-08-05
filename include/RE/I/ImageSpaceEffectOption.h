#pragma once

#include "RE/I/ImageSpaceEffect.h"

namespace RE
{
	class ImageSpaceEffectOption : public ImageSpaceEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceEffectOption;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceEffectOption;

		~ImageSpaceEffectOption() override;  // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_shape, ImageSpaceEffectParam* a_param) override;  // 01

		// members
		NiTPrimitiveArray<bool> options;  // 90
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceEffectOption) == 0xA8);
}
