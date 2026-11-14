#pragma once

namespace RE
{
	class Explosion;
	struct SpawnExplosionData;

	class IExplosionFactory
	{
	public:
		inline static constexpr auto RTTI = RTTI_IExplosionFactory;
		inline static constexpr auto VTABLE = VTABLE_IExplosionFactory;

		virtual ~IExplosionFactory();  // 00

		// add
		virtual Explosion* Create(SpawnExplosionData& a_data) = 0;  // 01
	};
	static_assert(sizeof(IExplosionFactory) == 0x8);
}
