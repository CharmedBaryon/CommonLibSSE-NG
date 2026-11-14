#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkpConstraintData.h"
#include "RE/H/hkpConstraintInstance.h"

namespace RE
{
	class hkpConstraintData;
	class hkpRigidBody;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkConstraintCinfo;

		virtual ~hkConstraintCinfo();  // 00

		// add
		virtual void CreateConstraintData();  // 01

		// members
		hkRefPtr<hkpConstraintData>                                           constraintData = nullptr;  // 08
		REX::EnumSet<hkpConstraintInstance::ConstraintPriority, std::uint8_t> priority =
			hkpConstraintInstance::ConstraintPriority::kInvalid;  // 10
		std::uint8_t  pad11[3] = { 0 };                           // 11
		std::uint32_t pad14 = 0;                                  // 14
		hkpRigidBody* rigidBodyA = nullptr;                       // 18
		hkpRigidBody* rigidBodyB = nullptr;                       // 20
	};
}
