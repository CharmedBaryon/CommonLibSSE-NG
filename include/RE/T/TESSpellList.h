#pragma once

#include "RE/B/BaseFormComponent.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	class SpellItem;
	class TESLevSpell;
	class TESShout;

	class TESSpellList : BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESSpellList;
		inline static constexpr auto VTABLE = VTABLE_TESSpellList;

		struct SpellData  // SPLO
		{
			SpellData();
			~SpellData() = default;

			bool AddLevSpell(TESLevSpell* a_levSpell);
			bool AddLevSpells(const std::vector<TESLevSpell*>& a_levSpells);
			bool AddShout(TESShout* a_shout);
			bool AddShouts(const std::vector<TESShout*>& a_shouts);
			bool AddSpell(SpellItem* a_spell);
			bool AddSpells(const std::vector<SpellItem*>& a_spells);

			std::optional<std::uint32_t> GetIndex(const SpellItem* a_spell) const;
			std::optional<std::uint32_t> GetIndex(const TESLevSpell* a_levSpell) const;
			std::optional<std::uint32_t> GetIndex(const TESShout* a_shout) const;

			bool RemoveLevSpell(TESLevSpell* a_levSpell);
			bool RemoveLevSpells(const std::vector<TESLevSpell*>& a_levSpells);
			bool RemoveShout(TESShout* a_shout);
			bool RemoveShouts(const std::vector<TESShout*>& a_shouts);
			bool RemoveSpell(SpellItem* a_spell);
			bool RemoveSpells(const std::vector<SpellItem*>& a_spells);

			TES_HEAP_REDEFINE_NEW();

			SpellItem**   spells;        // 00
			TESLevSpell** levSpells;     // 08
			TESShout**    shouts;        // 10
			std::uint32_t numSpells;     // 18
			std::uint32_t numlevSpells;  // 1C
			std::uint32_t numShouts;     // 20
			std::uint32_t pad24;         // 24

		private:
			void CopySpellList(const std::vector<TESLevSpell*>& a_copiedData);
			void CopySpellList(const std::vector<TESShout*>& a_copiedData);
			void CopySpellList(const std::vector<SpellItem*>& a_copiedData);
		};
		static_assert(sizeof(SpellData) == 0x28);

		~TESSpellList() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { return; }
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// members
		SpellData* actorEffects;  // 08 - SPLO
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESSpellList) == 0x10);
}
