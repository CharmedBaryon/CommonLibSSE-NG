#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPlane.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundAABB;
	class BSTriShape;
	class NiAVObject;
	class TESWaterForm;
	class TESWaterDisplacement;
	class TESWaterNormals;
	class TESWaterReflections;

	class TESWaterObject : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWaterObject;
		inline static constexpr auto VTABLE = VTABLE_TESWaterObject;

		virtual ~TESWaterObject();  // 00

		// members
		NiPlane                               plane;              // 10
		NiPointer<BSTriShape>                 shape;              // 20
		NiPointer<NiAVObject>                 waterRippleObject;  // 28
		TESWaterForm*                         waterType;          // 30
		std::uint64_t                         unk38;              // 38
		NiPointer<TESWaterReflections>        reflections;        // 40
		NiPointer<TESWaterDisplacement>       displacement;       // 48
		NiPointer<TESWaterNormals>            normals;            // 50
		BSTArray<NiPointer<BSMultiBoundAABB>> multiBounds;        // 58
		std::uint8_t                          flags;              // 70
		std::uint8_t                          pad71;              // 71
		std::uint16_t                         pad72;              // 72
		std::uint32_t                         pad74;              // 74
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESWaterObject) == 0x78);
}
