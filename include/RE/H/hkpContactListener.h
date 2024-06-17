#pragma once

namespace RE
{
	struct hkpCollisionEvent;
	struct hkpContactPointEvent;
	struct hkpContactPointAddedEvent;
	struct hkpContactPointRemovedEvent;
	struct hkpContactProcessEvent;

	class hkpContactListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpContactListener;
		inline static constexpr auto VTABLE = VTABLE_hkpContactListener;

		// add
		virtual void ContactPointCallback(const hkpContactPointEvent&) {}   // 00
		virtual void CollisionAddedCallback(const hkpCollisionEvent&) {}    // 01
		virtual void CollisionRemovedCallback(const hkpCollisionEvent&) {}  // 02

		virtual ~hkpContactListener() = default;  // 04

		virtual void ContactPointAddedCallback(hkpContactPointAddedEvent&) {}      // 05
		virtual void ContactPointRemovedCallback(hkpContactPointRemovedEvent&) {}  // 06
		virtual void ContactProcessCallback(hkpContactProcessEvent&) {}            // 07
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpContactListener) == 0x8);
}
