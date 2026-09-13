#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSThread.h"

namespace RE
{
	struct BSJobs
	{
		struct cpuInfo_t
		{
			struct cacheInfo_t
			{
				std::int32_t count;          // 00
				std::int32_t associativity;  // 04
				std::int32_t lineSize;       // 08
				std::int32_t size;           // 0C
			};
			static_assert(sizeof(cacheInfo_t) == 0x10);

			std::int32_t processorPackageCount;
			std::int32_t processorCoreCount;
			std::int32_t logicalProcessorCount;
			std::int32_t numaNodeCount;
			cacheInfo_t  cacheLevel[3];
		};
		static_assert(sizeof(cpuInfo_t) == 0x40);

		class JobListLocal
		{
		public:
			struct JobInstance
			{
				using func_t = void(void*);
				func_t* func;  // 00
				void*   data;  // 08
			};
			static_assert(sizeof(JobInstance) == 0x10);

			BSTArray<JobInstance>                   jobArray;                   // 00
			BSTArray<BSTAtomicValue<std::int64_t>>  signalJobCountArray;        // 18
			BSTArray<BSTAtomicValue<std::int64_t>>  signalJobCountArrayStatic;  // 30
			BSTArray<BSTAtomicValue<std::uint32_t>> stalledJobCountArray;       // 48
			BSFixedString                           name;                       // 60
			BSEventFlag                             threadSignOffEvent;         // 68
			BSTAtomicValue<std::int64_t>            doneGuards[4];              // 70
			BSTAtomicValue<std::int64_t>            currentJob;                 // 90
			BSTAtomicValue<std::int64_t>            numThreadsSignedUp;         // 98
			BSTAtomicValue<std::int64_t>            version;                    // A0
			BSTAtomicValue<std::int64_t>*           waitForGuard;               // A8
			BSEventFlag*                            eventFlag;                  // B0
			std::uint32_t                           numSyncs;                   // B8
			std::uint32_t                           maxJobs;                    // BC
			std::uint32_t                           batchSize;                  // C0
			std::uint32_t                           lastSignalJob;              // C4
			std::uint32_t                           currentDoneGuard;           // C8
			std::uint32_t                           usedThreads;                // CC
			std::uint32_t                           flags;                      // D0
			std::uint8_t                            overallPriority;            // D4
		};
		static_assert(sizeof(JobListLocal) == 0xD8);

		class JobList
		{
		public:
			JobListLocal* jobList;  // 00
		};
		static_assert(sizeof(JobList) == 0x8);

		class ThreadJobListState
		{
		public:
			void*         jobList;         // 00
			std::int32_t  version;         // 08
			std::uint32_t signalIndex;     // 0C
			std::uint32_t lastJobIndex;    // 10
			std::uint32_t nextJobIndex;    // 14
			bool          singleThreaded;  // 18
			std::uint8_t  priority;        // 19
		};
		static_assert(sizeof(ThreadJobListState) == 0x20);

		class SubmitJobDesc
		{
		public:
			JobListLocal* jobList;           // 00
			std::uint32_t jobIndexStart;     // 08
			std::uint32_t signalIndexStart;  // 0C
			std::int32_t  version;           // 10
		};
		static_assert(sizeof(SubmitJobDesc) == 0x18);

		class JobThread : public BSThread
		{
		public:
			class SubmitRingBuffer
			{
			public:
				class Desc : public SubmitJobDesc
				{
					BSTAtomicValue<int> toConsume;
					BSTAtomicValue<int> toConsumeCommit;
				};
				static_assert(sizeof(Desc) == 0x20);

				Desc                                   bufferArray[256];  // 00
				BSTAtomicValue<std::uint64_t volatile> cursor;            // 2000
				volatile std::uint64_t                 committed;         // 2008
				BSTAtomicValue<std::uint64_t volatile> claimed;           // 2010
			};
			static_assert(sizeof(SubmitRingBuffer) == 0x2018);

			inline static constexpr auto RTTI = RTTI_BSJobs__JobThread;
			inline static constexpr auto VTABLE = VTABLE_BSJobs__JobThread;

			~JobThread() override;  // 00

			// add
			std::uint32_t ThreadProc(void) override;  // 01
			void          Unk_02(void) override;      // 02

			// members
			ThreadJobListState stateArray[64];           // 50
			std::uint32_t      linkArray[64][2];         // 850
			BSSemaphore*       semaphore;                // A50;
			SubmitRingBuffer*  ringBuffer;               // A58
			std::uint64_t      nextRingFetch;            // A60
			std::uint32_t      nextAvailableStateIndex;  // A68
			std::uint32_t      activeStateList;          // A6C
			std::uint32_t      threadNumber;             // A70
			volatile bool      shutDown;                 // A74
		};
		static_assert(sizeof(JobThread) == 0xA78);
	};
}
