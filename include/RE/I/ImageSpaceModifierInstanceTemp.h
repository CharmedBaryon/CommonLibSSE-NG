#pragma once

#include "RE/I/ImageSpaceModifierInstance.h"

namespace RE
{
	class ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceModifierInstanceTemp;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceModifierInstanceTemp;

		~ImageSpaceModifierInstanceTemp() override;  // 00

		// override (ImageSpaceModifierInstance)
		bool Unk_25(void) override;               // 25
		void PrintInfo(char* a_dstBuf) override;  // 28

		// members
		float         duration;  // 28
		std::uint32_t pad3C;     // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceModifierInstanceTemp) == 0x30);
}
