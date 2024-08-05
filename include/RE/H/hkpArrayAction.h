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
		void GetEntities(hkArray<hkpEntity*>& a_entitiesOut) override;  // 04
		void EntityRemovedCallback(hkpEntity* a_entity) override;       // 06

		// members
		hkArray<hkpEntity*> entities;  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpArrayAction) == 0x40);
}
