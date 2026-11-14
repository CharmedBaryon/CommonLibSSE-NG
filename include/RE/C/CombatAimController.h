#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class CombatController;
	class MagicCaster;

	class CombatAimController : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAimController;
		inline static constexpr auto VTABLE = VTABLE_CombatAimController;

		enum class PRIORITY : uint32_t
		{
			kUnk0,
			kUnk1,
			kUnk2,
			kUnk3,
			kUnk4,
			kUnk5
		};

		enum class Flags : uint32_t
		{
			kAiming = 1 << 0,
			kUpdating = 1 << 1,
			kUnk2 = 1 << 2,
			kDisable = 1 << 3,
			kUnk4 = 1 << 4,
			kUnk5 = 1 << 5,
			kUnk6 = 1 << 6
		};
		using FLAGS = stl::enumeration<Flags, uint32_t>;

		~CombatAimController() override;  // 00

		// override (CombatObject)
		std::uint32_t GetObjectType() override;  // 02

		// add
		virtual bool                               CanFireAtTarget(const NiPoint3* a_arg2, const NiPoint3* a_arg3);  // 05 - { return true; }
		virtual bool                               CanFireNow();                                                     // 06 - { return true; }
		virtual bool                               IsFacingTarget(float a_tolerance);                                // 07
		virtual void                               Update();                                                         // 08
		[[nodiscard]] virtual CombatAimController* Clone();                                                          // 09
		virtual void                               OnWeaponTypeChanged();                                            // 0A - { return; }

		// members
		MagicCaster*      mcaster;         // 10 -- or weap?
		NiPoint3          P;               // 18
		uint32_t          field_24;        // 24
		CombatController* combat_control;  // 28
		ActorHandle       target;          // 30
		PRIORITY          priority1;       // 34
		PRIORITY          priority2;       // 38
		FLAGS             flags;           // 3C
		AITimer           timer;           // 40
	};
	static_assert(sizeof(CombatAimController) == 0x48);
}
