#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTexture.h"
#include <REX/W32/D3D11.h>

namespace RE
{
	namespace BSGraphics
	{
		class Texture
		{
		public:
			REX::W32::ID3D11Resource*            texture;       // 00 - can be ID3D11Texture1D/ID3D11Texture2D/ID3D11Texture3D
			REX::W32::ID3D11UnorderedAccessView* UAV;           // 08
			REX::W32::ID3D11ShaderResourceView*  resourceView;  // 10
			uint16_t                             height;        // 18
			uint16_t                             width;         // 1A
			uint8_t                              mips;          // 1C
			uint8_t                              format;        // 1D
			uint16_t                             unk1E;         // 1E
			std::uint32_t                        refCount;      // 20
			std::uint32_t                        pad24;         // 24
		};
		static_assert(sizeof(Texture) == 0x28);

		class DDSInfo  // used when loading renderer texture
		{
		public:
			struct DDS_PIXELFORMAT
			{
				std::int32_t dwSize;         // 00
				std::int32_t dwFlags;        // 04
				std::int32_t dwFourCC;       // 08
				std::int32_t dwRGBBitCount;  // 0C
				std::int32_t dwRBitMask;     // 10
				std::int32_t dwGBitMask;     // 14
				std::int32_t dwBBitMask;     // 18
				std::int32_t dwABitMask;     // 1C
			};
			static_assert(sizeof(DDS_PIXELFORMAT) == 0x20);

			struct DDS_HEADER
			{
				std::int32_t    dwSize;               // 00
				std::int32_t    dwFlags;              // 04
				std::int32_t    dwHeight;             // 08
				std::int32_t    dwWidth;              // 0A
				std::int32_t    dwPitchOrLinearSize;  // 10
				std::int32_t    dwDepth;              // 14
				std::int32_t    dwMipMapCount;        // 18
				std::int32_t    dwReserved1[11];      // 1A
				DDS_PIXELFORMAT ddspf;                // 48
				std::int32_t    dwCaps;               // 68
				std::int32_t    dwCaps2;              // 6A
				std::int32_t    dwCaps3;              // 70
				std::int32_t    dwCaps4;              // 74
				std::int32_t    dwReserved2;          // 78
			};
			static_assert(sizeof(DDS_HEADER) == 0x7C);

			DDS_HEADER ddsHeader;   // 00
			std::byte  unk7C[0xC];  // 7C
		};
		static_assert(sizeof(DDSInfo) == 0x88);
	}

	namespace BSResource
	{
		class Stream;
	}

	NiSmartPointer(NiSourceTexture);

	class NiSourceTexture : public NiTexture
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSourceTexture;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSourceTexture;
		inline static constexpr auto VTABLE = VTABLE_NiSourceTexture;

		~NiSourceTexture() override;  // 00

		// override (NiTexture)
		const NiRTTI* GetRTTI() const override;                                                                                                                  // 02
		void          Unk_25(void) override;                                                                                                                     // 25 - { return 0; }
		void          Unk_26(void) override;                                                                                                                     // 26 - { return 0; }
		char*         GetTextureFormat() override;                                                                                                               // 27
		void          GetTextureDimensionsAndMipInfo(std::uint32_t* width, std::uint32_t* height, std::uint32_t* mipLevels, std::uint32_t* arraySize) override;  // 28
		void          Unk_29(void) override;                                                                                                                     // 29 - { return; }
		void          Unk_2A(void) override;                                                                                                                     // 2A - { return; }

		// members
		BSResource::Stream*  resourceStream;   // 40
		BSGraphics::Texture* rendererTexture;  // 48
		std::uint8_t         flags;            // 50
		std::uint8_t         pad51;            // 51
		std::uint16_t        pad52;            // 52
		std::uint32_t        pad54;            // 54
	};
	static_assert(sizeof(NiSourceTexture) == 0x58);
}
