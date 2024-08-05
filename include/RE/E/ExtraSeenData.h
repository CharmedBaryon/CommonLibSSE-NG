#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class SeenData;

	class ExtraSeenData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraSeenData;
		inline static constexpr auto VTABLE = VTABLE_ExtraSeenData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kSeenData;

		~ExtraSeenData() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kSeenData; }

		// members
		SeenData* seenData;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraSeenData) == 0x18);
}
