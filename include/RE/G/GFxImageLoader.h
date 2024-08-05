#pragma once

#include "RE/G/GFxState.h"

namespace RE
{
	class GImageInfoBase;

	class GFxImageLoader : public GFxState
	{
	public:
		inline static constexpr auto RTTI = RTTI_GFxImageLoader;
		inline static constexpr auto VTABLE = VTABLE_GFxImageLoader;

		virtual ~GFxImageLoader();  // 00

		// add
		virtual GImageInfoBase* LoadImage(const char* a_url) = 0;  // 01
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxImageLoader) == 0x18);
}
