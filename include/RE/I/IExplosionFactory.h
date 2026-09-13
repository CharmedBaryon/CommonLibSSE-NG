#pragma once

namespace RE
{
	class BGSExplosion;
	class Explosion;

	class IExplosionFactory
	{
	public:
		inline static constexpr auto RTTI = RTTI_IExplosionFactory;
		inline static constexpr auto VTABLE = VTABLE_IExplosionFactory;

		virtual ~IExplosionFactory();  // 00

		// add
		virtual Explosion* Create(BGSExplosion* a_form) = 0;  // 01
	};
	static_assert(sizeof(IExplosionFactory) == 0x8);
}
