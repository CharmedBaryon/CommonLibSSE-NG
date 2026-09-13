#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class NiSwitchNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSwitchNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSwitchNode;
		inline static constexpr auto VTABLE = VTABLE_NiSwitchNode;

		~NiSwitchNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiSwitchNode* AsSwitchNode() override;                            // 04
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
		void          UpdateControllers(NiUpdateData& a_data) override;   // 25
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                       // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;               // 2D
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                  // 2E
		void UpdateWorldBound() override;                                                                   // 2F
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;               // 34
		void AttachChild(NiAVObject* a_child, bool a_firstAvail) override;                                  // 35
		void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut) override;                 // 37
		void DetachChild2(NiAVObject* a_child) override;                                                    // 38
		void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut) override;               // 39
		void DetachChildAt2(std::uint32_t a_idx) override;                                                  // 3A
		void SetAt1(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut) override;  // 3B
		void SetAt2(std::uint32_t a_idx, NiAVObject* a_child) override;                                     // 3C
#endif

		// members
		std::uint16_t                    flags;       // 128
		std::int32_t                     index;       // 12C
		float                            savedTime;   // 130
		std::uint32_t                    revID;       // 134
		NiTPrimitiveArray<std::uint32_t> childRevID;  // 138
	};
	STATIC_ASSERT_SIZE(NiSwitchNode, 0x150, 0x150, 0x178, 0x138);
}
