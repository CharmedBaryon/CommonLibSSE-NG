#pragma once

#include "RE/B/BSInstanceTriShape.h"

namespace RE
{
	class BSMultiStreamInstanceTriShape : public BSInstanceTriShape
	{
	public:
		inline static auto RTTI = RTTI_BSMultiStreamInstanceTriShape;
		inline static auto Ni_RTTI = NiRTTI_BSMultiStreamInstanceTriShape;

		~BSMultiStreamInstanceTriShape() override;  // 00

		// override (BSInstanceTriShape)
		const NiRTTI* GetRTTI() const override;                                                                                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                   // 17
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          OnVisible(NiCullingProcess& a_process) override;                                                                     // 34

		// overrides for BSTriShape
//		void          Unk_37(void) override;                                                                                               // 37
//		void          BeginAddingInstances(std::uint32_t a_numFloatsPerInstance) override;                                                 // 38
//		void          AddInstances(std::uint32_t a_numFloatsPerInstance, std::uint16_t& a_instanceData) override;                          // 39
//		void          DoneAddingInstances(BSTArray<std::uint32_t>& a_instances) override;                                                  // 3A
//		bool          GetIsAddingInstances() override;                                                                                     // 3B
//		std::uint32_t AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4) override;  // 3C
//		void          RemoveGroup(std::uint32_t a_numInstance) override;                                                                   // 3D

		// members
		BSTArray<void*> unk160;  // 160
		std::uint32_t   unk178;  // 178
		std::uint32_t   unk17C;  // 17C
		std::uint64_t   unk180;  // 180
		std::uint64_t   unk188;  // 188
		std::uint32_t   unk190;  // 190
		std::uint32_t   unk194;  // 194
		std::uint32_t   unk198;  // 198
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSMultiStreamInstanceTriShape) == 0x1E8);
#else
	static_assert(sizeof(BSMultiStreamInstanceTriShape) == 0x1A0);
#endif
}
