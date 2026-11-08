#pragma once

#include "RE/G/GColor.h"

namespace RE
{
	class GFxFillStyle;
	class GRenderer;

	class GFxLineStyle
	{
	public:
		enum class LineStyle
		{
			kNone = 0,
			kStrokeHinting = 1,

			kScalingNormal = 0,
			kScalingHorizontal = 2,
			kScalingVertical = 4,
			kScalingNone = 6,
			kScalingMask = 6,

			kComplexFill = 8,

			kJoinRound = 0,
			kJoinBevel = 16,
			kJoinMiter = 32,
			kJoinMask = 48,

			kCapRound = 0,
			kCapNone = 64,
			kCapSquare = 128,
			kCapMask = 192,

			kEndCapRound = 0,
			kEndCapNone = 256,
			kEndCapSquare = 512,
			kEndCapMask = 768,

			kShiftToCap = 2
		};

		virtual ~GFxLineStyle();  // 00

		// add
		virtual void Apply(GRenderer* a_renderer) const;  // 01

		// members
		std::uint16_t                          width;        // 08
		std::uint16_t                          pad0A;        // 0A
		GColor                                 color;        // 0C
		GFxFillStyle*                          complexFill;  // 10
		REX::EnumSet<LineStyle, std::uint16_t> styleFlags;   // 18
		std::uint16_t                          pad1A;        // 1A
		float                                  miterSize;    // 1C
	};
	static_assert(sizeof(GFxLineStyle) == 0x20);
}
