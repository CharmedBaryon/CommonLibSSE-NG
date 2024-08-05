#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraObjectHealth : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraObjectHealth;
		inline static constexpr auto VTABLE = VTABLE_ExtraObjectHealth;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kObjectHealth;

		~ExtraObjectHealth() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kObjectHealth; }

		// members
		float         health;  // 10
		std::uint32_t pad14;   // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraObjectHealth) == 0x18);
}
