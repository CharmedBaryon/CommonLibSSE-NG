#pragma once

#include "RE/H/hkLifoAllocator.h"

namespace RE
{
	class hkMemoryAllocator;

	class hkMemoryRouter
	{
	public:
		[[nodiscard]] static hkMemoryRouter* GetInstancePtr()
		{
			const REL::Relocation<std::uint32_t*> tlsSlot{ RELOCATION_ID(520865, 407383) };
			return static_cast<hkMemoryRouter*>(REX::W32::TlsGetValue(*tlsSlot));
		}

		[[nodiscard]] static hkMemoryRouter& GetInstance()
		{
			return *GetInstancePtr();
		}

		static void ReplaceInstance(hkMemoryRouter* a_router)
		{
			const REL::Relocation<std::uint32_t*> tlsSlot{ RELOCATION_ID(520865, 407383) };
			REX::W32::TlsSetValue(*tlsSlot, a_router);
		}

		void                           SetDebug(hkMemoryAllocator* a_val) noexcept { Debug = a_val; }
		void                           SetHeap(hkMemoryAllocator* a_val) noexcept { Heap = a_val; }
		void                           SetSolver(hkMemoryAllocator* a_val) noexcept { Solver = a_val; }
		void                           SetTemp(hkMemoryAllocator* a_val) noexcept { Temp = a_val; }
		[[nodiscard]] hkLifoAllocator& GetStack() noexcept { return Stack; }

		// members
		hkLifoAllocator    Stack;     // 0
		hkMemoryAllocator* Temp;      // 50
		hkMemoryAllocator* Heap;      // 58
		hkMemoryAllocator* Debug;     // 60
		hkMemoryAllocator* Solver;    // 68
		void*              UserData;  // 70
	};
	static_assert(sizeof(hkMemoryRouter) == 0x78);
}