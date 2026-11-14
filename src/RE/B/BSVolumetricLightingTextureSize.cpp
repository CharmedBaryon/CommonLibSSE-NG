#include "RE/B/BSVolumetricLightingTextureSize.h"

namespace RE
{
	BSVolumetricLightingTextureSize* BSVolumetricLightingTextureSize::GetQualitySizes()
	{
		static REL::Relocation<BSVolumetricLightingTextureSize*> sizes{ RELOCATION_ID(527970, 414916) };
		return sizes.get();
	}
}
