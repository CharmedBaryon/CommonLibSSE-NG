#include "RE/B/BSMultiStreamInstanceTriShape.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSMultiStreamInstanceTriShape::OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex)
	{
		REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::OnVisible)>(0x34, 0x35, this, a_process, a_alphaGroupIndex);
	}

	std::uint32_t BSMultiStreamInstanceTriShape::GetVisibleGroupsTriangleCount()
	{
		return REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::GetVisibleGroupsTriangleCount)>(0x37, 0x38, this);
	}

	void BSMultiStreamInstanceTriShape::BeginAddingInstances(std::uint32_t a_numFloatsPerInstance)
	{
		REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::BeginAddingInstances)>(0x38, 0x39, this, a_numFloatsPerInstance);
	}

	void BSMultiStreamInstanceTriShape::AddInstances(std::uint32_t a_numFloatsPerInstance, std::uint16_t& a_instanceData)
	{
		REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::AddInstances)>(0x39, 0x3A, this, a_numFloatsPerInstance, a_instanceData);
	}

	void BSMultiStreamInstanceTriShape::DoneAddingInstances(BSTArray<std::uint32_t>& a_instances)
	{
		REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::DoneAddingInstances)>(0x3A, 0x3B, this, a_instances);
	}

	bool BSMultiStreamInstanceTriShape::GetIsAddingInstances()
	{
		return REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::GetIsAddingInstances)>(0x3B, 0x3C, this);
	}

	std::uint32_t BSMultiStreamInstanceTriShape::AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4)
	{
		return REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::AddGroup)>(0x3C, 0x3D, this, a_numInstances, a_instanceData, a_arg3, a_arg4);
	}

	void BSMultiStreamInstanceTriShape::RemoveGroup(std::uint32_t a_numInstance)
	{
		REL::RelocateVirtual<decltype(&BSMultiStreamInstanceTriShape::RemoveGroup)>(0x3D, 0x3E, this, a_numInstance);
	}
#endif
}
