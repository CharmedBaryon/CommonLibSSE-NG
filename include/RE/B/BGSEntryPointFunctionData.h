#pragma once

#include "RE/F/FormTypes.h"

namespace RE
{
	class BGSPerkEntry;
	class TESFile;

	class BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointFunctionData;
		inline static constexpr auto VTABLE = VTABLE_BGSEntryPointFunctionData;

		enum class ENTRY_POINT_FUNCTION_DATA
		{
			kInvalid = 0,
			kOneValue = 1,
			kTwoValue = 2,
			kLeveledList = 3,
			kActivateChoice = 4,
			kSpellItem = 5,
			kBooleanGraphVariable = 6,
			kText = 7
		};

		virtual ~BGSEntryPointFunctionData();  // 00

		[[nodiscard]] virtual ENTRY_POINT_FUNCTION_DATA GetType() const = 0;                                     // 01
		virtual bool                                    LoadImpl(TESFile* a_mod) = 0;                            // 02
		virtual void                                    InitItem(TESForm* a_form);                               // 03 - { return; }
		virtual void                                    ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_perkEntry);  // 04 - { return; }
		virtual std::uint16_t                           GetID();                                                 // 05 - { return 0xFFFF; }
		virtual void                                    SetParentPerk(BGSPerk* a_perk);                          // 06 - { return; }
		virtual BGSPerk*                                GetParentPerk();                                         // 07 - { return 0; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSEntryPointFunctionData) == 0x8);
}
