#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class bhkWorld;
	class CellMopp;

	class ExtraHavok : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraHavok;
		inline static constexpr auto VTABLE = VTABLE_ExtraHavok;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kHavok;

		~ExtraHavok() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kHavok; }

		// members
		NiPointer<bhkWorld> world;     // 10
		NiPointer<CellMopp> cellMopp;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraHavok) == 0x20);
}
