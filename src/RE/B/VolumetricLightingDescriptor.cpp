#include "RE/B/VolumetricLightingDescriptor.h"

#include "REL/Relocation.h"

namespace RE
{
	VolumetricLightingDescriptor& GetVolumetricLightingDescriptor()
	{
		using func_t = VolumetricLightingDescriptor* (*)();
		static REL::Relocation<func_t> func{ RELOCATION_ID(100297, 107014) };
		return *func();
	}

	void SetVolumetricLightingQuality(VolumetricLightingDescriptor& a_descriptor, std::uint32_t a_quality)
	{
		using func_t = void (*)(VolumetricLightingDescriptor*, std::uint32_t);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100299, 107016) };
		func(&a_descriptor, a_quality);
	}

	void RenderVolumetricLighting(VolumetricLightingDescriptor* a_descriptor, NiCamera* a_camera, bool a_flag)
	{
		using func_t = void (*)(VolumetricLightingDescriptor*, NiCamera*, bool);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100306, 107023) };
		func(a_descriptor, a_camera, a_flag);
	}
}
