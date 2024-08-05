#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESLevItem;

	class ExtraLeveledItemBase : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraLeveledItemBase;
		inline static constexpr auto VTABLE = VTABLE_ExtraLeveledItemBase;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kLeveledItemBase;

		~ExtraLeveledItemBase() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kLeveledItemBase; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return levItem != a_rhs->levItem; }

		// members
		TESLevItem* levItem;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraLeveledItemBase) == 0x18);
}
