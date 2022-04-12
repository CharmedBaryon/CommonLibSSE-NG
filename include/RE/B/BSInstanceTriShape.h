#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTriShape.h"

namespace RE
{
	class BSInstanceTriShape : public BSTriShape
	{
	public:
		inline static auto RTTI = RTTI_BSInstanceTriShape;
		inline static auto Ni_RTTI = NiRTTI_BSInstanceTriShape;

		~BSInstanceTriShape() override;  // 00

		// override (BSTriShape)
		const NiRTTI* GetRTTI() const override;  // 02

		// add
		void          BeginAddingInstances(std::uint32_t a_numFloatsPerInstance);                                                 // 38
		void          AddInstances(std::uint32_t a_numInstances, std::uint16_t& a_instanceData);                                  // 39
		void          DoneAddingInstances(BSTArray<std::uint32_t>& a_instances);                                                  // 3A
		bool          GetIsAddingInstances();                                                                                     // 3B
		std::uint32_t AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4);  // 3C
		void          RemoveGroup(std::uint32_t a_numInstance);                                                                   // 3D
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(BSInstanceTriShape) == 0x160);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSInstanceTriShape) == 0x1A8);
#endif
}
