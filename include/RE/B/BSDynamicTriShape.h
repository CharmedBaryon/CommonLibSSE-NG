#pragma once

#include "RE/B/BSTriShape.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSDynamicTriShape : public BSTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSDynamicTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSDynamicTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSDynamicTriShape;

		struct DYNAMIC_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT            \
	void*         dynamicData; /* 00 */ \
	BSSpinLock    lock;        /* 08 */ \
	std::uint32_t dataSize;    /* 10 */ \
	std::uint32_t frameCount;  /* 14 */ \
	std::uint32_t unk178;      /* 18 */ \
	std::uint32_t unk17C;      /* 1C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(DYNAMIC_TRISHAPE_RUNTIME_DATA) == 0x20);

		// override (BSTriShape)
		const NiRTTI*      GetRTTI() const override;                           // 02
		BSDynamicTriShape* AsDynamicTriShape() override;                       // 0C
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void               LoadBinary(NiStream& a_stream) override;            // 18
		void               LinkObject(NiStream& a_stream) override;            // 19 - { BSTriShape::LinkObject(a_stream); }
		bool               RegisterStreamables(NiStream& a_stream) override;   // 1A - { return BSTriShape::RegisterStreamables(a_stream); }
		void               SaveBinary(NiStream& a_stream) override;            // 1B
		bool               IsEqual(NiObject* a_object) override;               // 1C

		RUNTIME_DATA_ACCESSOR_EX(DYNAMIC_TRISHAPE_RUNTIME_DATA, GetDynamicTrishapeRuntimeData, 0x160, 0x1A0);
		BSDynamicTriShape* ctor()
		{
			using func_t = decltype(&BSDynamicTriShape::ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(69564, 70948) };
			return func(this);
		}

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 160, 1A0
#endif
	};
	STATIC_ASSERT_SIZE(BSDynamicTriShape, 0x180, 0x180, 0x1C0, 0x110);
}
#undef RUNTIME_DATA_CONTENT
