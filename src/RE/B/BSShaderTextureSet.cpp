#include "RE/B/BSShaderTextureSet.h"

namespace RE
{
	BSShaderTextureSet* BSShaderTextureSet::Ctor()
	{
		using func_t = decltype(&BSShaderTextureSet::Ctor);
		REL::Relocation<func_t> func{ REL::ID(99886) };
		return func(this);
	}

	BSShaderTextureSet* BSShaderTextureSet::Create()
	{
		if (REL::Module::get().IsAE()) {
			using func_t = decltype(&BSShaderTextureSet::Create);
			REL::Relocation<func_t> func{ REL::ID(107172) };
			return func();
		} else {
			auto textureset = malloc<BSShaderTextureSet>();
			if (textureset) {
				std::memset(textureset, 0, sizeof(BSShaderTextureSet));
				textureset->Ctor();
			}
			return textureset;
		}
	}
}
