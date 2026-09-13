#pragma once

#include "RE/B/BSJobs.h"

namespace RE
{
	class BSEventFlag;

	struct JobListManager
	{
		enum RUNNING_STATE
		{
			kNone = 0,
			kJobs = 1,
			kLoadScreen = 2
		};

		struct JOB_FUNC
		{
			using func_t = void(void*);
			func_t*     func;  // 00
			const char* name;  // 08
		};

		class ManagerJL : public BSJobs::JobList
		{
		public:
			BSEventFlag     jobsDone;  // 08
			const JOB_FUNC* endFunc;   // 10
		};
		static_assert(sizeof(ManagerJL) == 0x18);

		class ServingThread : public BSThread, BSTSingletonSDM<ServingThread>
		{
		public:
			inline static constexpr auto RTTI = RTTI_JobListManager__ServingThread;
			inline static constexpr auto VTABLE = VTABLE_JobListManager__ServingThread;

			static ServingThread* GetSingleton()
			{
				static REL::Relocation<ServingThread**> singleton{ RELOCATION_ID(516848, 403107) };
				return *singleton;
			}

			~ServingThread() override;  // 00

			// override
			std::uint32_t ThreadProc() override;  // 01

			// members
			BSEventFlag   newWork;      // 58
			BSEventFlag   workDone;     // 60
			RUNNING_STATE states[2];    // 68
			volatile bool bShutDown;    // 70
			volatile bool bProcessing;  // 71
			volatile bool bRunning;     // 72
		};
		static_assert(sizeof(ServingThread) == 0x78);
	};
}
