#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/B/BeamProjectile.h"
#include "RE/E/Explosion.h"

namespace RE
{
	class ChainExplosion :
		public Explosion,                               // 00
		public BSTEventSink<BeamProjectileImpactEvent>  // 140
	{
	public:
		inline static constexpr auto RTTI = RTTI_ChainExplosion;
		inline static constexpr auto VTABLE = VTABLE_ChainExplosion;

		~ChainExplosion() override;  // 00

#ifndef SKYRIM_CROSS_VR
		// override (Explosion)
		void Initialize() override;           // A2
		void Update(float a_delta) override;  // A3
		void FindTargets() override;          // A4 - { return; }
#endif

		// override (BSTEventSink<BeamProjectileImpactEvent>)
		BSEventNotifyControl ProcessEvent(const BeamProjectileImpactEvent* a_event, BSTEventSource<BeamProjectileImpactEvent>* a_eventSource) override;  // 01

		// members
		std::uint8_t unk148[0x58];  // 148 - chain-link bookkeeping (next-target handle, a component pointer, a bound BGSDestructibleObjectForm*, and per-link effectiveness floats); not yet broken out field-by-field

	private:
		TES_HEAP_REDEFINE_NEW();
	};
	STATIC_ASSERT_SIZE(ChainExplosion, 0x1A0, 0x1A8, 0x1A0);
}
