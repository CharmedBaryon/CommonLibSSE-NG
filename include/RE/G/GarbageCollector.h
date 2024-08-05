#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSAnimationGraphManager;
	class BSCloneReserver;
	class BSTempEffect;
	class BipedAnim;
	class NavMesh;
	class NiAVObject;
	class QueuedFile;
	class TESBoundObject;
	class TESObjectREFR;

	struct GarbageCollection
	{
	public:
		// members
		BSSpinLock                                         lock;            // 00
		BSTArray<BSTSmartPointer<BSAnimationGraphManager>> animations;      // 08
		BSTArray<TESBoundObject*>                          baseObjects;     // 20
		BSTArray<ObjectRefHandle>                          objectHandles;   // 38
		BSTArray<NiPointer<NiAVObject>>                    actorNodes;      // 50
		BSTArray<BSTSmartPointer<BipedAnim>>               bipedAnims;      // 68
		BSTArray<NiPointer<BSTempEffect>>                  tempEffects;     // 80
		BSTArray<NiPointer<QueuedFile>>                    queuedFiles;     // 98
		BSTArray<NiPointer<BSCloneReserver>>               cloneReservers;  // B0
		BSTArray<BSTSmartPointer<NavMesh>>                 navMeshes;       // C8
		bool                                               deleting;        // E0
	};
	static_assert(sizeof(GarbageCollection) == 0xE8);

	class GarbageCollector :
		public BSTSingletonSDM<GarbageCollector>,
		public BSTEventSink<PositionPlayerEvent>
	{
	public:
		inline static constexpr auto RTTI = RTTI_GarbageCollector;
		inline static constexpr auto VTABLE = VTABLE_GarbageCollector;

		~GarbageCollector() override;  // 00

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent* a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override;  // 01

		static GarbageCollector* GetSingleton()
		{
			REL::Relocation<GarbageCollector**> singleton{ RELOCATION_ID(514180, 400329) };
			return *singleton;
		}

		void Add(TESObjectREFR* a_object, bool a_removeFromCell)
		{
			using func_t = decltype(&GarbageCollector::Add);
			static REL::Relocation<func_t> func{ RELOCATION_ID(35492, 36459) };
			return func(this, a_object, a_removeFromCell);
		}

		// members
		GarbageCollection* garbageCollection;  // 10
	};
	static_assert(sizeof(GarbageCollector) == 0x18);
}
