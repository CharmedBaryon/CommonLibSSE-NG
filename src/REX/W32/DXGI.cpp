#include "REX/W32/DXGI.h"

REX_W32_IMPORT(std::int32_t, CreateDXGIFactory, const IID&, void**);
REX_W32_IMPORT(std::int32_t, CreateDXGIFactory1, const IID&, void**);

namespace REX::W32
{
	HRESULT CreateDXGIFactory(const IID& a_iid, void** a_factory) noexcept
	{
		return ::W32_IMPL_CreateDXGIFactory(a_iid, a_factory);
	}

	HRESULT CreateDXGIFactory1(const IID& a_iid, void** a_factory) noexcept
	{
		return ::W32_IMPL_CreateDXGIFactory1(a_iid, a_factory);
	}
}
