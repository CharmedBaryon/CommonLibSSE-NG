#pragma once

#include "RE/B/BSExtraData.h"

namespace RE
{
	class ExtraCannotWear : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCannotWear;
		inline static constexpr auto VTABLE = VTABLE_ExtraCannotWear;
		inline static auto           EXTRADATATYPE = ExtraDataType::kCannotWear;

		ExtraCannotWear();
		~ExtraCannotWear() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kCannotWear; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraCannotWear) == 0x10);
};
