#pragma once

#include "RE/B/BGSEntryPointFunctionData.h"
#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class BGSEntryPointFunctionDataActivateChoice : public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSEntryPointFunctionDataActivateChoice;
		inline static constexpr auto VTABLE = VTABLE_BGSEntryPointFunctionDataActivateChoice;

		enum class Flag
		{
			kNone = 0,
			kRunImmediately = 1,
			kReplaceDefault = 2
		};

		~BGSEntryPointFunctionDataActivateChoice() override;  // 00

		// override (BGSEntryPointFunctionData)
		ENTRY_POINT_FUNCTION_DATA GetType() const override;                 // 01 - { return kDataActivateChoice; }
		bool                      LoadImpl(TESFile* a_mod) override;        // 02
		void                      InitItem(TESForm* a_form) override;       // 03
		std::uint16_t             GetID() override;                         // 05
		void                      SetParentPerk(BGSPerk* a_perk) override;  // 06 - { perk = a_perk; }
		BGSPerk*                  GetParentPerk() override;                 // 07 - { return perk; }

		[[nodiscard]] bool ReplacesDefault() const;
		[[nodiscard]] bool RunsImmediately() const;

		// members
		BSFixedString                         label;         // 08
		BGSPerk*                              perk;          // 10
		SpellItem*                            appliedSpell;  // 18
		stl::enumeration<Flag, std::uint16_t> flags;         // 20
		std::uint16_t                         id;            // 22
		std::uint32_t                         pad24;         // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSEntryPointFunctionDataActivateChoice) == 0x28);
}
