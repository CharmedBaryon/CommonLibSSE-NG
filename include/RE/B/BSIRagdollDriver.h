#pragma once

#include "RE/H/hkpMotion.h"

namespace RE
{
	class bhkWorld;

	class BSIRagdollDriver
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSIRagdollDriver;
		inline static constexpr auto VTABLE = VTABLE_BSIRagdollDriver;

		virtual ~BSIRagdollDriver();  // 00

		virtual bool HasRagdoll() = 0;                                       // 01
		virtual bool AddRagdollToWorld() = 0;                                // 02
		virtual bool RemoveRagdollFromWorld() = 0;                           // 03
		virtual void SetWorld(bhkWorld* a_world) = 0;                        // 04 - { world = a_world; }
		virtual void ResetRagdoll(void) = 0;                                 // 05
		virtual void Unk_06(void) = 0;                                       // 06
		virtual void SetRagdollConstraintsFromBhkConstraints() = 0;          // 07
		virtual void SetMotionType(hkpMotion::MotionType a_motionType) = 0;  // 08
		virtual void Unk_09(void) = 0;                                       // 09
		virtual void ToggleSyncOnUpdate(bool a_disable) = 0;                 // 0A
		virtual void Unk_0B(void) = 0;                                       // 0B
		virtual void ToggleConstraints(bool a_disable) = 0;                  // 0C
		virtual void Unk_0D(void) = 0;                                       // 0D
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSIRagdollDriver) == 0x8);
}
