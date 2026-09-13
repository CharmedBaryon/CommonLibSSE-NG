#pragma once

#include <array>
#include <cstdint>

#include "RE/B/BSTasklet.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class bhkRigidBody;

	class CellMopp : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CellMopp;
		inline static constexpr auto VTABLE = VTABLE_CellMopp;

		class HeightFieldWeldingTasklet : public BSTasklet
		{
		public:
			inline static constexpr auto RTTI = RTTI_CellMopp__HeightFieldWeldingTasklet;
			inline static constexpr auto VTABLE = VTABLE_CellMopp__HeightFieldWeldingTasklet;

			~HeightFieldWeldingTasklet() override;  // 00

			// members
			bool                         unk08;     // 08 - false at construction
			void*                        unk10;     // 10 - null at construction
			bool                         unk18;     // 18 - true at construction
			std::uint32_t                unk1C;     // 1C - 0 at construction
			std::uint8_t                 unk20[8];  // 20 - not yet identified
			hkRefPtr<hkReferencedObject> target;    // 28 - released via RemoveReference in the dtor
		};
		static_assert(sizeof(HeightFieldWeldingTasklet) == 0x30);

		~CellMopp() override;  // 00

		// members
		void*                                    unk10;            // 10 - null at construction
		std::array<HeightFieldWeldingTasklet, 4> weldingTasklets;  // 18 - one per quadrant
		NiTObjectArray<NiPointer<bhkRigidBody>>  rigidBodies;      // D8
	};
	static_assert(sizeof(CellMopp) == 0xF0);
}
