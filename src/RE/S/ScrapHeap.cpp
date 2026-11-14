#include "RE/S/ScrapHeap.h"

namespace RE
{
	void* ScrapHeap::Allocate(std::size_t a_size, std::size_t a_alignment)
	{
		using func_t = decltype(&ScrapHeap::Allocate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66884, 68144) };
		return func(this, a_size, a_alignment);
	}

	void ScrapHeap::Deallocate(void* a_mem)
	{
		using func_t = decltype(&ScrapHeap::Deallocate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66885, 68146) };
		return func(this, a_mem);
	}
}
