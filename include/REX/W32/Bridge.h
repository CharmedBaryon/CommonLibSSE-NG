#pragma once

// CommonLib first, SDK second -- REX/W32/BASE.h errors if the Windows API was
// included first.
#include "REX/W32/D3D11.h"
#include "REX/W32/DXGI.h"

#include <DirectXMath.h>
#include <d3d11.h>
#include <type_traits>

// Deliberately absent from REX/W32.h: this is the one REX header that includes
// the SDK, so a consumer opts in only where it already links d3d11.

namespace REX::W32
{
	namespace detail
	{
		template <class T>
		struct RealOf
		{
			static_assert(!std::is_same_v<T, T>, "no REX::W32 <-> SDK pairing registered for this type -- add a REX_W32_PAIR entry in REX/W32/Bridge.h");
		};
		template <class T>
		struct W32Of
		{
			static_assert(!std::is_same_v<T, T>, "no REX::W32 <-> SDK pairing registered for this type -- add a REX_W32_PAIR entry in REX/W32/Bridge.h");
		};

		// clang-format off
#define REX_W32_PAIR(Real, W32Type)                             \
	template <> struct RealOf<Real> { using type = Real; };     \
	template <> struct RealOf<W32Type> { using type = Real; };  \
	template <> struct W32Of<Real> { using type = W32Type; };   \
	template <> struct W32Of<W32Type> { using type = W32Type; };
		// clang-format on

		REX_W32_PAIR(::ID3D11View, ID3D11View)
		REX_W32_PAIR(::ID3D11Resource, ID3D11Resource)
		REX_W32_PAIR(::ID3D11Texture2D, ID3D11Texture2D)
		REX_W32_PAIR(::ID3D11ShaderResourceView, ID3D11ShaderResourceView)
		REX_W32_PAIR(::ID3D11RenderTargetView, ID3D11RenderTargetView)
		REX_W32_PAIR(::ID3D11DepthStencilView, ID3D11DepthStencilView)
		REX_W32_PAIR(::ID3D11UnorderedAccessView, ID3D11UnorderedAccessView)
		REX_W32_PAIR(::D3D11_TEXTURE2D_DESC, D3D11_TEXTURE2D_DESC)
		REX_W32_PAIR(::D3D11_SHADER_RESOURCE_VIEW_DESC, D3D11_SHADER_RESOURCE_VIEW_DESC)
		REX_W32_PAIR(::D3D11_RENDER_TARGET_VIEW_DESC, D3D11_RENDER_TARGET_VIEW_DESC)
		REX_W32_PAIR(::D3D11_DEPTH_STENCIL_VIEW_DESC, D3D11_DEPTH_STENCIL_VIEW_DESC)
		REX_W32_PAIR(::D3D11_UNORDERED_ACCESS_VIEW_DESC, D3D11_UNORDERED_ACCESS_VIEW_DESC)
		REX_W32_PAIR(::GUID, GUID)
		REX_W32_PAIR(const ::GUID, const GUID)
		REX_W32_PAIR(::ID3D11VertexShader, ID3D11VertexShader)
		REX_W32_PAIR(::ID3D11PixelShader, ID3D11PixelShader)
		REX_W32_PAIR(::ID3D11ComputeShader, ID3D11ComputeShader)
		REX_W32_PAIR(::ID3D11Buffer, ID3D11Buffer)
		REX_W32_PAIR(::ID3D11Device, ID3D11Device)
		REX_W32_PAIR(::ID3D11DeviceContext, ID3D11DeviceContext)
		REX_W32_PAIR(::IDXGISwapChain, IDXGISwapChain)
		REX_W32_PAIR(::DirectX::XMFLOAT4X4, XMFLOAT4X4)
		REX_W32_PAIR(const ::DirectX::XMFLOAT4X4, const XMFLOAT4X4)

		REX_W32_PAIR(::ID3D11Resource*, ID3D11Resource*)
		REX_W32_PAIR(::ID3D11Texture2D*, ID3D11Texture2D*)
		REX_W32_PAIR(::ID3D11ShaderResourceView*, ID3D11ShaderResourceView*)
		REX_W32_PAIR(::ID3D11RenderTargetView*, ID3D11RenderTargetView*)
		REX_W32_PAIR(::ID3D11UnorderedAccessView*, ID3D11UnorderedAccessView*)
		REX_W32_PAIR(::ID3D11VertexShader*, ID3D11VertexShader*)
		REX_W32_PAIR(::ID3D11PixelShader*, ID3D11PixelShader*)
		REX_W32_PAIR(::ID3D11ComputeShader*, ID3D11ComputeShader*)
#undef REX_W32_PAIR
	}

	template <class T>
	[[nodiscard]] auto* AsReal(T* a_ptr) noexcept
	{
		return reinterpret_cast<typename detail::RealOf<T>::type*>(a_ptr);
	}

	template <class T>
	[[nodiscard]] auto* AsW32(T* a_ptr) noexcept
	{
		return reinterpret_cast<typename detail::W32Of<T>::type*>(a_ptr);
	}

	// Explicit both-type form for a source that is type-erased (e.g. a void* an
	// engine hook fills in), where there is nothing to deduce from.
	template <class To, class From>
	[[nodiscard]] To* CastTo(From* a_ptr) noexcept
	{
		return reinterpret_cast<To*>(a_ptr);
	}
}
