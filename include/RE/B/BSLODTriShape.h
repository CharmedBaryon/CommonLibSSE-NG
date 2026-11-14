#pragma once

#include "RE/N/NiTriShape.h"

#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSLODTriShape : public NiTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLODTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSLODTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSLODTriShape;

		struct LOD_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                     \
	std::uint32_t lodTriangleCounts[3]; /* 00 */ \
	std::uint32_t pad0C;                /* 0C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(LOD_TRISHAPE_RUNTIME_DATA) == 0x10);

		~BSLODTriShape() override;  // 00

		// override (NiTriShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C

		RUNTIME_DATA_ACCESSOR_EX(LOD_TRISHAPE_RUNTIME_DATA, GetLODTriShapeRuntimeData, 0x138, 0x160);

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 138, 160 - triangle count per LOD level
#endif
	};
	STATIC_ASSERT_SIZE(BSLODTriShape, 0x148, 0x148, 0x170, 0x110);
}
#undef RUNTIME_DATA_CONTENT
