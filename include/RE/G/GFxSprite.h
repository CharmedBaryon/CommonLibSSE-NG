#pragma once

#include "RE/G/GASEnvironment.h"
#include "RE/G/GArray.h"
#include "RE/G/GFxASCharacter.h"

namespace RE
{
	class GFxMovieRoot;
	class GFxSpriteDef;

	class GFxSprite : public GFxASCharacter
	{
	public:
		~GFxSprite() override;  // 00

		// override (GFxASCharacter)
		void                Unk_02(void) override;      // 02
		void                Unk_03(void) override;      // 03
		void                Unk_0A(void) override;      // 0A
		void                Unk_0D(void) override;      // 0D
		void                Unk_0E(void) override;      // 0E
		void                Unk_0F(void) override;      // 0F
		void                Unk_10(void) override;      // 10
		void                Unk_11(void) override;      // 11
		void                Unk_12(void) override;      // 12
		void                Unk_13(void) override;      // 13
		void                Unk_14(void) override;      // 14
		void                Unk_15(void) override;      // 15
		void                Unk_16(void) override;      // 16
		void                Unk_17(void) override;      // 17
		void                Unk_18(void) override;      // 18
		void                Unk_19(void) override;      // 19
		void                Unk_1A(void) override;      // 1A
		void                Unk_1B(void) override;      // 1B
		GASEnvironment*     GetEnvironment() override;  // 1C
		void                Unk_1D(void) override;      // 1D
		void                Unk_1E(void) override;      // 1E
		void                Unk_1F(void) override;      // 1F
		void                Unk_20(void) override;      // 20
		void                Unk_21(void) override;      // 21
		void                Unk_22(void) override;      // 22
		void                Unk_23(void) override;      // 23
		void                Unk_24(void) override;      // 24
		void                Unk_25(void) override;      // 25
		void                Unk_28(void) override;      // 28
		void                Unk_29(void) override;      // 29
		void                Unk_2C(void) override;      // 2C
		void                Unk_2E(void) override;      // 2E
		void                Unk_33(void) override;      // 33
		void                Unk_35(void) override;      // 35
		void                Unk_37(void) override;      // 37
		void                Unk_39(void) override;      // 39
		void                Unk_3B(void) override;      // 3B
		void                Unk_3C(void) override;      // 3C
		void                Unk_3D(void) override;      // 3D
		void                Unk_3E(void) override;      // 3E
		void                Unk_40(void) override;      // 40
		GASMovieClipObject* GetMovieClip() override;    // 41
		void                Unk_42(void) override;      // 42
		void                Unk_43(void) override;      // 43
		void                Unk_46(void) override;      // 46
		void                Unk_47(void) override;      // 47
		void                Unk_48(void) override;      // 48
		void                Unk_49(void) override;      // 49
		void                Unk_4A(void) override;      // 4A
		void                Unk_4B(void) override;      // 4B
		void                Unk_4C(void) override;      // 4C
		void                Unk_4D(void) override;      // 4D
		void                Unk_4E(void) override;      // 4E
		void                Unk_4F(void) override;      // 4F
		void                Unk_50(void) override;      // 50
		void                Unk_51(void) override;      // 51
		void                Unk_52(void) override;      // 52
		void                Unk_53(void) override;      // 53
		void                Unk_54(void) override;      // 54
		void                Unk_57(void) override;      // 57

		// override (GASObjectInterface)
		void GASObjectInterface_02(void) override;  // 02
		void GASObjectInterface_04(void) override;  // 04
		void GASObjectInterface_06(void) override;  // 06
		void GASObjectInterface_08(void) override;  // 08
		void GASObjectInterface_0A(void) override;  // 0A
		void GASObjectInterface_0B(void) override;  // 0B

		// add
		virtual void Unk_58(void);  // 58
		virtual void Unk_59(void);  // 59
		virtual void Unk_5A(void);  // 5A
		virtual void Unk_5B(void);  // 5B
		virtual void Unk_5C(void);  // 5C
		virtual void Unk_5D(void);  // 5D
		virtual void Unk_5E(void);  // 5E

		// members
		GFxSpriteDef*       spriteDef;     // 110
		GFxMovieRoot*       movieRoot;     // 118
		std::uint64_t       unk120[5];     // 120
		std::uint32_t       unk148;        // 148
		std::uint32_t       currentFrame;  // 14C
		GArray<void*>       unk150;        // 150
		GASEnvironment      unk168;        // 168
		std::uint64_t       unk308;        // 308
		std::uint64_t       unk310;        // 310
		GASMovieClipObject* movieClip;     // 318 - smart pointer
		std::uint64_t       unk320;        // 320
		std::uint64_t       unk328;        // 328
		std::uint64_t       unk330;        // 330
		std::uint64_t       unk338;        // 338
		std::uint64_t       unk340;        // 340
		std::uint8_t        unk348;        // 348
		std::uint8_t        unk349;        // 349
		std::uint8_t        unk34A;        // 34A
		std::uint8_t        unk34B;        // 34B
		std::uint32_t       unk34C;        // 34C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxSprite) == 0x350);
}
