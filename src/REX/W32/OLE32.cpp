#include "REX/W32/OLE32.h"

REX_W32_IMPORT(void, CoTaskMemFree, void*);

namespace REX::W32
{
	void CoTaskMemFree(void* a_block) noexcept
	{
		::W32_IMPL_CoTaskMemFree(a_block);
	}
}
