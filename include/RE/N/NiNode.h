#pragma once

#include "RE/N/NiAVObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class NiUpdateData;

	class NiNode : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiNode;
		inline static constexpr auto VTABLE = VTABLE_NiNode;

		~NiNode() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiNode*       AsNode() override;                                   // 03 - { return this; }
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
		void          UpdateControllers(NiUpdateData& a_data) override;    // 25
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void        PerformOp(PerformOpFunc& a_func) override;                                                                   // 26
		void        AttachProperty(NiAlphaProperty* a_property) override;                                                        // 27
		NiAVObject* GetObjectByName(const BSFixedString& a_name) override;                                                       // 2A
		void        SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  // 2B
		void        UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                     // 2C
		void        UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                             // 2D
		void        UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                // 2E
		void        UpdateWorldBound() override;                                                                                 // 2F
		void        UpdateTransformAndBounds(NiUpdateData& a_data) override;                                                     // 31
		void        OnVisible(NiCullingProcess& a_process) override;                                                             // 34
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void AttachChild(NiAVObject* a_child, bool a_firstAvail = false);                          // 35
		SKYRIM_REL_VR_VIRTUAL void InsertChildAt(std::uint32_t a_idx, NiAVObject* a_child);                              // 36
		SKYRIM_REL_VR_VIRTUAL void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);                 // 37
		SKYRIM_REL_VR_VIRTUAL void DetachChild2(NiAVObject* a_child);                                                    // 38
		SKYRIM_REL_VR_VIRTUAL void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut);               // 39
		SKYRIM_REL_VR_VIRTUAL void DetachChildAt2(std::uint32_t a_idx);                                                  // 3A
		SKYRIM_REL_VR_VIRTUAL void SetAt1(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);  // 3B
		SKYRIM_REL_VR_VIRTUAL void SetAt2(std::uint32_t a_idx, NiAVObject* a_child);                                     // 3C
		SKYRIM_REL_VR_VIRTUAL void UpdateUpwardPass(NiUpdateData& a_data);                                               // 3D

		static NiNode* Create(std::uint16_t a_arrBufLen = 0);

		[[nodiscard]] inline NiTObjectArray<NiPointer<NiAVObject>>& GetChildren() noexcept
		{
			return REL::RelocateMember<NiTObjectArray<NiPointer<NiAVObject>>>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const NiTObjectArray<NiPointer<NiAVObject>>& GetChildren() const noexcept
		{
			return REL::RelocateMember<NiTObjectArray<NiPointer<NiAVObject>>>(this, 0x110, 0x138);
		}

		void DetachChild(NiAVObject* a_child);
		void DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);
		void DetachChildAt(std::uint32_t a_idx);
		void DetachChildAt(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut);
		void SetAt(std::uint32_t a_idx, NiAVObject* a_child);
		void SetAt(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);

		// members
#ifndef SKYRIM_CROSS_VR
		NiTObjectArray<NiPointer<NiAVObject>> children;  // 110, 138
#endif

	protected:
		NiNode* Ctor(std::uint16_t a_arrBufLen);

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiNode) == 0x128);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiNode) == 0x150);
#endif
}
