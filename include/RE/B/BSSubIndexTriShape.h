#pragma once

#include "RE/B/BSTriShape.h"

namespace RE
{
	struct SegmentData
	{
		std::uint32_t index;        // 00
		std::uint32_t unkTriCount;  // 04
		std::uint8_t  unkFlags;     // 08
		std::uint32_t numTris;      // 0C
		std::uint8_t  flags;        // 10
	};

	class BSSubIndexTriShape : public BSTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSubIndexTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSSubIndexTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSSubIndexTriShape;

		struct SUB_INDEX_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT             \
	SegmentData*  segmentData;  /* 00 */ \
	std::uint32_t numSegments;  /* 08 */ \
	std::uint32_t unkSegCount;  /* 0C */ \
	bool          unk170;       /* 10 */ \
	bool          nonSegmented; /* 14 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(SUB_INDEX_TRISHAPE_RUNTIME_DATA) == 0x18);

		~BSSubIndexTriShape() override;  // 00

		// override (BSTriShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void          OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
		std::uint32_t GetVisibleGroupsTriangleCount() override;                                         // 37
#endif

		RUNTIME_DATA_ACCESSOR_EX(SUB_INDEX_TRISHAPE_RUNTIME_DATA, GetSubIndexedTrishapeRuntimeData, 0x160, 0x1A0);

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 160, 1A0
#endif
	};
	STATIC_ASSERT_SIZE(BSSubIndexTriShape, 0x178, 0x178, 0x1B8, 0x110);
}
#undef RUNTIME_DATA_CONTENT
