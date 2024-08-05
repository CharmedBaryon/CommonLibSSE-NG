#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTFreeList.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTMessageQueue.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/C/CompiledScriptLoader.h"
#include "RE/D/DelayFunctor.h"
#include "RE/F/FragmentSystem.h"
#include "RE/H/HandlePolicy.h"
#include "RE/I/IFreezeQuery.h"
#include "RE/I/IStackCallbackSaveInterface.h"
#include "RE/L/Logger.h"
#ifdef ENABLE_SKYRIM_VR
#	include "RE/M/MenuOpenCloseEvent.h"
#endif
#include "RE/P/Profiler.h"
#include "RE/S/SavePatcher.h"
#include "RE/S/SimpleAllocMemoryPagePolicy.h"
#include "RE/S/SkyrimScriptObjectBindPolicy.h"
#include "RE/S/SkyrimScriptStore.h"

namespace RE
{
	namespace BSScript
	{
		class IFunctionArguments;
		class IVirtualMachine;
		class IVMDebugInterface;
		class IVMSaveLoadInterface;
		struct StatsEvent;
	}

	class MenuOpenCloseEvent;
	struct PositionPlayerEvent;
	struct TESActivateEvent;
	struct TESActiveEffectApplyRemoveEvent;
	struct TESActorLocationChangeEvent;
	struct TESBookReadEvent;
	struct TESCellAttachDetachEvent;
	struct TESCellFullyLoadedEvent;
	struct TESCombatEvent;
	struct TESContainerChangedEvent;
	struct TESDeathEvent;
	struct TESDestructionStageChangedEvent;
	struct TESEnterBleedoutEvent;
	struct TESEquipEvent;
	struct TESFastTravelEndEvent;
	struct TESFormDeleteEvent;
	struct TESFurnitureEvent;
	struct TESGrabReleaseEvent;
	struct TESHitEvent;
	struct TESInitScriptEvent;
	struct TESLoadGameEvent;
	struct TESLockChangedEvent;
	struct TESMagicEffectApplyEvent;
	struct TESMagicWardHitEvent;
	struct TESMoveAttachDetachEvent;
	struct TESObjectLoadedEvent;
	struct TESObjectREFRTranslationEvent;
	struct TESOpenCloseEvent;
	struct TESPackageEvent;
	struct TESPerkEntryRunEvent;
	struct TESPlayerBowShotEvent;
	struct TESQuestInitEvent;
	struct TESQuestStageEvent;
	struct TESResetEvent;
	struct TESResolveNPCTemplatesEvent;
	struct TESSceneActionEvent;
	struct TESSceneEvent;
	struct TESScenePhaseEvent;
	struct TESSellEvent;
	struct TESSleepStartEvent;
	struct TESSleepStopEvent;
	struct TESSpellCastEvent;
	struct TESSwitchRaceCompleteEvent;
	struct TESTopicInfoEvent;
	struct TESTrackedStatsEvent;
	struct TESTrapHitEvent;
	struct TESTriggerEnterEvent;
	struct TESTriggerEvent;
	struct TESTriggerLeaveEvent;
	struct TESUniqueIDChangeEvent;

	class SkyrimVM :
		public BSTSingletonSDM<SkyrimVM>,                      // 01A0
		public BSScript::IFreezeQuery,                         // 0000
		public BSScript::IStackCallbackSaveInterface,          // 0008
		public BSTEventSink<TESActivateEvent>,                 // 0010
		public BSTEventSink<TESActiveEffectApplyRemoveEvent>,  // 0018
		public BSTEventSink<TESActorLocationChangeEvent>,      // 0020
		public BSTEventSink<TESBookReadEvent>,                 // 0028
		public BSTEventSink<TESCellAttachDetachEvent>,         // 0030
		public BSTEventSink<TESCellFullyLoadedEvent>,          // 0038
		public BSTEventSink<TESCombatEvent>,                   // 0040
		public BSTEventSink<TESContainerChangedEvent>,         // 0048
		public BSTEventSink<TESDeathEvent>,                    // 0050
		public BSTEventSink<TESDestructionStageChangedEvent>,  // 0058
		public BSTEventSink<TESEnterBleedoutEvent>,            // 0060
		public BSTEventSink<TESEquipEvent>,                    // 0068
		public BSTEventSink<TESFormDeleteEvent>,               // 0070
		public BSTEventSink<TESFurnitureEvent>,                // 0078
		public BSTEventSink<TESGrabReleaseEvent>,              // 0080
		public BSTEventSink<TESHitEvent>,                      // 0088
		public BSTEventSink<TESInitScriptEvent>,               // 0090
		public BSTEventSink<TESLoadGameEvent>,                 // 0098
		public BSTEventSink<TESLockChangedEvent>,              // 00A0
		public BSTEventSink<TESMagicEffectApplyEvent>,         // 00A8
		public BSTEventSink<TESMagicWardHitEvent>,             // 00B0
		public BSTEventSink<TESMoveAttachDetachEvent>,         // 00B8
		public BSTEventSink<TESObjectLoadedEvent>,             // 00C0
		public BSTEventSink<TESObjectREFRTranslationEvent>,    // 00C8
		public BSTEventSink<TESOpenCloseEvent>,                // 00D0
		public BSTEventSink<TESPackageEvent>,                  // 00D8
		public BSTEventSink<TESPerkEntryRunEvent>,             // 00E0
		public BSTEventSink<TESQuestInitEvent>,                // 00E8
		public BSTEventSink<TESQuestStageEvent>,               // 00F0
		public BSTEventSink<TESResetEvent>,                    // 00F8
		public BSTEventSink<TESResolveNPCTemplatesEvent>,      // 0100
		public BSTEventSink<TESSceneEvent>,                    // 0108
		public BSTEventSink<TESSceneActionEvent>,              // 0110
		public BSTEventSink<TESScenePhaseEvent>,               // 0118
		public BSTEventSink<TESSellEvent>,                     // 0120
		public BSTEventSink<TESSleepStartEvent>,               // 0128
		public BSTEventSink<TESSleepStopEvent>,                // 0130
		public BSTEventSink<TESSpellCastEvent>,                // 0138
		public BSTEventSink<TESTopicInfoEvent>,                // 0140
		public BSTEventSink<TESTrackedStatsEvent>,             // 0148
		public BSTEventSink<TESTrapHitEvent>,                  // 0150
		public BSTEventSink<TESTriggerEvent>,                  // 0158
		public BSTEventSink<TESTriggerEnterEvent>,             // 0160
		public BSTEventSink<TESTriggerLeaveEvent>,             // 0168
		public BSTEventSink<TESUniqueIDChangeEvent>,           // 0170
		public BSTEventSink<TESSwitchRaceCompleteEvent>,       // 0178
		public BSTEventSink<TESPlayerBowShotEvent>,            // 0180
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		public BSTEventSink<TESFastTravelEndEvent>,  // 0188
		public BSTEventSink<PositionPlayerEvent>,    // 0190
		public BSTEventSink<BSScript::StatsEvent>,   // 0198
#else
		public BSTEventSink<PositionPlayerEvent>,   // 0188
		public BSTEventSink<BSScript::StatsEvent>,  // 0190
		public BSTEventSink<MenuOpenCloseEvent>,    // 0198
#endif
		public BSTEventSource<BSScript::StatsEvent>  // 01A8
	{
	public:
		inline static constexpr auto RTTI = RTTI_SkyrimVM;
		inline static constexpr auto VTABLE = VTABLE_SkyrimVM;

		struct UpdateDataEvent : public BSIntrusiveRefCounted
		{
		public:
			enum class UpdateType : bool
			{
				kRepeat = 0,    // RegisterForUpdate/RegisterForUpdateGameTime
				kNoRepeat = 1,  // RegisterForSingleUpdate/RegisterForSingleUpdateGameTime
			};

			// members
			UpdateType    updateType;       // 04
			std::uint16_t pad06;            // 06
			std::uint32_t timeToSendEvent;  // 08 - updateTime + currentVMMenuMode/currentVMDaysPassed
			std::uint32_t updateTime;       // 0C
			VMHandle      handle;           // 10
		};
		static_assert(sizeof(UpdateDataEvent) == 0x18);

		struct MenuOpenClose : public BSIntrusiveRefCounted
		{
		public:
			// members
			std::uint32_t pad04;     // 04
			VMHandle      handle;    // 08
			BSFixedString menuName;  // 10
		};
		static_assert(sizeof(MenuOpenClose) == 0x18);

		struct WaitCall
		{
		public:
			// members
			std::uint32_t              timeToSendEvent;  // 00 - Same as UpdateDataEvent, updateTime is discarded
			VMStackID                  stackID;          // 04 - used for vm->ReturnFromLatent()
			BSScript::IVirtualMachine* vm;               // 08
		};
		static_assert(sizeof(WaitCall) == 0x10);

		struct LOSDataEvent : public BSIntrusiveRefCounted
		{
		public:
			enum class LOSEventType
			{
				kGain = 0,
				kLost,
				kBoth,
			};

			enum class PreviousLOS
			{
				kLOS = 1,
				kNoLOS = 2
			};

			// members
			std::uint32_t pad04;               // 04
			VMHandle      handle;              // 08
			FormID        akViewerFormID;      // 10
			FormID        akTargetFormID;      // 14
			LOSEventType  losEventType;        // 18
			PreviousLOS   lastLOSCheckResult;  // 1C - (2 - (akViewer::HasLOS(akTarget) != 0))
		};
		static_assert(sizeof(LOSDataEvent) == 0x20);

		struct InventoryEventFilterLists : public BSIntrusiveRefCounted
		{
			// members
			BSTSet<FormID> itemsForFiltering;      // 08
			BSTSet<FormID> itemListsForFiltering;  // 38
		};
		static_assert(sizeof(InventoryEventFilterLists) == 0x68);

		struct ISendEventFilter
		{
			virtual bool matchesFilter(VMHandle handle) = 0;
		};

		~SkyrimVM() override;  // 00

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                 \
	mutable BSSpinLock registeredSleepEventsLock; /* 0754 */ \
	std::uint32_t      pad075C;                   /* 075C */
            RUNTIME_DATA_CONTENT
		};

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                               \
	mutable BSSpinLock                       registeredMenuEventsLock;  /* 0754 */                            \
	std::uint32_t                            pad075C;                   /* 075C */                            \
	BSTArray<BSTSmartPointer<MenuOpenClose>> registeredMenuEvents;      /* 0760 - RegisterForMenuOpenClose */ \
	mutable BSSpinLock                       registeredSleepEventsLock; /* 0778 */
            VR_RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                                                                                                \
	BSTSet<VMHandle>                                                      registeredSleepEvents;       /* 0760, VR0780 - RegisterForSleep */ \
	mutable BSSpinLock                                                    registeredStatsEventsLock;   /* 0810 */                            \
	BSTSet<VMHandle>                                                      registeredStatsEvents;       /* 0818 - RegisterForTrackedStats */  \
	BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>   renderSafeFunctorPool1;      /* 07E8 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>  renderSafeFunctorQueue1;     /* 2800 */                            \
	BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>   renderSafeFunctorPool2;      /* 2828 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>  renderSafeFunctorQueue2;     /* 4840 */                            \
	BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>   postRenderFunctorPool1;      /* 4868 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>  postRenderFunctorQueue1;     /* 6880 */                            \
	BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>   postRenderFunctorPool2;      /* 6908 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>  postRenderFunctorQueue2;     /* 88C0 */                            \
	mutable BSSpinLock                                                    renderSafeQueueLock;         /* 88E8 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>* renderSafeQueueToReadFrom;   /* 88F0 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>* renderSafeQueueToWriteTo;    /* 88F8 */                            \
	mutable BSSpinLock                                                    postRenderQueueLock;         /* 8900 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>* postRenderQueueToReadFrom;   /* 8908 */                            \
	BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>* postRenderQueueToWriteTo;    /* 8910 */                            \
	mutable BSSpinLock                                                    userLogMapLock;              /* 8918 */                            \
	BSTHashMap<const char*, SkyrimScript::Logger*>                        userLogMap;                  /* 8920 - Debug.OpenUserLog */        \
	mutable BSSpinLock                                                    currentVMOverstressTimeLock; /* 8950 */                            \
	std::uint32_t                                                         currentVMOverstressTime;     /* 8958 */                            \
	std::uint32_t                                                         lastVMStackDumpTime;         /* 895C */                            \
	mutable BSSpinLock                                                    InventoryEventFilterMapLock; /* 8960 */                            \
	BSTHashMap<VMHandle, InventoryEventFilterLists*>                      InventoryEventFilterMap;     /* 8968 - AddInventoryEventFilter */
            RUNTIME_DATA2_CONTENT
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x754, 0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x754, 0);
		}

		[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x754);
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x754);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x760, 0x780);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x760, 0x780);
		}

		static SkyrimVM* GetSingleton();

		bool QueuePostRenderCall(const BSTSmartPointer<SkyrimScript::DelayFunctor>& a_functor);
		void RelayEvent(VMHandle handle, BSFixedString* event, BSScript::IFunctionArguments* args, ISendEventFilter* optionalFilter);
		void SendAndRelayEvent(VMHandle handle, BSFixedString* event, BSScript::IFunctionArguments* args, ISendEventFilter* optionalFilter);

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> impl;                       // 0200
		BSScript::IVMSaveLoadInterface*            saveLoadInterface;          // 0208
		BSScript::IVMDebugInterface*               debugInterface;             // 0210
		BSScript::SimpleAllocMemoryPagePolicy      memoryPagePolicy;           // 0218
		BSScript::CompiledScriptLoader             scriptLoader;               // 0240
		SkyrimScript::Logger                       logger;                     // 0278
		SkyrimScript::HandlePolicy                 handlePolicy;               // 0328
		SkyrimScript::ObjectBindPolicy             objectBindPolicy;           // 0398
		BSTSmartPointer<SkyrimScript::Store>       scriptStore;                // 0470
		SkyrimScript::FragmentSystem               fragmentSystem;             // 0478
		SkyrimScript::Profiler                     profiler;                   // 0590
		SkyrimScript::SavePatcher                  savePatcher;                // 0670
		mutable BSSpinLock                         frozenLock;                 // 0678
		std::uint32_t                              isFrozen;                   // 0680
		mutable BSSpinLock                         currentVMTimeLock;          // 0684
		std::uint32_t                              currentVMTime;              // 068C
		std::uint32_t                              currentVMMenuModeTime;      // 0690
		std::uint32_t                              currentVMGameTime;          // 0694
		std::uint32_t                              currentVMDaysPassed;        // 0698 - Calender.GetDaysPassed() * 1000
		mutable BSSpinLock                         queuedWaitEventLock;        // 069C
		std::uint32_t                              pad06A4;                    // 06A4
		BSTArray<WaitCall>                         queuedWaitCalls;            // 06A8 - Utility.Wait() calls
		BSTArray<WaitCall>                         queuedWaitMenuModeCalls;    // 06C0 - Utility.WaitMenuMode() calls
		BSTArray<WaitCall>                         queuedWaitGameCalls;        // 06D8 - Utility.WaitGameTime() calls
		mutable BSSpinLock                         queuedLOSEventCheckLock;    // 06F0
		BSTArray<BSTSmartPointer<LOSDataEvent>>    queuedLOSEventChecks;       // 06F8 - OnGainLOS/OnLostLOS
		std::uint32_t                              currentLOSEventCheckIndex;  // 0710
		mutable BSSpinLock                         queuedOnUpdateEventLock;    // 0714
		std::uint32_t                              pad071C;                    // 071C
		BSTArray<BSTSmartPointer<UpdateDataEvent>> queuedOnUpdateEvents;       // 0720
		BSTArray<BSTSmartPointer<UpdateDataEvent>> queuedOnUpdateGameEvents;   // 0738
		std::uint32_t                              unk0750;                    // 0750
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;
#elif defined(SKYRIM_CROSS_VR)
#else
		RUNTIME_DATA2_CONTENT;
#endif

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#ifdef ENABLE_SKYRIM_AE
	static_assert(sizeof(SkyrimVM) == 0x760);
	#else
	static_assert(sizeof(SkyrimVM) == 0x760);
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(SkyrimVM) == 0x780);
#else
	static_assert(sizeof(SkyrimVM) == 0x758);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
