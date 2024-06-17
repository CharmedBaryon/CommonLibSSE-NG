#pragma once

#include "RE/G/GASObjectInterface.h"
#include "RE/G/GFxCharacter.h"

namespace RE
{
	class GASMovieClipObject;
	class GFxMovieDef;

	class GFxASCharacter :
		public GFxCharacter,       // 000
		public GASObjectInterface  // 098
	{
	public:
		virtual ~GFxASCharacter();  // 00

		// override (GFxCharacter)
		void Unk_01(void) override;  // 01
		void Unk_04(void) override;  // 04
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06
		void Unk_07(void) override;  // 07
		void Unk_08(void) override;  // 08
		void Unk_09(void) override;  // 09
		void Unk_0A(void) override;  // 0A
		void Unk_0B(void) override;  // 0B
		void Unk_0C(void) override;  // 0C
		void Unk_22(void) override;  // 22
		void Unk_23(void) override;  // 23
		void Unk_2C(void) override;  // 2C
		void Unk_2D(void) override;  // 2D
		void Unk_2E(void) override;  // 2E
		void Unk_2F(void) override;  // 2F
		void Unk_30(void) override;  // 30

		// override (GASObjectInterface)
		void GASObjectInterface_02(void) override;                                           // 02
		void GASObjectInterface_03(void) override;                                           // 03
		void GASObjectInterface_04(void) override;                                           // 04
		void GASObjectInterface_05(void) override;                                           // 05
		void GASObjectInterface_06(void) override;                                           // 06
		void GASObjectInterface_07(void) override;                                           // 07
		void GASObjectInterface_08(void) override;                                           // 08
		void GASObjectInterface_09(void) override;                                           // 09
		void GASObjectInterface_0A(void) override;                                           // 0A
		void GASObjectInterface_0B(void) override;                                           // 0B
		void Set__proto__(GASStringContext* a_stringContext, GASObject* a_object) override;  // 0D
		void GASObjectInterface_12(void) override;                                           // 12
		void GASObjectInterface_13(void) override;                                           // 13
		void GASObjectInterface_14(void) override;                                           // 14

		// add
		virtual void                Unk_31(void);    // 31
		virtual void                Unk_32(void);    // 32
		virtual void                Unk_33(void);    // 33
		virtual void                Unk_34(void);    // 34
		virtual void                Unk_35(void);    // 35 - pure
		virtual void                Unk_36(void);    // 36
		virtual void                Unk_37(void);    // 37
		virtual void                Unk_38(void);    // 38
		virtual void                Unk_39(void);    // 39
		virtual void                Unk_3A(void);    // 3A
		virtual void                Unk_3B(void);    // 3B
		virtual void                Unk_3C(void);    // 3C
		virtual void                Unk_3D(void);    // 3D
		virtual void                Unk_3E(void);    // 3E
		virtual void                Unk_3F(void);    // 3F
		virtual void                Unk_40(void);    // 40
		virtual GASMovieClipObject* GetMovieClip();  // 41 - { return nullptr; }
		virtual void                Unk_42(void);    // 42
		virtual void                Unk_43(void);    // 43
		virtual void                Unk_44(void);    // 44
		virtual void                Unk_45(void);    // 45
		virtual void                Unk_46(void);    // 46
		virtual void                Unk_47(void);    // 47
		virtual void                Unk_48(void);    // 48
		virtual void                Unk_49(void);    // 49
		virtual void                Unk_4A(void);    // 4A
		virtual void                Unk_4B(void);    // 4B
		virtual void                Unk_4C(void);    // 4C
		virtual void                Unk_4D(void);    // 4D
		virtual void                Unk_4E(void);    // 4E
		virtual void                Unk_4F(void);    // 4F
		virtual void                Unk_50(void);    // 50
		virtual void                Unk_51(void);    // 51
		virtual void                Unk_52(void);    // 52
		virtual void                Unk_53(void);    // 53
		virtual void                Unk_54(void);    // 54
		virtual void                Unk_55(void);    // 55
		virtual void                Unk_56(void);    // 56
		virtual void                Unk_57(void);    // 57

		// members
		std::uint64_t unk0B0;    // 0B0
		std::uint64_t unk0B8;    // 0B8
		std::uint64_t unk0C0;    // 0C0
		GFxMovieDef*  movieDef;  // 0C8
		std::uint64_t unk0D0;    // 0D0
		std::uint64_t unk0D8;    // 0D0
		std::uint64_t unk0E0;    // 0D0
		std::uint64_t unk0E8;    // 0D0
		std::uint64_t unk0F0;    // 0D0
		std::uint64_t unk0F8;    // 0D0
		std::uint64_t unk100;    // 0D0
		std::uint64_t unk118;    // 0D0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxASCharacter) == 0x110);
}
