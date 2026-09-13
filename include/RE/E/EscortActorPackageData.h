#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class TESPackage;

	class EscortActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_EscortActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_EscortActorPackageData;

		~EscortActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// Init(target, escortPackage, ...) writes target/escortPackage/escortPackageData below;
		// exact parameter ABI unconfirmed, not exposed here.

		// members
		ObjectRefHandle target;             // 08
		std::uint32_t   pad0C;              // 0C
		TESPackage*     escortPackage;      // 10
		void*           escortPackageData;  // 18 - TESPackage::GetEscortPackageData() result
		std::uint32_t   unk20;              // 20
		std::uint32_t   pad24;              // 24
		void*           unk28;              // 28
	};
	static_assert(sizeof(EscortActorPackageData) == 0x30);
}
