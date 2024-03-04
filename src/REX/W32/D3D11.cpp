#include "REX/W32/D3D11.h"

REX_W32_IMPORT(std::int32_t, D3D11CreateDevice, REX::W32::IDXGIAdapter*, REX::W32::D3D_DRIVER_TYPE, REX::W32::HMODULE, std::uint32_t, const REX::W32::D3D_FEATURE_LEVEL*, std::uint32_t, std::uint32_t, REX::W32::ID3D11Device**, REX::W32::D3D_FEATURE_LEVEL*, REX::W32::ID3D11DeviceContext**);
REX_W32_IMPORT(std::int32_t, D3D11CreateDeviceAndSwapChain, REX::W32::IDXGIAdapter*, REX::W32::D3D_DRIVER_TYPE, REX::W32::HMODULE, std::uint32_t, const REX::W32::D3D_FEATURE_LEVEL*, std::uint32_t, std::uint32_t, const REX::W32::DXGI_SWAP_CHAIN_DESC*, REX::W32::IDXGISwapChain**, REX::W32::ID3D11Device**, REX::W32::D3D_FEATURE_LEVEL*, REX::W32::ID3D11DeviceContext**);

namespace REX::W32
{
	HRESULT D3D11CreateDevice(IDXGIAdapter* a_adapter, D3D_DRIVER_TYPE a_driverType, HMODULE a_software, std::uint32_t a_flags, const D3D_FEATURE_LEVEL* a_pFeatureLevels, std::uint32_t a_featureLevels, std::uint32_t a_sdkVersion, ID3D11Device** a_device, D3D_FEATURE_LEVEL* a_pFeatureLevel, ID3D11DeviceContext** a_immediateContext) noexcept
	{
		return ::W32_IMPL_D3D11CreateDevice(a_adapter, a_driverType, a_software, a_flags, a_pFeatureLevels, a_featureLevels, a_sdkVersion, a_device, a_pFeatureLevel, a_immediateContext);
	}

	HRESULT D3D11CreateDeviceAndSwapChain(IDXGIAdapter* a_adapter, D3D_DRIVER_TYPE a_driverType, HMODULE a_software, std::uint32_t a_flags, const D3D_FEATURE_LEVEL* a_pFeatureLevels, std::uint32_t a_featureLevels, std::uint32_t a_sdkVersion, const DXGI_SWAP_CHAIN_DESC* a_swapChainDesc, IDXGISwapChain** a_swapChain, ID3D11Device** a_device, D3D_FEATURE_LEVEL* a_pFeatureLevel, ID3D11DeviceContext** a_immediateContext) noexcept
	{
		return ::W32_IMPL_D3D11CreateDeviceAndSwapChain(a_adapter, a_driverType, a_software, a_flags, a_pFeatureLevels, a_featureLevels, a_sdkVersion, a_swapChainDesc, a_swapChain, a_device, a_pFeatureLevel, a_immediateContext);
	}
}
