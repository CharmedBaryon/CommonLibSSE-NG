#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/bhkBackfaceContactListener.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class ActorCause;
	class bhkRigidBody;
	class TESObjectREFR;

	class FOCollisionListener :
		public bhkBackfaceContactListener,           // 00
		public BSTSingletonSDM<FOCollisionListener>  // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_FOCollisionListener;
		inline static constexpr auto VTABLE = VTABLE_FOCollisionListener;

		struct ObjectDamageImpactData
		{
		public:
			// members
			NiPointer<bhkRigidBody> body;        // 00
			float                   damage;      // 04
			std::uint32_t           pad08;       // 08
			NiPointer<ActorCause>   actorCause;  // 10
		};
		static_assert(sizeof(ObjectDamageImpactData) == 0x18);

		// override (bhkBackfaceContactListener)
		void ContactPointCallback(const hkpContactPointEvent&) override;  // 00

		~FOCollisionListener() override;  // 00

		static FOCollisionListener* GetSingleton()
		{
			REL::Relocation<FOCollisionListener**> singleton{ RELOCATION_ID(514284, 400444) };
			return *singleton;
		}

		// members
		BSTArray<ObjectDamageImpactData> damageImpacts;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FOCollisionListener) == 0x28);
}
