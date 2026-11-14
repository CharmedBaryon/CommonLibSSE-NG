#include "RE/H/hkpAabbPhantom.h"

namespace RE
{
	void hkpAabbPhantom::castRay(const hkpWorldRayCastInput& input, hkpRayHitCollector& collector) const
	{
		using func_t = void (*)(const hkpAabbPhantom*, const hkpWorldRayCastInput&, hkpRayHitCollector&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60173, 60941) };
		func(this, input, collector);
	}

	void hkpAabbPhantom::castRay(const hkpWorldRayCastInput& input, hkpWorldRayCastOutput& output) const
	{
		using func_t = void (*)(const hkpAabbPhantom*, const hkpWorldRayCastInput&, const hkpWorldRayCastOutput&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60174, 60942) };
		return func(this, input, output);
	}

	void hkpAabbPhantom::linearCast(const hkpCollidable* castCollidable, const hkpLinearCastInput& input, hkpCdPointCollector& castCollector, hkpCdPointCollector* startCollector) const
	{
		using func_t = decltype(&hkpAabbPhantom::linearCast);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60175, 60943) };
		return func(this, castCollidable, input, castCollector, startCollector);
	}

	void hkpAabbPhantom::setAabb(const hkAabb& a_aabb)
	{
		using func_t = decltype(&hkpAabbPhantom::setAabb);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60181, 60949) };
		return func(this, a_aabb);
	}
}
