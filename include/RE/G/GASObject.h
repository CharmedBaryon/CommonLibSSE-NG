#pragma once

#include "RE/G/GASObjectInterface.h"
#include "RE/G/GASRefCountBase.h"

namespace RE
{
	class GASObject :
		public GASRefCountBase<GASObject>,  // 00
		public GASObjectInterface           // 20
	{
	public:
		// override (GASRefCountBase)
		void Unk_00(void) override;  // 00
		void Unk_01(void) override;  // 01

		~GASObject() override;  // 02

		// override (GASObjectInterface)
		void GASObjectInterface_01(void) override;                                           // 01
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
		virtual void Unk_03(void);  // 03
		virtual void Unk_04(void);  // 04
		virtual void Unk_05(void);  // 05
		virtual void Unk_06(void);  // 06
		virtual void Unk_07(void);  // 07
		virtual void Unk_08(void);  // 08

		// members
		std::uint64_t unk38;  // 38 - properties
		std::uint64_t unk40;  // 40 - __resolve handler
		std::uint64_t unk48;  // 48
		std::uint64_t unk50;  // 50
		std::uint64_t unk58;  // 58
		std::uint64_t unk60;  // 60
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASObject) == 0x68);
}
