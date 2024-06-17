#pragma once

#include "RE/H/hkpAction.h"

namespace RE
{
	class hkpArrayAction : public hkpAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpArrayAction;
		inline static constexpr auto VTABLE = VTABLE_hkpArrayAction;

		virtual ~hkpArrayAction() override;  // 00

		// add
		virtual void Unk_04(void) override;  // 04
		virtual void Unk_06(void) override;  // 06

		// members
		hkArray<hkpEntity*> entities;  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpArrayAction) == 0x40);
}
