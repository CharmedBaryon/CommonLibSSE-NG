#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/ActorValues.h"
#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterRestore : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterRestore;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterRestore;

		~CombatMagicCasterRestore() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                        // 02
		void                          SaveGame(BGSSaveGameBuffer* a_buf) override;                     // 03
		void                          LoadGame(BGSLoadGameBuffer* a_buf) override;                     // 04
		CombatInventoryItem::CATEGORY GetCategory() override;                                          // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;   // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;    // 07
		void                          NotifyStartCast(CombatController* a_combatController) override;  // 0B
		void                          NotifyStopCast(CombatController* a_combatController) override;   // 0C

		// members
		AITimeStamp   concentrationCastTimeStamp;  // 20
		std::uint32_t unk24;                       // 24
		ActorValue    primaryAV;                   // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterRestore) == 0x30);
}
