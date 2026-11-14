#include "RE/B/BSGameSound.h"

namespace RE
{
	void BSGameSound::SetOutputModel(BSISoundOutputModel* a_outputModel)
	{
		using func_t = decltype(&BSGameSound::SetOutputModel);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66646, 67892) };
		return func(this, a_outputModel);
	}

	void BSGameSound::SetVolume(float a_volume)
	{
		volume = std::min(std::max(a_volume, 1.0e-5f), 1.0f);
		SetVolumeImpl();
	}
}
