#pragma once

#include "RE/I/ImageSpaceEffectParam.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTexture.h"
#include "RE/T/TextureFilterModes.h"

namespace RE
{
	class ImageSpaceShaderParam : public ImageSpaceEffectParam
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceShaderParam;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceShaderParam;

		~ImageSpaceShaderParam() override;  // 00

		// members
		std::uint32_t                                    unk08;                    // 08
		bool                                             SLIMode;                  // 0C
		std::uint8_t                                     pad0D;                    // 0D
		std::uint16_t                                    pad0E;                    // 0E
		std::uint64_t                                    unk10;                    // 10
		std::uint64_t                                    unk18;                    // 18
		std::uint8_t                                     unk20;                    // 20
		std::uint8_t                                     pad21;                    // 21
		std::uint16_t                                    pad22;                    // 22
		std::uint32_t                                    unk24;                    // 24
		float                                            unk28;                    // 28
		std::uint32_t                                    unk2C;                    // 2C
		float*                                           vertexConstantGroup;      // 30
		std::uint32_t                                    vertexConstantGroupSize;  // 38
		std::uint32_t                                    unk3C;                    // 3C
		float*                                           pixelConstantGroup;       // 40
		std::uint32_t                                    pixelConstantGroupSize;   // 48
		std::uint32_t                                    unk4C;                    // 4C
		NiTObjectArray<NiPointer<NiTexture>>             textures;                 // 50
		NiTPrimitiveArray<BSGraphics::TextureFilterMode> textureFilterModes;       // 68 - NiTPrimitiveArray<enum BSGraphics::TextureFilterMode>
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceShaderParam) == 0x80);
}
