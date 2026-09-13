#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaRagdollInstance;
	class hkaRagdollRigidBodyController;
	class hkbCharacter;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	struct hkbWorldFromModelModeData
	{
	public:
		enum class WorldFromModelMode : std::uint8_t
		{
			kUseOld = 0,
			kUseInput = 1,
			kCompute = 2,
			kNone = 3,
			kUseRootBone = 4,
		};

		// members
		std::int16_t       poseMatchingBone0;  // 00
		std::int16_t       poseMatchingBone1;  // 02
		std::int16_t       poseMatchingBone2;  // 04
		WorldFromModelMode mode;               // 06
	};
	static_assert(sizeof(hkbWorldFromModelModeData) == 0x8);

	class hkbRagdollDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRagdollDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbRagdollDriver;

		~hkbRagdollDriver() override;  // 00

		// members - total size (0xD0) and character/ragdoll's offsets are ground-truth
		// confirmed via the dtor's own fallback free-size; the rest is ported from
		// https://github.com/adamhynek/activeragdoll (GPL-3.0)
		float                          ragdollBlendOutTime;                     // 10
		hkbWorldFromModelModeData      worldFromModelModeData;                  // 14
		bool                           autoAddRemoveRagdollToWorld;             // 1C
		bool                           useAsynchronousStepping;                 // 1D
		std::uint16_t                  pad1E;                                   // 1E
		hkQsTransform                  lastWorldFromModel;                      // 20
		hkbWorldFromModelModeData      worldFromModelModeDataInternal;          // 50
		hkArray<std::uint32_t>         reportingWhenKeyframed;                  // 58
		std::uint64_t                  unk68;                                   // 68
		std::uint8_t                   attachedRigidBodyToIndexMap[0x10];       // 70 - hkPointerMap<hkReferencedObject*, uint32_t>, not modeled as a generic type here
		hkbCharacter*                  character;                               // 80
		hkaRagdollInstance*            ragdoll;                                 // 88
		hkQsTransform*                 ragdollPoseWS;                           // 90
		hkaRagdollRigidBodyController* ragdollController;                       // 98
		hkQsTransform*                 ragdollPoseHiResLocal;                   // A0
		hkQsTransform*                 lastPoseLocal;                           // A8
		std::int32_t                   lastNumPoseLocal;                        // B0
		float                          lastFrameRigidBodyOnFraction;            // B4
		float                          lastFramePoweredOnFraction;              // B8
		float                          timeRigidBodyControllerActive;           // BC
		float                          ragdollBlendOutTimeElapsed;              // C0
		bool                           canAddRagdollToWorld;                    // C4
		bool                           shouldReinitializeRagdollController;     // C5
		bool                           isEnabled;                               // C6
		bool                           isPoweredControllerEnabled;              // C7
		bool                           isRigidBodyControllerEnabled;            // C8
		bool                           wasRigidBodyControllerEnabledLastFrame;  // C9
		bool                           ragdollPoseWasUsed;                      // CA
		bool                           allBonesKeyframed;                       // CB
		std::uint32_t                  pad4CC;                                  // CC
	};
	static_assert(offsetof(hkbRagdollDriver, character) == 0x80);
	static_assert(offsetof(hkbRagdollDriver, ragdoll) == 0x88);
	static_assert(sizeof(hkbRagdollDriver) == 0xD0);
}
