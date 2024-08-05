#pragma once

#include "RE/B/BGSEntryPointFunctionData.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	class BGSEntryPointFunctionDataText : public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointFunctionDataText;
		inline static constexpr auto VTABLE = VTABLE_BGSEntryPointFunctionDataText;

		~BGSEntryPointFunctionDataText() override;  // 00

		// override (BGSEntryPointFunctionData)
		ENTRY_POINT_FUNCTION_DATA GetType() const override;           // 01 - { return kText; }
		bool                      LoadImpl(TESFile* a_mod) override;  // 02

		// members
		BSFixedString text;  // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSEntryPointFunctionDataText) == 0x10);
}
