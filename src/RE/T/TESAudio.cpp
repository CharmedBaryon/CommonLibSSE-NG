#include "RE/T/TESAudio.h"

namespace RE
{
	namespace TESAudio
	{
		void ClearAcousticSpace(BGSAcousticSpace* a_space)
		{
			using func_t = decltype(&TESAudio::ClearAcousticSpace);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34309, 35131) };
			func(a_space);
		}

		void SetAcousticSpace(BGSAcousticSpace* a_space)
		{
			using func_t = decltype(&TESAudio::SetAcousticSpace);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34308, 35130) };
			func(a_space);
		}
	}
}
