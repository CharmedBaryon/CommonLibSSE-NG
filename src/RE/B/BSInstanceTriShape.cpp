#include "RE/B/BSInstanceTriShape.h"

using namespace REL;

namespace RE
{
	void BSInstanceTriShape::BeginAddingInstances(std::uint32_t a_numFloatsPerInstance)
	{
		RelocateVirtual<decltype(&BSInstanceTriShape::BeginAddingInstances)>(0x38, 0x39, this, a_numFloatsPerInstance);
	}

	void BSInstanceTriShape::AddInstances(std::uint32_t a_numInstances, std::uint16_t& a_instanceData)
	{
		RelocateVirtual<decltype(&BSInstanceTriShape::AddInstances)>(0x39, 0x3A, this, a_numInstances, a_instanceData);
	}

	void BSInstanceTriShape::DoneAddingInstances(BSTArray<std::uint32_t>& a_instances)
	{
		RelocateVirtual<decltype(&BSInstanceTriShape::DoneAddingInstances)>(0x3A, 0x3B, this, a_instances);
	}

	bool BSInstanceTriShape::GetIsAddingInstances()
	{
		return RelocateVirtual<decltype(&BSInstanceTriShape::GetIsAddingInstances)>(0x3B, 0x3C, this);
	}

	std::uint32_t BSInstanceTriShape::AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4)
	{
		return RelocateVirtual<decltype(&BSInstanceTriShape::AddGroup)>(0x3C, 0x3D, this, a_numInstances, a_instanceData, a_arg3, a_arg4);
	}

	void BSInstanceTriShape::RemoveGroup(std::uint32_t a_numInstance)
	{
		RelocateVirtual<decltype(&BSInstanceTriShape::RemoveGroup)>(0x3D, 0x3E, this, a_numInstance);
	}
}
