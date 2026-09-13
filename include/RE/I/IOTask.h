#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTask.h"

namespace RE
{
	class QueuedFile;

	class IOTask : public BSTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_IOTask;
		inline static constexpr auto VTABLE = VTABLE_IOTask;

		~IOTask() override;  // 00

		// add
		virtual void Unk_05() { return; }  // 05
		virtual void Unk_06() { return; }  // 06
		virtual void Unk_07() { return; }  // 07
		virtual void Unk_08() { return; }  // 08

		// VR inherits BSTask's own +8-byte insertion, shifting this tail by +8.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                                        \
	BSTSmartPointer<QueuedFile> dependency; /* 20 - related/dependency task; may be null */                                                         \
	void*                       children;   /* 28 - pointer to a child-tracking object (finishedCount + a child-task array); null when childless */ \
	std::int32_t                state;      /* 30 - task state; see QueuedFile::ProcessStateMachine */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                                                     \
	BSTSmartPointer<QueuedFile> dependency; /* 28 - related/dependency task; may be null */                                                         \
	void*                       children;   /* 30 - pointer to a child-tracking object (finishedCount + a child-task array); null when childless */ \
	std::int32_t                state;      /* 38 - task state; see QueuedFile::ProcessStateMachine */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x18);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x20, 0x0);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x28);

		// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 20
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 28
#endif
	};
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(IOTask, 0x38, 0x40);
}
