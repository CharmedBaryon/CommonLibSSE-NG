#pragma once

#include "RE/G/GPtr.h"

namespace RE
{
	class GASGlobalContext;
	class GASObject;
	class GASStringContext;
	struct GASString;

	class GASObjectInterface
	{
	public:
		virtual ~GASObjectInterface();  // 00

		// add
		virtual void GASObjectInterface_01(void);                                           // 01
		virtual void GASObjectInterface_02(void);                                           // 02
		virtual void GASObjectInterface_03(void);                                           // 03 - pure
		virtual void GASObjectInterface_04(void);                                           // 04 - pure
		virtual void GASObjectInterface_05(void);                                           // 05 - pure
		virtual void GASObjectInterface_06(void);                                           // 06 - pure
		virtual void GASObjectInterface_07(void);                                           // 07 - pure
		virtual void GASObjectInterface_08(void);                                           // 08 - pure
		virtual void GASObjectInterface_09(void);                                           // 09 - pure
		virtual void GASObjectInterface_0A(void);                                           // 0A - pure
		virtual void GASObjectInterface_0B(void);                                           // 0B - pure
		virtual void GASObjectInterface_0C(void);                                           // 0C
		virtual void Set__proto__(GASStringContext* a_stringContext, GASObject* a_object);  // 0D - pure
		virtual void GASObjectInterface_0E(void);                                           // 0E
		virtual void GASObjectInterface_0F(void);                                           // 0F
		virtual void GASObjectInterface_10(void);                                           // 10
		virtual void GASObjectInterface_11(void);                                           // 11
		virtual void GASObjectInterface_12(void);                                           // 12
		virtual void GASObjectInterface_13(void);                                           // 13
		virtual void GASObjectInterface_14(void);                                           // 14

		// members
		std::uint64_t unk08;      // 08
		GASObject*    __proto__;  // 10 - smart pointer
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASObjectInterface) == 0x18);
}
