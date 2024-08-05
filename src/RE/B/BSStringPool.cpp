#include "RE/B/BSStringPool.h"

namespace RE
{
	BucketTable* BucketTable::GetSingleton()
	{
		using func_t = decltype(&BucketTable::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67855, 69200) };
		return func();
	}
}
