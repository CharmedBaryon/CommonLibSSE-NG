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
		inline static constexpr auto RTTI = RTTI_BGSDecalNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BGSDecalNode;
		inline static constexpr auto VTABLE = VTABLE_BGSDecalNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	BSTArray<NiPointer<BSTempEffect>> decals;    /* 00 */ \
	bool                              isSkinned; /* 18 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~BGSDecalNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process) override;  // 34
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL std::uint8_t Unk_3E();                                               // 3E - { return 1; }
		SKYRIM_REL_VR_VIRTUAL void         AttachDecal(BSTempEffect* a_decal, bool a_firstAvail);  // 3F

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
	static_assert(sizeof(BGSDecalNode) == 0x148);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BGSDecalNode) == 0x170);
#endif
}
#undef RUNTIME_DATA_CONTENT
