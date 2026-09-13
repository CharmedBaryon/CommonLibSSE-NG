#pragma once

#include "RE/B/BSPathingDoor.h"
#include "RE/B/BSPathingLocation.h"

namespace RE
{
	class PathingDoor : public BSPathingDoor
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingDoor;
		inline static constexpr auto VTABLE = VTABLE_PathingDoor;

		~PathingDoor() override;  // 00

		void Unk_01(void) override;  // 01
		void Unk_02(void) override;  // 02
		void Unk_03(void) override;  // 03
		void Unk_04(void) override;  // 04
		void Unk_05(void) override;  // 05
		void Unk_06(void) override;  // 06
		void Unk_07(void) override;  // 07
		void Unk_08(void) override;  // 08
		void Unk_09(void) override;  // 09
		void Unk_0A(void) override;  // 0A
		void Unk_0B(void) override;  // 0B
		void Unk_0C(void) override;  // 0C
		void Unk_0D(void) override;  // 0D
		void Unk_0E(void) override;  // 0E
		void Unk_0F(void) override;  // 0F
		void Unk_10(void) override;  // 10
		void Unk_11(void) override;  // 11

		// members
		std::uint32_t     unk10;             // 10
		std::uint32_t     refHandle;         // 14 - TESObjectREFR handle (NullRefHandleId when none)
		BSPathingLocation forwardLocation;   // 18 - flag bit checked: forwardLocation.flags & 0x40
		BSPathingLocation backwardLocation;  // 48
	};
	STATIC_ASSERT_SIZE(PathingDoor, 0x78);
}
