#pragma once

#include "RE/B/BSNiNode.h"

namespace RE
{
	class BSOrderedNode : public BSNiNode
	{
	public:
		inline static auto RTTI = RTTI_BSOrderedNode;
		inline static auto Ni_RTTI = NiRTTI_BSOrderedNode;

		~BSOrderedNode() override;  // 00

		// override (BSNiNode)
		const NiRTTI* GetRTTI() const override;                                                         // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                // 17
		void          LoadBinary(NiStream& a_stream) override;                                          // 18
		void          LinkObject(NiStream& a_stream) override;                                          // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                 // 1A
		void          SaveBinary(NiStream& a_stream) override;                                          // 1B
		bool          IsEqual(NiObject* a_object) override;                                             // 1C
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
//		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
//		void          OnVisible(NiCullingProcess& a_process) override;                                  // 34

		// members
		NiBound       orderedBound;    // 128
		bool          useStaticBound;  // 138
		std::uint32_t pad13C;          // 13C
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSOrderedNode) == 0x168);
#else
	static_assert(sizeof(BSOrderedNode) == 0x140);
#endif
}
