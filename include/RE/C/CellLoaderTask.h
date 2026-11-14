#pragma once

#include "RE/I/IOTask.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class ExteriorCellLoader;
	class TESObjectCELL;
	class TESWorldSpace;

	class CellLoaderTask : public IOTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_CellLoaderTask;
		inline static constexpr auto VTABLE = VTABLE_CellLoaderTask;

		~CellLoaderTask() override;  // 00

		// override (BSTask)
		void Run() override;                                                   // 01
		void Finish() override;                                                // 02
		void Cancel(std::uint32_t a_previousState, void* a_unk) override;      // 03
		bool GetDescription(char* a_dest, std::uint32_t a_maxCount) override;  // 04

		// override (IOTask)
		void PostProcess() override;  // 06

		// VR's BSTask is 8 bytes larger, shifting these members by +8.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                     \
	ExteriorCellLoader* loader;   /* 18 */                                                       \
	TESWorldSpace*      world;    /* 20 */                                                       \
	TESObjectCELL*      cell;     /* 28 */                                                       \
	std::int32_t        x;        /* 30 */                                                       \
	std::int32_t        y;        /* 34 */                                                       \
	std::uint32_t       state;    /* 38 - advanced with InterlockedCompareExchange */            \
	bool                interior; /* 3C - selects the interior-cell load path and description */ \
	bool                unk3D;    /* 3D */                                                       \
	std::uint8_t        pad3E[2]; /* 3E */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x28);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x18, 0x20);

		// members
#if !defined(SKYRIM_CROSS_VR)
		RUNTIME_DATA_CONTENT;  // 18
#endif
	};
#undef RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(CellLoaderTask, 0x40, 0x48);
}
