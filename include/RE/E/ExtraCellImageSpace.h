#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESImageSpace;

	class ExtraCellImageSpace : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellImageSpace;
		inline static constexpr auto VTABLE = VTABLE_ExtraCellImageSpace;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCellImageSpace;

		~ExtraCellImageSpace() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kCellImageSpace; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return imageSpace != a_rhs->imageSpace; }

		// members
		TESImageSpace* imageSpace;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraCellImageSpace) == 0x18);
}
