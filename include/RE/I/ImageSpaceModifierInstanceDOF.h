#pragma once

#include "RE/I/ImageSpaceData.h"
#include "RE/I/ImageSpaceModifierInstanceTemp.h"

namespace RE
{
	class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceModifierInstanceDOF;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceModifierInstanceDOF;

		enum class DepthOfFieldMode
		{
			kFrontBack = 0,
			kFront = 1,
			kBack = 2,
			kNone = 3
		};

		~ImageSpaceModifierInstanceDOF() override;  // 00

		// override (ImageSpaceModifierInstanceTemp)
		void Apply() override;                    // 26
		void PrintInfo(char* a_dstBuf) override;  // 28

		// members
		ImageSpaceModData data;  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceModifierInstanceDOF) == 0x78);
}
