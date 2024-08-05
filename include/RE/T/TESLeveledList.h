#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/C/ContainerItemExtra.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	class TESFaction;
	class TESForm;
	class TESGlobal;

	struct LEVELED_OBJECT
	{
	public:
		// members
		TESForm*            form;       // 00 - LVLO~
		std::uint16_t       count;      // 08
		std::uint16_t       level;      // 0A - ~LVLO
		std::uint32_t       pad0C;      // 0C
		ContainerItemExtra* itemExtra;  // 10 - COED
	};
	static_assert(sizeof(LEVELED_OBJECT) == 0x18);

	struct CALCED_OBJECT
	{
	public:
		// members
		TESForm*           form;           // 00
		std::uint16_t      count;          // 08
		std::uint16_t      pad0A;          // 08
		std::uint32_t      pad0C;          // 0C
		ContainerItemExtra containerItem;  // 10
	};
	static_assert(sizeof(CALCED_OBJECT) == 0x28);

	class TESLeveledList : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESLeveledList;
		inline static constexpr auto VTABLE = VTABLE_TESLeveledList;

		enum Flag : std::uint8_t  // LVLF
		{
			kCalculateFromAllLevelsLTOrEqPCLevel = 1 << 0,
			kCalculateForEachItemInCount = 1 << 1,
			kUseAll = 1 << 2,
			kSpecialLoot = 1 << 3
		};

		~TESLeveledList() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual std::uint8_t GetChanceNone();                                      // 04 - { if (global) return global->value; else return chanceNone; }
		[[nodiscard]] virtual bool         GetMultCalc();                                        // 05 - { return (flags >> 1) & 1; }
		[[nodiscard]] virtual std::int32_t GetLevDifferenceMax();                                // 06 - { return 0; }
		[[nodiscard]] virtual bool         GetCanContainFormsOfType(FormType a_type) const = 0;  // 07

		void                                CalculateCurrentFormList(std::uint16_t a_level, std::int16_t a_count, BSScrapArray<CALCED_OBJECT>& a_calcedObjects, std::uint32_t a_arg5, bool a_usePlayerLevel);
		[[nodiscard]] std::vector<TESForm*> GetContainedForms() const;

		// members
		SimpleArray<LEVELED_OBJECT> entries;       // 08
		std::int8_t                 chanceNone;    // 10 - LVLD
		Flag                        llFlags;       // 11 - LVLF
		std::uint8_t                numEntries;    // 12 - LLCT
		std::uint8_t                unk13;         // 13
		std::uint32_t               pad14;         // 14
		void*                       unk18;         // 18
		TESGlobal*                  chanceGlobal;  // 20 - LVLG
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESLeveledList) == 0x28);
}
