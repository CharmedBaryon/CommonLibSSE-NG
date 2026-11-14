#pragma once

#include <cstdint>

namespace RE
{
	class VolumetricLightingDescriptor;
	class NiCamera;

	[[nodiscard]] VolumetricLightingDescriptor& GetVolumetricLightingDescriptor();
	void                                        SetVolumetricLightingQuality(VolumetricLightingDescriptor& a_descriptor, std::uint32_t a_quality);
	void                                        RenderVolumetricLighting(VolumetricLightingDescriptor* a_descriptor, NiCamera* a_camera, bool a_flag);
}
