#pragma once

#include "RE/B/BSScriptObjectBindPolicy.h"
#include "RE/B/BSTHashMap.h"

namespace RE
{
	namespace SkyrimScript
	{
		class ObjectBindPolicy : public BSScript::ObjectBindPolicy
		{
		public:
			inline static constexpr auto RTTI = RTTI_SkyrimScript__ObjectBindPolicy;
			inline static constexpr auto VTABLE = VTABLE_SkyrimScript__ObjectBindPolicy;

			~ObjectBindPolicy() override;  // 00

			// override (BSScript::ObjectBindPolicy)
			void Unk_01(VMHandle a_handle) override;  // 01
			void Unk_02(VMHandle a_handle) override;  // 02
			void Unk_03(VMHandle a_handle) override;  // 03
			void Unk_04() override;                   // 04
			void Unk_05(void) override;               // 05 - { return 0; }
			void Unk_06(void) override;               // 06
			void Unk_07(void) override;               // 07
			void Unk_08(void) override;               // 08
			void Unk_09(void) override;               // 09
			void Unk_0A(void) override;               // 0A
			void Unk_0B(void) override;               // 0B
			void Unk_0C(void) override;               // 0C

			// members
			mutable BSSpinLock           unk50;  // 50
			std::byte                    unk58;  // 58
			std::byte                    unk59;  // 59
			std::byte                    unk5A;  // 5A
			BSTHashMap<UnkKey, UnkValue> unk60;  // 60
			std::uint64_t                unk90;  // 90
			std::uint64_t                unk98;  // 98
			std::uint64_t                unkA0;  // A0
			BSTSet<VMHandle>             unkA8;  // A8
		};
		static_assert(sizeof(ObjectBindPolicy) == 0xD8);
	}
}
