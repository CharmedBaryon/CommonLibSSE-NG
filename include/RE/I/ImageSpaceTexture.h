#pragma once

#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TextureAddressModes.h"
#include "RE/T/TextureFilterModes.h"

namespace RE
{
	class NiSourceTexture;

	class ImageSpaceTexture
	{
	public:
		// members
		NiPointer<NiSourceTexture>     texture;       // 00
		RENDER_TARGET                  renderTarget;  // 08
		std::uint32_t                  unk0C;         // 0C
		BSGraphics::TextureFilterMode  filterMode;    // 10
		BSGraphics::TextureAddressMode clampMode;     // 14
		bool                           isAcquired;    // 18
		std::uint8_t                   pad19;         // 19
		std::uint16_t                  pad1A;         // 1A
		std::uint16_t                  pad1C;         // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceTexture) == 0x20);
}
