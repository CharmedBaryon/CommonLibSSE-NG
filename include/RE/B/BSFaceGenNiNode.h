#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSFaceGenAnimationData;
	class NiNode;

	class BSFaceGenNiNode : public NiNode
	{
	public:
		inline static auto RTTI = RTTI_BSFaceGenNiNode;
		inline static auto Ni_RTTI = NiRTTI_BSFaceGenNiNode;

		~BSFaceGenNiNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                                                 // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                        // 17
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2C

		// add
		void FixSkinInstances(NiNode* a_skeleton, bool a_arg2);  // 3E

		// members
		NiMatrix3                         baseRotation;   // 128
		std::uint32_t                     pad14C;         // 14C
		NiPointer<BSFaceGenAnimationData> animationData;  // 150
		float                             lastTime;       // 158
		ActorHandle                       unk15C;         // 15C
		std::uint16_t                     flags;          // 160
		std::uint16_t                     pad162;         // 162
		std::uint32_t                     pad164;         // 164
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSFaceGenNiNode) == 0x190);
#else
	static_assert(sizeof(BSFaceGenNiNode) == 0x168);
#endif
}
