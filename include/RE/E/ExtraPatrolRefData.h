#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct PatrolRefData
	{
		std::uint64_t unk00;  // 00
		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
		std::uint64_t unk18;  // 18
		std::uint64_t unk20;  // 20
	};
	static_assert(sizeof(PatrolRefData) == 0x28);

	class ExtraPatrolRefData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPatrolRefData;
		inline static constexpr auto VTABLE = VTABLE_ExtraPatrolRefData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPatrolRefData;

		~ExtraPatrolRefData() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kPatrolRefData; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02

		// members
		PatrolRefData* patrolData;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraPatrolRefData) == 0x18);
}
