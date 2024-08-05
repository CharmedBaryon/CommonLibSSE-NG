#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	struct hkConstraintInternal;
	class hkpConstraintData;
	class hkpConstraintOwner;
	struct hkpModifierConstraintAtom;

	class hkpConstraintInstance : public hkReferencedObject
	{
	public:
		enum class ConstraintPriority
		{
			kInvalid,
			kPSI,
			kSimplifiedTOI_Unused,
			kTOI,
			kTOIHigher,
			kTOIForced,

			kTotal
		};

		enum class OnDestructionRemapInfo
		{
			kRemap = 0,
			kRemove = 1,
			kResetRemove = 2
		};

		inline static constexpr auto RTTI = RTTI_hkpConstraintInstance;
		inline static constexpr auto VTABLE = VTABLE_hkpConstraintInstance;

		~hkpConstraintInstance() override;  // 00

		inline hkpRigidBody* GetRigidBodyA() const
		{
			return reinterpret_cast<hkpRigidBody*>(entities[0]);
		}

		inline hkpRigidBody* GetRigidBodyB() const
		{
			return reinterpret_cast<hkpRigidBody*>(entities[1]);
		}

		// members
		hkpConstraintOwner*                                    owner;                 // 10
		hkpConstraintData*                                     data;                  // 18
		hkpModifierConstraintAtom*                             constraintModifiers;   // 20
		hkpEntity*                                             entities[2];           // 28
		stl::enumeration<ConstraintPriority, std::uint8_t>     priority;              // 38
		bool                                                   wantRuntime;           // 39
		stl::enumeration<OnDestructionRemapInfo, std::uint8_t> destructionRemapInfo;  // 3A
		hkSmallArray<hkpConstraintListener*>                   listeners;             // 40
		hkStringPtr                                            name;                  // 50
		uint64_t                                               userData;              // 58
		hkConstraintInternal*                                  internal;              // 60
		uint32_t                                               uid;                   // 68
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpConstraintInstance) == 0x70);

	struct hkConstraintInternal
	{
		hkpConstraintInstance*                                                    constraint;          // 00
		hkpEntity*                                                                entities[2];         // 08
		hkpConstraintAtom*                                                        atoms;               // 18
		uint16_t                                                                  atomsSize;           // 20
		uint8_t                                                                   callbackRequest;     // 22
		stl::enumeration<hkpConstraintInstance::ConstraintPriority, std::uint8_t> priority;            // 23
		uint16_t                                                                  sizeOfSchemas;       // 24
		uint16_t                                                                  numSolverResults;    // 26
		uint16_t                                                                  numSolverElemTemps;  // 28
		uint8_t                                                                   whoIsMaster;         // 2A
		bool                                                                      isNormalType;        // 2B
		hkpConstraintRuntime*                                                     runtime;             // 30
		uint16_t                                                                  runtimeSize;         // 38
		hkObjectIndex                                                             slaveIndex;          // 3A
	};
	static_assert(sizeof(hkConstraintInternal) == 0x40);
}
