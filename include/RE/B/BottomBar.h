#pragma once

#include "RE/G/GFxMovieView.h"
#include "RE/G/GFxValue.h"

namespace RE
{
	struct BottomBar
	{
	public:
		BottomBar(RE::GFxMovieView* a_view)
		{
			a_view->CreateObject(&obj);
		}

		TES_HEAP_REDEFINE_NEW();

		// members
		GFxValue obj;  // 00 - kObject
	};
	static_assert(sizeof(BottomBar) == 0x18);
}
