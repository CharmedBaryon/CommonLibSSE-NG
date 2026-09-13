#pragma once

#include "RE/B/BSMultiBoundNode.h"
#include "RE/N/NiTPointerList.h"

namespace RE
{
	class BSLight;
	class BSOcclusionShape;
	class BSPortal;

	class BSMultiBoundRoom : public BSMultiBoundNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiBoundRoom;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiBoundRoom;
		inline static constexpr auto VTABLE = VTABLE_BSMultiBoundRoom;

		~BSMultiBoundRoom() override;  // 00

		// override (BSMultiBoundNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void              UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void              UpdateWorldBound() override;                                                      // 2F
		void              OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
		BSMultiBoundRoom* GetMultiBoundRoom() override;                                                     // 3E - { return this; }
		bool              QPointWithin(const NiPoint3& a_point) override;                                   // 3F
		bool              CheckBound1(const BSMultiBound& a_targetBound) override;                          // 40
		bool              CheckBound2(const NiBound& a_targetBound) override;                               // 41
#endif

		// members
		NiTPointerList<BSPortal*>               portalList;            // 138
		NiTPointerList<BSOcclusionShape*>       occluderList;          // 150
		NiTPointerList<NiPointer<BSMultiBound>> joinedMultiBoundList;  // 168
		BSTArray<BSLight*>                      lights;                // 180
	};
	STATIC_ASSERT_SIZE(BSMultiBoundRoom, 0x198, 0x1C0);
}
