#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class ActorValueInfo;
	class BGSPerk;

	class BGSSkillPerkTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSkillPerkTreeNode;
		inline static constexpr auto VTABLE = VTABLE_BGSSkillPerkTreeNode;

		BGSSkillPerkTreeNode(std::int32_t a_index, ActorValueInfo* a_avInfo);

		virtual ~BGSSkillPerkTreeNode() = default;  // 00

		TES_HEAP_REDEFINE_NEW();

		// members
		std::uint32_t                   index;               // 08 - INAM
		std::uint32_t                   unk0C;               // 0C
		BSTArray<BGSSkillPerkTreeNode*> children;            // 10 - CNAM
		BSTArray<BGSSkillPerkTreeNode*> parents;             // 28
		BGSPerk*                        perk;                // 40 - PNAM
		std::uint32_t                   unk48;               // 48 - FNAM
		std::uint32_t                   perkGridX;           // 4C - XNAM
		std::uint32_t                   perkGridY;           // 50 - YNAM
		std::uint32_t                   unk54;               // 54
		ActorValueInfo*                 associatedSkill;     // 58 - SNAM
		float                           horizontalPosition;  // 60 - HNAM
		float                           verticalPosition;    // 64 - VNAM
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSkillPerkTreeNode) == 0x68);
}
