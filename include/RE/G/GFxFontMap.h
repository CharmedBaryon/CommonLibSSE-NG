#pragma once

#include "RE/G/GFxState.h"
#include "RE/G/GString.h"

namespace RE
{
	class GFxFontMapImpl;

	class GFxFontMap : public GFxState
	{
	public:
		enum class MapFontFlags
		{
			kNormal = 0,
			kItalic = 1 << 0,
			kBold = 1 << 1,
			kBoldItalic = kItalic | kBold,
			kFauxItalic = 1 << 2,
			kFauxBold = 1 << 3,
			kFauxBoldItalic = kFauxItalic | kFauxBold,
			kOriginal = 1 << 4,
			kNoAutoFit = 1 << 5
		};

		class MapEntry
		{
		public:
			// members
			GString                                   name;         // 00
			float                                     scaleFactor;  // 08
			float                                     unk0C;        // 0C
			float                                     unk10;        // 10
			REX::EnumSet<MapFontFlags, std::uint32_t> flags;        // 14
		};
		static_assert(sizeof(MapEntry) == 0x18);

		~GFxFontMap() override;  // 00

		// members
		GFxFontMapImpl* impl;  // 18
	};
	static_assert(sizeof(GFxFontMap) == 0x20);

	class GFxFontMapImpl
	{
	public:
		// members
		GStringHash<GFxFontMap::MapEntry> fontMap;  // 00
	};
	static_assert(sizeof(GFxFontMapImpl) == 0x8);
}
