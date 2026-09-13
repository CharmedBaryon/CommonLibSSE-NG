#pragma once

#include "RE/B/BSQueuedResourceCollectionBase.h"

namespace RE
{
	namespace TESModelDB
	{
		// Adds no new POD fields beyond BSQueuedResourceCollectionBase's own tail.
		class TESQueuedHandles : public BSQueuedResourceCollectionBase
		{
		public:
			inline static constexpr auto RTTI = RTTI_TESModelDB__TESQueuedHandles;
			inline static constexpr auto VTABLE = VTABLE_TESModelDB__TESQueuedHandles;

			~TESQueuedHandles() override;  // 00

			// add
			virtual void Unk_15();             // 15 - unregisters via the global BSResourceEntryDB
			virtual void Unk_16();             // 16 - ClearQueue: releases/frees every queued entry
			virtual void Unk_17();             // 17 - CountPending: counts entries whose handle flags (+0xC, masked 0x70000000) are unset
			virtual void Unk_18() { return; }  // 18 - owner ambiguous: base class vs. the shared BSQueuedResourceCollection<Traits,N> template
		};
	}
}
