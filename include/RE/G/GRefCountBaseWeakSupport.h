#pragma once

#include "RE/G/GMemory.h"
#include "RE/G/GRefCountBaseStatImpl.h"
#include "RE/G/GRefCountWeakSupportImpl.h"

namespace RE
{
	template <class T, std::uint32_t STAT>
	class GRefCountBaseWeakSupport : public GRefCountBaseStatImpl<GRefCountWeakSupportImpl, STAT>
	{
	public:
		enum
		{
			kStatType = STAT
		};

	private:
		KEEP_FOR_RE()
	};
}
