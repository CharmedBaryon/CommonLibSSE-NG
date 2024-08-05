#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class DisguiseEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DisguiseEffect;
		inline static constexpr auto VTABLE = VTABLE_DisguiseEffect;

		enum class State
		{
			kInitiate = 0,
			kWaiting,
			kNormal,
			kFail
		};

		// override (ActiveEffect)
		virtual void EvaluateConditions(float a_delta, bool a_forceUpdate) override;  // 05
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;                     // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;                     // 09
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;               // 0A
		virtual ~DisguiseEffect();                                                    // 13
		virtual void Start() override;                                                // 14
		virtual void Finish() override;                                               // 15

		// members
		DisguiseEffect::State state;  // 90
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DisguiseEffect) == 0x98);
}
