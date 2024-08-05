#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class NiAVObject;

	class AttachLightHitEffectVisitor : public ActiveEffect::ForEachHitEffectVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI___AttachLightHitEffectVisitor;
		inline static constexpr auto VTABLE = VTABLE___AttachLightHitEffectVisitor;

		~AttachLightHitEffectVisitor() override;  // 00

		// override (ActiveEffect::ForEachHitEffectVisitor)
		BSContainer::ForEachResult operator()(ReferenceEffect* a_hitEffect) override;  // 01

		// members
		NiAVObject*   attachRoot;       // 08
		NiAVObject*   attachLightNode;  // 10
		bool          allAttached;      // 18
		std::uint8_t  pad19;            // 19
		std::uint16_t pad1A;            // 1A
		std::uint32_t pad1C;            // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AttachLightHitEffectVisitor) == 0x20);
}
