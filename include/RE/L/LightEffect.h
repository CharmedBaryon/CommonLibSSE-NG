#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class NiPointLight;

	class LightEffect : public ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_LightEffect;
		inline static constexpr auto VTABLE = VTABLE_LightEffect;

		// override (ActiveEffect)
		void Update(float a_delta) override;                                     // 04
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;                  // 0A
		void Revert(BGSLoadFormBuffer* a_buf) override;                          // 0B
		void SwitchAttachedRoot(NiNode* a_root, NiNode* a_attachRoot) override;  // 0E

		~LightEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15

		// members
		NiPointer<NiPointLight> light;  // 90
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(LightEffect) == 0x98);
}
