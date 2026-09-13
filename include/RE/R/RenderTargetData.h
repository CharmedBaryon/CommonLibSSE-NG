#pragma once

#include <REX/W32/D3D11.h>

namespace RE
{
	namespace BSGraphics
	{
		struct RenderTargetData
		{
			REX::W32::ID3D11Texture2D*           texture;      // 00
			REX::W32::ID3D11Texture2D*           textureCopy;  // 08
			REX::W32::ID3D11RenderTargetView*    RTV;          // 10 - for "Texture"
			REX::W32::ID3D11ShaderResourceView*  SRV;          // 18 - for Texture"
			REX::W32::ID3D11ShaderResourceView*  SRVCopy;      // 20 - for "TextureCopy"
			REX::W32::ID3D11UnorderedAccessView* UAV;          // 28 - for "Texture"
		};
		static_assert(sizeof(RenderTargetData) == 0x30);

		struct DepthStencilData
		{
			REX::W32::ID3D11Texture2D*          texture;           // 00
			REX::W32::ID3D11DepthStencilView*   views[8];          // 08
			REX::W32::ID3D11DepthStencilView*   readOnlyViews[8];  // 48
			REX::W32::ID3D11ShaderResourceView* depthSRV;          // 88
			REX::W32::ID3D11ShaderResourceView* stencilSRV;        // 90
		};
		static_assert(sizeof(DepthStencilData) == 0x98);

		struct CubemapRenderTargetData
		{
			REX::W32::ID3D11Texture2D*          texture;         // 00
			REX::W32::ID3D11RenderTargetView*   cubeSideRTV[6];  // 08
			REX::W32::ID3D11ShaderResourceView* SRV;             // 38
		};
		static_assert(sizeof(CubemapRenderTargetData) == 0x40);

		struct Texture3DTargetData
		{
			std::uint64_t unk00;  // 00
			std::uint64_t unk08;  // 08
			std::uint64_t unk10;  // 10
			std::uint64_t unk18;  // 18
		};
		static_assert(sizeof(Texture3DTargetData) == 0x20);
	}
}
