#pragma once


namespace RE
{
	struct DECAL_DATA_DATA
	{
		enum Flag : UInt8
		{
			kNone = 0,
			kParallax = 1 << 0,
			kAlphaBlending = 1 << 1,
			kAlphaTesting = 1 << 2,
			kNoSubtextures = 1 << 3
		};


		float	decalMinWidth;	// 00
		float	decalMaxWidth;	// 04
		float	decalMinHeight;	// 08
		float	decalMaxHeight;	// 0C
		float	depth;			// 10
		float	shininess;		// 14
		float	parallaxScale;	// 18
		SInt8	parallaxPasses;	// 1C
		Flag	flags;			// 1D
		UInt16	pad1E;			// 1E
		Color	color;			// 20
	};
	STATIC_ASSERT(sizeof(DECAL_DATA_DATA) == 0x24);


	struct DecalData
	{
		DECAL_DATA_DATA data;	// 00
	};
	STATIC_ASSERT(sizeof(DecalData) == 0x24);
}
