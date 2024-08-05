#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	struct CellAttachDetachEvent;

	class ICellAttachDetachEventSource :
		public BSTSingletonExplicit<ICellAttachDetachEventSource>,  // 08
		public BSTEventSource<CellAttachDetachEvent>                // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_ICellAttachDetachEventSource;
		inline static constexpr auto VTABLE = VTABLE_ICellAttachDetachEventSource;

		virtual ~ICellAttachDetachEventSource();  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ICellAttachDetachEventSource) == 0x60);
}
