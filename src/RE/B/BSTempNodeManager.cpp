#include "RE/B/BSTempNodeManager.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSTempNodeManager::UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&BSTempNodeManager::UpdateDownwardPass)>(0x2C, 0x2D, this, a_data, a_arg2);
	}

	void BSTempNodeManager::UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&BSTempNodeManager::UpdateSelectedDownwardPass)>(0x2D, 0x2E, this, a_data, a_arg2);
	}

	void BSTempNodeManager::UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&BSTempNodeManager::UpdateRigidDownwardPass)>(0x2E, 0x2F, this, a_data, a_arg2);
	}
#endif

	void BSTempNodeManager::UpdateTempNodeTimers(float a_elapsedTime)
	{
		using func_t = decltype(&BSTempNodeManager::UpdateTempNodeTimers);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74387, 76110) };
		return func(this, a_elapsedTime);
	}
}
