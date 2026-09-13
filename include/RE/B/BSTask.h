#pragma once

#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTask;
		inline static constexpr auto VTABLE = VTABLE_BSTask;

		virtual ~BSTask() = default;       // 00
		virtual void Unk_01() { return; }  // 01
		virtual void Unk_02() { return; }  // 02
		virtual void Unk_03() { return; }  // 03
		virtual void Unk_04() { return; }  // 04

		// VR inserts 8 unidentified bytes here instead of appending a trailing
		// tail, shifting the following field by +8.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	std::int32_t threadDepthMarker; /* 18 - set from a TLS slot during construction */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x4);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                       \
	std::uint8_t unk18[8];          /* 18 - VR-only insertion; byte 0 is zeroed at construction, rest unidentified */ \
	std::int32_t threadDepthMarker; /* 20 - set from a TLS slot during construction */
			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0xC);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x18, 0x20);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x18);

		// members
		std::int32_t  refCount;  // 08
		std::uint32_t unk0C;     // 0C
		std::uint8_t  unk10[2];  // 10
		std::uint8_t  priority;  // 12 - task priority/type byte
		std::uint8_t  unk13[5];  // 13
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 18
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 18
#endif
	};
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(BSTask, 0x20, 0x28);
}
