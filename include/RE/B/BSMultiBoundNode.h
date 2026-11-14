#pragma once

#include "RE/B/BSCullingProcess.h"
#include "RE/B/BSNiNode.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSMultiBound;
	class BSMultiBoundRoom;
	class NiPoint3;

	class BSMultiBoundNode : public BSNiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiBoundNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiBoundNode;
		inline static constexpr auto VTABLE = VTABLE_BSMultiBoundNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                  \
	NiPointer<BSMultiBound>           multiBound;    /* 00 */ \
	BSCullingProcess::BSCPCullingType cullingMode;   /* 08 */ \
	float                             lastAccumTime; /* 0C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		~BSMultiBoundNode() override;  // 00

		// override (BSNiNode)
		const NiRTTI*     GetRTTI() const override;                           // 02
		BSMultiBoundNode* AsMultiBoundNode() override;                        // 06 - { return this; }
		NiObject*         CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void              LoadBinary(NiStream& a_stream) override;            // 18
		void              LinkObject(NiStream& a_stream) override;            // 19
		bool              RegisterStreamables(NiStream& a_stream) override;   // 1A
		void              SaveBinary(NiStream& a_stream) override;            // 1B
		bool              IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void UpdateWorldBound() override;                                                      // 2F
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
		void UpdateUpwardPass(NiUpdateData& a_data) override;                                  // 3D
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL BSMultiBoundRoom* GetMultiBoundRoom();                             // 3E - { return 0; }
		SKYRIM_REL_VR_VIRTUAL bool              QPointWithin(const NiPoint3& a_point);           // 3F
		SKYRIM_REL_VR_VIRTUAL bool              CheckBound1(const BSMultiBound& a_targetBound);  // 40
		SKYRIM_REL_VR_VIRTUAL bool              CheckBound2(const NiBound& a_targetBound);       // 41

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x128, 0x150);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
	STATIC_ASSERT_SIZE(BSMultiBoundNode, 0x138, 0x160);
}
#undef RUNTIME_DATA_CONTENT
