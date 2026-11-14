#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BGSInstancedQuestObjective.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class PatrolActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_PatrolActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_PatrolActorPackageData;

		~PatrolActorPackageData() override;  // 00

		// override (ActorPackageData)
		void Unk_01(void) override;  // 01
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06

		// members
		std::uint32_t                        unk08;        // 08 - observed 5
		std::uint32_t                        pad0C;        // 0C
		ObjectRefHandle                      target;       // 10
		std::uint32_t                        pad14;        // 14
		BSTArray<BGSInstancedQuestObjective> objectives;   // 18 - sub_1407110F0 constructs it via ::Ctor
		ObjectRefHandle                      refHandle30;  // 30
		bool                                 unk34;        // 34
		bool                                 unk35;        // 35 - observed true
		std::uint16_t                        pad36;        // 36
		std::uint32_t                        unk38;        // 38
		std::uint32_t                        pad3C;        // 3C
	};
	static_assert(sizeof(PatrolActorPackageData) == 0x40);
}
