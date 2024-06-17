#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTriShape.h"

namespace RE
{
	class BSInstanceTriShape : public BSTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSInstanceTriShape;
		inline static auto           Ni_RTTI = NiRTTI_BSInstanceTriShape;

		~BSInstanceTriShape() override;  // 00

		// override (BSTriShape)
		const NiRTTI* GetRTTI() const override;  // 02

		// add
		SKYRIM_REL_VR_VIRTUAL void BeginAddingInstances(std::uint32_t a_numFloatsPerInstance);                                                          // 38
		SKYRIM_REL_VR_VIRTUAL void AddInstances(std::uint32_t a_numInstances, std::uint16_t& a_instanceData);                                           // 39
		SKYRIM_REL_VR_VIRTUAL void DoneAddingInstances(BSTArray<std::uint32_t>& a_instances);                                                           // 3A
		SKYRIM_REL_VR_VIRTUAL bool GetIsAddingInstances();                                                                                              // 3B
		SKYRIM_REL_VR_VIRTUAL std::uint32_t AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4);  // 3C
		SKYRIM_REL_VR_VIRTUAL void          RemoveGroup(std::uint32_t a_numInstance);                                                                   // 3D
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(BSInstanceTriShape) == 0x160);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSInstanceTriShape) == 0x1A8);
#endif
}
