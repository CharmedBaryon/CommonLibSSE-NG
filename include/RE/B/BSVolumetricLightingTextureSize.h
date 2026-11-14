#pragma once

#include "REL/Relocation.h"

#include <cstddef>
#include <cstdint>

namespace RE
{
	struct BSVolumetricLightingTextureSize
	{
		std::int32_t width;
		std::int32_t height;
		std::int32_t depth;

		[[nodiscard]] static BSVolumetricLightingTextureSize* GetQualitySizes();

		static constexpr std::size_t kQualityCount = 3;
	};
	static_assert(sizeof(BSVolumetricLightingTextureSize) == 0xC);
}
