#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSResourceEntryDB.h"
#include "RE/B/BSTArray.h"
#include "RE/Q/QueuedFile.h"

namespace RE
{
	struct QueuedResourceEntry
	{
		void*         resourceHandle;  // 00 - freed via FreeRequestedModel on removal
		BSFixedString path;            // 08
	};
	static_assert(sizeof(QueuedResourceEntry) == 0x10);

	// Base of TESModelDB::TESQueuedHandles and the BSQueuedResourceCollection<Traits,N>
	// instantiations; multiply-inherits QueuedFile (primary) and
	// BSResource::IEntryDB::PostFlushNotify (secondary).
	class BSQueuedResourceCollectionBase :
		public QueuedFile,                            // 00
		public BSResource::IEntryDB::PostFlushNotify  // 38 (SE/AE) / 40 (VR)
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSQueuedResourceCollectionBase;
		inline static constexpr auto VTABLE = VTABLE_BSQueuedResourceCollectionBase;

		~BSQueuedResourceCollectionBase() override;  // 00

		// override (BSTask)
		void Unk_03() override;  // 03 - CAS-guards on PostFlushNotify::TryAbort; on success releases the dependency, calls BSTask's own slots 1/2, then PostFlushNotify::Aborted
		void Unk_04() override;  // 04 - debug type name, "Queued resource collection"

		// override (QueuedFile)
		void Unk_09() override;  // 09 - if pendingCount is nonzero, bumps refCount, calls Unk_15, and resubmits `this` to the global IOManager; else sets BSTask::unk0C (abort-state) to 5
		void Unk_10() override;  // 10 - if pendingCount==0 and abort-state is 0/1, CASes abort-state to 4 and records needNotifyFlag
		void Unk_11() override;  // 11 - calls Unk_13; if needNotifyFlag is set, notifies the global IOManager and clears it

		// add
		virtual void Unk_12() { return; }  // 12
		virtual void Unk_13() { return; }  // 13
		virtual void Unk_14() { return; }  // 14

		// members
		std::uint32_t                         pendingCount;    // 50 - nonzero while entries are outstanding
		bool                                  needNotifyFlag;  // 54 - set by Unk_10, consumed by Unk_11
		bool                                  unk55;           // 55 - nonzero at construction; purpose unresolved
		std::uint16_t                         pad56;           // 56
		BSTSmallArray<QueuedResourceEntry, 2> queue;           // 58
	};
	STATIC_ASSERT_SIZE(BSQueuedResourceCollectionBase, 0x88, 0x90);
}
