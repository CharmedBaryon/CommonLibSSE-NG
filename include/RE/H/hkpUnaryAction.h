#pragma once

#include "RE/H/hkpAction.h"

namespace RE
{
	class hkpEntity;

	class hkpUnaryAction : public hkpAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpUnaryAction;
		inline static constexpr auto VTABLE = VTABLE_hkpUnaryAction;

		virtual ~hkpUnaryAction() override;  // 00

		// override (hkpAction)
		void GetEntities(hkArray<hkpEntity*>& a_entitiesOut) override;  // 04
		void EntityRemovedCallback(hkpEntity* a_entity) override;       // 06

		// members
		hkpEntity* entity;  // 30
	};
	static_assert(sizeof(hkpUnaryAction) == 0x38);
}
