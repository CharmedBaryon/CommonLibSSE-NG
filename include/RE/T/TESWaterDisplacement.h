#pragma once

#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class TESWaterForm;

	class TESWaterDisplacement : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWaterDisplacement;
		inline static constexpr auto VTABLE = VTABLE_TESWaterDisplacement;

		virtual ~TESWaterDisplacement();  // 00

		// members
		TESWaterForm*         waterType;             // 10
		float                 waterHeight;           // 18
		std::uint32_t         unk1C;                 // 1C
		std::uint32_t         flags;                 // 20
		std::uint32_t         pad24;                 // 24
		NiPointer<NiAVObject> displacementGeometry;  // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESWaterDisplacement) == 0x30);
}
