#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class ActorCause;
	template <class>
	class NiPointer;

	class SpawnHazardEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_SpawnHazardEffect;
		inline static constexpr auto VTABLE = VTABLE_SpawnHazardEffect;

		// override (ActiveEffect)
		virtual void HandleQueuedStart() override;  // 0F
		virtual ~SpawnHazardEffect();               // 13
		virtual void Start() override;              // 14
		virtual void Finish() override;             // 15

		// members
		NiPointer<ActorCause> actorCause;  // 90
		ObjectRefHandle       hazard;      // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SpawnHazardEffect) == 0xA0);
}
