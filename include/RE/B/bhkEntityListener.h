#pragma once

#include "RE/H/hkpEntityListener.h"

namespace RE
{
	class bhkWorldObject;
	struct hkpRootCdPoint;

	class bhkEntityListener : public hkpEntityListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkEntityListener;
		inline static constexpr auto VTABLE = VTABLE_bhkEntityListener;

		~bhkEntityListener() override;  // 00

		// override (hkpEntityListener)
		void EntityAddedCallback(hkpEntity* a_entity) override;    // 01
		void EntityRemovedCallback(hkpEntity* a_entity) override;  // 02

		// add
		virtual void            Update(float a_delta) = 0;                             // 06
		virtual bool            ContactPointAddedCallback(hkpRootCdPoint& a_point);    // 07 - { return false; }
		virtual bool            ContactPointRemovedCallback(hkpRootCdPoint& a_point);  // 08 - { return false; }
		virtual bhkWorldObject* GetMatchingWorldObject(hkpEntity* a_entity);           // 09 - the entity's world object if its collision mask passes this listener's filter

		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
	};
	static_assert(sizeof(bhkEntityListener) == 0x18);
}
