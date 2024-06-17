#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class Script;
	class ScriptLocals;

	class ScriptEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_ScriptEffect;
		inline static constexpr auto VTABLE = VTABLE_ScriptEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;               // 04
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 09
		virtual void ClearTargetImpl() override;                   // 12
		virtual ~ScriptEffect();                                   // 13
		virtual void Start() override;                             // 14
		virtual void Finish() override;                            // 15

		// members
		Script*       script;        // 90
		ScriptLocals* effectLocals;  // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ScriptEffect) == 0xA0);
}
