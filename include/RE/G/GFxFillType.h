#pragma once

namespace RE
{
	enum class GFxFillType
	{
		kSolid = 0,
		kLinearGradient = 16,
		kRadialGradient = 18,
		kFocalPointGradient = 19,
		kTiledSmoothImage = 64,
		kClippedSmoothImage = 65,
		kTiledImage = 66,
		kClippedImage = 67,

		kGradientTestBit = 16,
		kImageTestBit = 64
	};
}
