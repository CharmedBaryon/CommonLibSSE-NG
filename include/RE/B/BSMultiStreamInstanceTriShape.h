#pragma once

#include "RE/B/BSInstanceTriShape.h"
#include "RE/B/BSMultiBoundAABB.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	namespace BSGraphics
	{
		struct VertexBuffer
		{
			REX::W32::ID3D11Buffer* buffer;
			void*                   m_data;
			size_t                  byteWidth;
		};
		static_assert(sizeof(VertexBuffer) == 0x18);
	}

	class BSMultiStreamInstanceTriShape : public BSInstanceTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiStreamInstanceTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiStreamInstanceTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSMultiStreamInstanceTriShape;

		class InstanceGroup : public BSMultiBoundAABB
		{
		public:
			BSGraphics::VertexBuffer* vertexBuffer;   // 40
			std::uint32_t             triCount;       // 48
			std::uint32_t             instanceCount;  // 4C
			bool                      isVisible;      // 50
		};
		static_assert(sizeof(InstanceGroup) == 0x58);

		struct GroupHeader
		{
			RE::NiPoint3  center;
			RE::NiPoint3  size;
			std::uint32_t triCount;
			std::uint32_t groupInstanceCount;
			std::uint32_t numShortsPerInstance;
		};
		static_assert(sizeof(GroupHeader) == 0x24);

		struct GroupAttachTask
		{
			RE::BSMultiStreamInstanceTriShape*                trishape;
			RE::BSMultiStreamInstanceTriShape::InstanceGroup* instanceGroup;
			BSTArray<std::uint32_t>*                          groupIndicies;
		};
		static_assert(sizeof(GroupAttachTask) == 0x18);

		struct MULTISTREAM_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                \
	BSTArray<InstanceGroup*> instanceGroups;       /* 00 */ \
	std::uint32_t            meshTriCount;         /* 18 */ \
	std::uint32_t            maxInstancesPerGroup; /* 1C */ \
	float                    renderDistance;       /* 20 */ \
	std::uint32_t            unk184;               /* 24 */ \
	void*                    groupAlloc;           /* 28 */ \
	std::uint32_t            instanceCount;        /* 30 */ \
	std::uint32_t            instanceSize;         /* 34 */ \
	std::uint32_t            activeGroupCount;     /* 38 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(MULTISTREAM_TRISHAPE_RUNTIME_DATA) == 0x40);

		~BSMultiStreamInstanceTriShape() override;  // 00

		// override (BSInstanceTriShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		// VR inserts a virtual before these slots; keep the SE/AE and VR indices paired.
		SKYRIM_REL_VR_VIRTUAL void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex);  // 34/35

		// overrides for BSTriShape
		SKYRIM_REL_VR_VIRTUAL std::uint32_t GetVisibleGroupsTriangleCount();                                                                            // 37/38
		SKYRIM_REL_VR_VIRTUAL void          BeginAddingInstances(std::uint32_t a_numFloatsPerInstance);                                                 // 38/39
		SKYRIM_REL_VR_VIRTUAL void          AddInstances(std::uint32_t a_numFloatsPerInstance, std::uint16_t& a_instanceData);                          // 39/3A
		SKYRIM_REL_VR_VIRTUAL void          DoneAddingInstances(BSTArray<std::uint32_t>& a_instances);                                                  // 3A/3B
		SKYRIM_REL_VR_VIRTUAL bool          GetIsAddingInstances();                                                                                     // 3B/3C
		SKYRIM_REL_VR_VIRTUAL std::uint32_t AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4);  // 3C/3D
		SKYRIM_REL_VR_VIRTUAL void          RemoveGroup(std::uint32_t a_numInstance);                                                                   // 3D/3E

		RUNTIME_DATA_ACCESSOR_EX(MULTISTREAM_TRISHAPE_RUNTIME_DATA, GetMultiStreamTrishapeRuntimeData, 0x160, 0x1A0);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 160, 1A0
#endif
	};
	STATIC_ASSERT_SIZE(BSMultiStreamInstanceTriShape, 0x1A0, 0x1A0, 0x1E0, 0x110);
}
#undef RUNTIME_DATA_CONTENT
