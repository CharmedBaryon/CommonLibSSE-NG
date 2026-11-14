#pragma once

#include "RE/B/BSTHashMap.h"
#include "RE/N/NiNode.h"

namespace RE
{
	class BSFlattenedBoneTree : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFlattenedBoneTree;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFlattenedBoneTree;
		inline static constexpr auto VTABLE = VTABLE_BSFlattenedBoneTree;

		~BSFlattenedBoneTree() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#ifndef SKYRIM_CROSS_VR
		NiAVObject* GetObjectByName(const BSFixedString& a_name) override;                            // 2A
		void        UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void        UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
		void        UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;     // 2E
#endif

		struct BoneEntry
		{
			NiTransform   local;             // 00
			NiTransform   world;             // 34
			std::int16_t  parentIndex;       // 68
			std::int16_t  unk6A;             // 6A  (always -1?? purpose unclear)
			std::uint16_t childCount;        // 6C  (number of children)
			std::int16_t  nextSiblingIndex;  // 6E  (next sibling, -1 = last
			NiAVObject*   node;              // 70
			BSFixedString nodeName;          // 78
		};
		static_assert(sizeof(BoneEntry) == 0x80);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                             \
	std::uint32_t                           numBones;          /* 128 */ \
	std::uint32_t                           numPopulatedBones; /* 12C */ \
	BoneEntry*                              boneEntries;       /* 130 */ \
	BSTHashMap<BSFixedString, std::int32_t> boneMap;           /* 138 */

			RUNTIME_DATA_CONTENT
		};
		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x128, 0x150);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 128, 150
#endif
	};
	STATIC_ASSERT_SIZE(BSFlattenedBoneTree, 0x168, 0x168, 0x190);
}
#undef RUNTIME_DATA_CONTENT
