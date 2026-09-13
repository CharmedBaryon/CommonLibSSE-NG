#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class UseWeaponActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_UseWeaponActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_UseWeaponActorPackageData;

		~UseWeaponActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// members
		ObjectRefHandle target;  // 08
		std::uint32_t   pad0C;   // 0C
	};
	static_assert(sizeof(UseWeaponActorPackageData) == 0x10);
}
