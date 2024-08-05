#pragma once

#include "RE/N/NiTPointerAllocator.h"
#include "RE/N/NiTPointerListBase.h"

namespace RE
{
	template <class T>
	class NiTPointerList : public NiTPointerListBase<NiTPointerAllocator<std::uintptr_t>, T>
	{
	public:
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiTPointerList<void*>) == 0x18);
}
