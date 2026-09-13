#include "RE/A/AIFormulas.h"
#include "RE/S/SoundLevels.h"

namespace RE
{
	namespace AIFormulas
	{
		std::int32_t ComputePickpocketSuccess(float a_thiefSkill, float a_targetSkill, std::uint32_t a_valueStolen, float a_weightStolen, Actor* a_thief, Actor* a_target, bool a_isDetected, TESForm* a_itemPickpocketing)
		{
			using func_t = decltype(ComputePickpocketSuccess);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25822, 26379) };
			return func(a_thiefSkill, a_targetSkill, a_valueStolen, a_weightStolen, a_thief, a_target, a_isDetected, a_itemPickpocketing);
		}

		std::int32_t GetSoundLevelValue(SOUND_LEVEL a_soundLevel)
		{
			using func_t = decltype(GetSoundLevelValue);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25814, 26367) };
			return func(a_soundLevel);
		}
	}
}
