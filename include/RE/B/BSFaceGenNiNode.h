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
		inline static constexpr auto RTTI = RTTI_BSFaceGenNiNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFaceGenNiNode;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenNiNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                  \
	NiMatrix3                         baseRotation;  /* 00 */ \
	std::uint32_t                     pad14C;        /* 24 */ \
	NiPointer<BSFaceGenAnimationData> animationData; /* 28 */ \
	float                             lastTime;      /* 30 */ \
	ActorHandle                       unk15C;        /* 34 */ \
	std::uint16_t                     flags;         /* 38 */ \
	std::uint16_t                     pad162;        /* 3A */ \
	std::uint32_t                     pad164;        /* 3C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x40);

		~BSFaceGenNiNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2C
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void FixSkinInstances(NiNode* a_skeleton, bool a_arg2);  // 3E

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSFaceGenNiNode) == 0x168);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSFaceGenNiNode) == 0x190);
#endif
}
#undef RUNTIME_DATA_CONTENT
