#pragma once

#include "RE/B/BGSEntryPointFunctionData.h"

namespace RE
{
	class SpellItem;

	class BGSEntryPointFunctionDataSpellItem : public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointFunctionDataSpellItem;
		inline static constexpr auto VTABLE = VTABLE_BGSEntryPointFunctionDataSpellItem;

		// Override (BGSEntryPointFunctionData)
		[[nodiscard]] virtual ENTRY_POINT_FUNCTION_DATA GetType() const override;            // 1
		virtual bool                                    LoadImpl(TESFile* a_mod) override;   // 2
		virtual void                                    InitItem(TESForm* a_form) override;  // 3

		// Member variables
		SpellItem* spell;  // 8
	};
	static_assert(offsetof(BGSEntryPointFunctionDataSpellItem, spell) == 0x8);
	static_assert(sizeof(BGSEntryPointFunctionDataSpellItem) == 0x10);
}
