#pragma once

#include "RE/G/GRefCountNTSImpl.h"

namespace RE
{
	class GWeakPtrProxy;

	class GRefCountWeakSupportImpl : public GRefCountNTSImpl
	{
	public:
		GRefCountWeakSupportImpl()
		{
			weakProxy = nullptr;
		}

		virtual ~GRefCountWeakSupportImpl();

		GWeakPtrProxy* CreateWeakProxy() const;

		// members
		mutable GWeakPtrProxy* weakProxy;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GRefCountWeakSupportImpl) == 0x18);
}
