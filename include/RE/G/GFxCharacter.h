#pragma once

#include "RE/G/GFxLogBase.h"
#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GFxResourceID.h"
#include "RE/G/GMatrix2D.h"
#include "RE/G/GRefCountBaseWeakSupport.h"
#include "RE/G/GRenderer.h"

namespace RE
{
	class GASEnvironment;
	class GFxSprite;

	class GFxCharacter :
		public GRefCountBaseWeakSupport<GFxCharacter, GFxStatMovieViews::kGFxStatMV_MovieClip_Mem>,  // 00
		public GFxLogBase<GFxCharacter>                                                              // 18
	{
	public:
		~GFxCharacter() override;  // 00

		// add
		virtual void            Unk_01(void);      // 01
		virtual void            Unk_02(void);      // 02
		virtual void            Unk_03(void);      // 03
		virtual void            Unk_04(void);      // 04
		virtual void            Unk_05(void);      // 05
		virtual void            Unk_06(void);      // 06
		virtual void            Unk_07(void);      // 07
		virtual void            Unk_08(void);      // 08
		virtual void            Unk_09(void);      // 09
		virtual void            Unk_0A(void);      // 0A
		virtual void            Unk_0B(void);      // 0B
		virtual void            Unk_0C(void);      // 0C
		virtual void            Unk_0D(void);      // 0D
		virtual void            Unk_0E(void);      // 0E
		virtual void            Unk_0F(void);      // 0F
		virtual void            Unk_10(void);      // 10
		virtual void            Unk_11(void);      // 11
		virtual void            Unk_12(void);      // 12
		virtual void            Unk_13(void);      // 13
		virtual void            Unk_14(void);      // 14
		virtual void            Unk_15(void);      // 15
		virtual void            Unk_16(void);      // 16 - pure
		virtual void            Unk_17(void);      // 17
		virtual void            Unk_18(void);      // 18
		virtual void            Unk_19(void);      // 19
		virtual void            Unk_1A(void);      // 1A
		virtual void            Unk_1B(void);      // 1B
		virtual GASEnvironment* GetEnvironment();  // 1C
		virtual void            Unk_1D(void);      // 1D
		virtual void            Unk_1E(void);      // 1E
		virtual void            Unk_1F(void);      // 1F
		virtual void            Unk_20(void);      // 20
		virtual void            Unk_21(void);      // 21
		virtual void            Unk_22(void);      // 22
		virtual void            Unk_23(void);      // 23
		virtual void            Unk_24(void);      // 24
		virtual void            Unk_25(void);      // 25
		virtual void            Unk_26(void);      // 26
		virtual void            Unk_27(void);      // 27
		virtual void            Unk_28(void);      // 28
		virtual void            Unk_29(void);      // 29
		virtual void            Unk_2A(void);      // 2A
		virtual void            Unk_2B(void);      // 2B
		virtual void            Unk_2C(void);      // 2C
		virtual void            Unk_2D(void);      // 2D
		virtual void            Unk_2E(void);      // 2E
		virtual void            Unk_2F(void);      // 2F
		virtual void            Unk_30(void);      // 30

		// members
		GFxResourceID     resourceID;      // 20
		std::uint32_t     pad24;           // 24
		std::int64_t      createdFrame;    // 28
		GFxSprite*        parentClip;      // 30
		GRenderer::Cxform colorTransform;  // 38
		GMatrix2D         matrix;          // 58
		std::uint64_t     unk70;           // 70
		std::uint64_t     unk78;           // 78
		std::uint64_t     unk80;           // 80
		std::uint32_t     unk88;           // 88
		std::uint32_t     unk8C;           // 8C
		std::uint32_t     unk90;           // 90
		std::uint16_t     unk94;           // 94
		std::uint16_t     unk96;           // 96
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxCharacter) == 0x98);
}
