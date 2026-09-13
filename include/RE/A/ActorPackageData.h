#pragma once

namespace RE
{
	// Base for the per-package-type runtime data hung off ActorPackage::data (e.g.
	// EscortActorPackageData, GuardActorPackageData, PatrolActorPackageData, SandBoxActorPackageData,
	// UseWeaponActorPackageData, CustomActorPackageData). Holds only the vtable pointer -- derived
	// classes append their own fields starting immediately at offset 08.
	class ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_ActorPackageData;

		virtual ~ActorPackageData();  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void);      // 02
		virtual void Unk_03(void);      // 03
		virtual void Unk_04(void);      // 04
		virtual void Unk_05(void) = 0;  // 05
		virtual void Unk_06(void) = 0;  // 06
		virtual void Unk_07(void);      // 07
		virtual void Unk_08(void);      // 08
		virtual void Unk_09(void);      // 09
	};
	static_assert(sizeof(ActorPackageData) == 0x8);
}
