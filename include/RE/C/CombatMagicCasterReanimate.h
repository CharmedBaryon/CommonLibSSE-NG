#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterReanimate : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterReanimate;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterReanimate;

		~CombatMagicCasterReanimate() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                                     // 02
		void                          SaveGame(BGSSaveGameBuffer* a_buf) override;                                  // 03
		void                          LoadGame(BGSLoadGameBuffer* a_buf) override;                                  // 04
		CombatInventoryItem::CATEGORY GetCategory() override;                                                       // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;                // 06
		void*                         GetMagicTarget(CombatController* a_combatController) const override;          // 0A
		void                          NotifyStopCast(CombatController* a_combatController) override;                // 0C
		void                          SetupAimController(CombatProjectileAimController* a_aimController) override;  // 0D

		// members
		NiPointer<CombatProjectileAimController> aimController;    // 20
		ActorHandle                              reanimateTarget;  // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterReanimate) == 0x30);
}
