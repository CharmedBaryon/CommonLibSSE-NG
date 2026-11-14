#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/T/TESCustomPackageData.h"

namespace RE
{
	// Runtime ActorPackageData counterpart to the on-form TESCustomPackageData; not the same class.
	class CustomActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_CustomActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_CustomActorPackageData;

		~CustomActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// members
		BGSPackageDataList data;   // 08
		void*              unk20;  // 20
	};
	static_assert(sizeof(CustomActorPackageData) == 0x28);
}
