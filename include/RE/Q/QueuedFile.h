#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IOTask.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class QueuedFile : public IOTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_QueuedFile;
		inline static constexpr auto VTABLE = VTABLE_QueuedFile;

		~QueuedFile() override;  // 00

		// override (BSTask)
		void Run() override;                                               // 01 - { return; }
		void Finish() override;                                            // 02
		void Cancel(std::uint32_t a_previousState, void* a_unk) override;  // 03

		// override (IOTask)
		void Requeue(std::uint32_t a_newPriority) override;  // 08

		// add
		virtual void DoOnQueueMe();           // 09 - { return; }
		virtual void DoOnChildrenFinished();  // 0A - { return; }
		virtual void DoOnTaskFinished();      // 0B - { return; }

		// VR's BSTask is 8 bytes larger, shifting these members by +8.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                                               \
	std::int32_t                threadDepthMarker; /* 18 - set from a TLS slot during construction */                                                      \
	std::uint32_t               pad1C;             /* 1C */                                                                                                \
	BSTSmartPointer<QueuedFile> parent;            /* 20 - may be null */                                                                                  \
	void*                       children;          /* 28 - pointer to a child-tracking object (finishedCount + a child-task array); null when childless */ \
	std::int32_t                state;             /* 30 - task state */                                                                                   \
	std::uint32_t               pad34;             /* 34 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x18, 0x20);

		// members
#if !defined(SKYRIM_CROSS_VR)
		RUNTIME_DATA_CONTENT;  // 18
#endif
	};
#undef RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(QueuedFile, 0x38, 0x40);
}
