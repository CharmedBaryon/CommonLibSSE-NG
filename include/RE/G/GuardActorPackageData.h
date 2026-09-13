#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class GuardActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_GuardActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_GuardActorPackageData;

		~GuardActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// members
		std::uint32_t   unk08;         // 08
		ObjectRefHandle target;        // 0C - set via sub_140710EA0 (target setter)
		std::uint32_t   unk10;         // 10
		float           warningTimer;  // 14 - default fWarningTimer
		std::uint8_t    unk18[0x10];   // 18 - untouched by the ctor
		void*           unk28;         // 28 - owned; freed in the dtor
		bool            unk30;         // 30
		std::uint8_t    pad31[7];      // 31
	};
	static_assert(sizeof(GuardActorPackageData) == 0x38);
}
