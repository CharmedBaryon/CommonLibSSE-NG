#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTHashMap.h"
#include "RE/C/CellLoaderTask.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class ExteriorCellLoader
	{
	public:
		static ExteriorCellLoader* GetSingleton()
		{
			static REL::Relocation<ExteriorCellLoader**> singleton{ RELOCATION_ID(514741, 400899) };
			return *singleton;
		}

		void QueueCellLoad(TESWorldSpace* a_space, std::int16_t a_x, std::int16_t a_y, bool a_unk)
		{
			using func_t = decltype(&ExteriorCellLoader::QueueCellLoad);
			static REL::Relocation<func_t> func{ RELOCATION_ID(18150, 18541) };
			func(this, a_space, a_x, a_y, a_unk);
		}

		// members
		BSReadWriteLock                                      lock;           // 00
		BSTHashMap<std::uint32_t, NiPointer<CellLoaderTask>> queuedCellMap;  // 08
	};
	static_assert(sizeof(ExteriorCellLoader) == 0x38);
}
