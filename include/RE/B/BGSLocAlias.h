#pragma once

#include "RE/B/BGSBaseAlias.h"

namespace RE
{
	class TESCondition;

	class BGSLocAlias : public BGSBaseAlias
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSLocAlias;
		inline static constexpr auto VTABLE = VTABLE_BGSLocAlias;
		inline static constexpr auto VMTYPEID = static_cast<VMTypeID>(141);

		~BGSLocAlias() override;  // 00

		// members
		std::uint64_t unk28;       // 28
		std::uint64_t unk30;       // 30
		std::uint64_t unk38;       // 38
		std::uint64_t unk40;       // 40
		std::uint64_t unk48;       // 48
		std::uint64_t unk50;       // 50
		TESCondition* conditions;  // 58
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSLocAlias) == 0x60);
}
