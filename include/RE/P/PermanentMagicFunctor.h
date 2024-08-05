#pragma once

#include "RE/B/BSContainer.h"

namespace RE
{
	class Actor;
	class MagicCaster;
	class MagicItem;

	struct PermanentMagicFunctor
	{
		enum class Flags
		{
			kNone = 0,
			kRemoveHitEffectArt = 1 << 0
		};

		PermanentMagicFunctor(MagicCaster* a_caster, Actor* a_actor) :
			caster(a_caster),
			actor(a_actor)
		{}

		BSContainer::ForEachResult operator()(MagicItem* a_spell)
		{
			using func_t = decltype(&PermanentMagicFunctor::operator());
			static REL::Relocation<func_t> func{ RELOCATION_ID(33684, 34464) };
			return func(this, a_spell);
		}

		// members
		MagicCaster*  caster;                 // 00
		Actor*        actor;                  // 08
		std::uint8_t  isSpellType{ 0xFF };    // 10
		std::uint8_t  isNotSpellType{ 0xA };  // 11
		std::uint8_t  flags{ 0 };             // 12
		std::uint8_t  pad13{ 0 };             // 13
		std::uint32_t pad14{ 0 };             // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(PermanentMagicFunctor) == 0x18);
}
