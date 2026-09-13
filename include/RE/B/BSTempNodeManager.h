#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class BSTempNodeManager : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTempNodeManager;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTempNodeManager;
		inline static constexpr auto VTABLE = VTABLE_BSTempNodeManager;

		~BSTempNodeManager() override;  // 00

		// override (NiNode)
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;     // 2E
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2D
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2E
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;     // 2F
#else
		// VR shifts these slots by +1 (NiAVObject::ApplyLocalTransformToWorld is inserted ahead of
		// them); resolve the real per-runtime slot via RelocateVirtual instead of a fixed ordinal.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);          // SE/AE 2C, VR 2D
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);  // SE/AE 2D, VR 2E
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);     // SE/AE 2E, VR 2F
#endif

		// add

		// Per-frame update: decrements each attached BSTempNode child's remaining lifetime by
		// elapsed time, detaching any that reach zero.
		void UpdateTempNodeTimers(float a_elapsedTime);

	private:
		std::uint64_t unk128;  // 128 / 150 - not yet reverse engineered
	};
	STATIC_ASSERT_SIZE(BSTempNodeManager, 0x130, 0x130, 0x158, SIZE_UNDEFINED, 0x130);
}
