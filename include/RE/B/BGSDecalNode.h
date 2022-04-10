#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSTempEffect;

	class BGSDecalNode : public NiNode
	{
	public:
		inline static auto RTTI = RTTI_BGSDecalNode;
		inline static auto Ni_RTTI = NiRTTI_BGSDecalNode;

		~BGSDecalNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          OnVisible(NiCullingProcess& a_process) override;     // 34

		// add
		std::uint8_t Unk_3E();                                               // 3E - { return 1; }
		void         AttachDecal(BSTempEffect* a_decal, bool a_firstAvail);  // 3F

		// members
		BSTArray<NiPointer<BSTempEffect>> decals;     // 128
		bool                              isSkinned;  // 140
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BGSDecalNode) == 0x170);
#else
	static_assert(sizeof(BGSDecalNode) == 0x148);
#endif
}
