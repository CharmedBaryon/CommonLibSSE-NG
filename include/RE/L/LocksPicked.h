#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	struct LocksPicked
	{
		struct Event
		{
		public:
		};
		static_assert(std::is_empty_v<LocksPicked::Event>);

		[[nodiscard]] static BSTEventSource<LocksPicked::Event>* QEventSource()
		{
			using func_t = decltype(&LocksPicked::QEventSource);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51115, 51997) };
			return func();
		}
	};
}
