#pragma once

#include "RE/B/BSTriShape.h"

#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSMeshLODTriShape : public BSTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMeshLODTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMeshLODTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSMeshLODTriShape;

		struct MESH_LOD_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                     \
	std::uint32_t lodTriangleCounts[3]; /* 00 */ \
	std::uint32_t pad0C;                /* 0C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(MESH_LOD_TRISHAPE_RUNTIME_DATA) == 0x10);

		~BSMeshLODTriShape() override;  // 00

		// override (BSTriShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C

		RUNTIME_DATA_ACCESSOR_EX(MESH_LOD_TRISHAPE_RUNTIME_DATA, GetMeshLODTriShapeRuntimeData, 0x160, 0x1A0);

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 160, 1A0 - triangle count per LOD level
#endif
	};
	STATIC_ASSERT_SIZE(BSMeshLODTriShape, 0x170, 0x170, 0x1B0, 0x110);
}
#undef RUNTIME_DATA_CONTENT
