#pragma once

#include "RE/B/BSAnimationGraphChannel.h"

namespace RE
{
	template <class T, class Val, template <class U, class UVal> class Channel>
	class BSTAnimationGraphDataChannel :
		public BSAnimationGraphChannel,  // 00
		public Channel<T, Val>           // 20
	{
	public:
	private:
		KEEP_FOR_RE()
	};
}
