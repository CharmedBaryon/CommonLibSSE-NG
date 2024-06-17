#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpAction : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpAction;
		inline static constexpr auto VTABLE = VTABLE_hkpAction;

		virtual ~hkpAction() override;  // 00

		// add
		virtual void Unk_03(void) = 0;  // 03
		virtual void Unk_04(void) = 0;  // 04
		virtual void Unk_05(void);      // 05
		virtual void Unk_06(void) = 0;  // 06
		virtual void Unk_07(void) = 0;  // 07

		// members
		hkpWorld*            world;     // 10
		hkpSimulationIsland* island;    // 18
		std::uint64_t        userData;  // 20
		hkStringPtr          name;      // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpAction) == 0x30);
}
