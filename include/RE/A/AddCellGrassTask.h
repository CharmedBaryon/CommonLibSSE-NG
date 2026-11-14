#pragma once

#include "RE/Q/QueuedFile.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class TESObjectCELL;

	class AddCellGrassTask : public QueuedFile
	{
	public:
		inline static constexpr auto RTTI = RTTI_AddCellGrassTask;
		inline static constexpr auto VTABLE = VTABLE_AddCellGrassTask;

		~AddCellGrassTask() override;  // 00

		// override (BSTask)
		void Run() override;     // 01
		void Finish() override;  // 02

		// override (IOTask)
		void PostProcess() override;  // 06

		static void CreateGrassLoadTaskForCell(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&AddCellGrassTask::CreateGrassLoadTaskForCell);
			static REL::Relocation<func_t> func{ RELOCATION_ID(13137, 13277) };
			func(a_cell);
		}

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT          \
	TESObjectCELL* cell;     /* 38 */ \
	std::int32_t   x;        /* 40 */ \
	std::int32_t   y;        /* 44 */ \
	bool           cancel;   /* 48 */ \
	std::uint8_t   pad49[7]; /* 49 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x38, 0x40);

		// members
#if !defined(SKYRIM_CROSS_VR)
		RUNTIME_DATA_CONTENT;  // 38
#endif
	};
#undef RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(AddCellGrassTask, 0x50, 0x58);
}
