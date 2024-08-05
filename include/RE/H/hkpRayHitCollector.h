#pragma once

namespace RE
{
	class hkpCdBody;

	struct hkpShapeRayCastCollectorOutput;

	class hkpRayHitCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpRayHitCollector;
		inline static constexpr auto VTABLE = VTABLE_hkpRayHitCollector;

		// add
		virtual void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) = 0;  // 00

		virtual ~hkpRayHitCollector(){};  // 01

		constexpr void Reset() noexcept { earlyOutHitFraction = 1.0f; }

		// members
		float         earlyOutHitFraction{ 1.0f };  // 08
		std::uint32_t pad0C;                        // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpRayHitCollector) == 0x10);
}
