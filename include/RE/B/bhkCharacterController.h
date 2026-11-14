#pragma once

#include "RE/B/BSBound.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/bhkWorld.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStepInfo.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkpCharacterContext.h"
#include "RE/H/hkpCharacterControl.h"
#include "RE/H/hkpCharacterState.h"
#include "RE/H/hkpRigidBody.h"
#include "RE/M/MaterialIDs.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class bhkCharacterMoveFinishEvent;
	class bhkICharOrientationController;
	class bhkRigidBody;
	class bhkShape;
	class bhkWorld;
	class CFilter;
	class hkpRigidBody;
	class hkpWorldObject;
	class hkContactPoint;
	class hkTransform;
	class hkVector4;

	struct DamageImpactData;

	enum class CHARACTER_FLAGS
	{
		kNone = 0,
		kQuadruped = 1 << 0,
		kNoGravityOnGround = 1 << 1,
		kTryStep = 1 << 2,
		kNoFriction = 1 << 3,
		kAllowJumpNoContact = 1 << 4,
		kStuckQuad = 1 << 5,
		kAnimAngleMod = 1 << 6,
		kHitDamage = 1 << 7,
		kHitFlags = 1 << 7,
		kSupport = 1 << 8,
		kHasPotentialSupportManifold = 1 << 9,
		kCanJump = 1 << 10,
		kChaseBip = 1 << 11,
		kFollowRagdoll = 1 << 12,
		kJumping = 1 << 13,
		kNotPushable = 1 << 14,
		kFloatLand = 1 << 15,
		kCheckSupport = 1 << 16,
		kNoSim = 1 << 17,
		kFarAway = 1 << 18,
		kOnStilts = 1 << 19,
		kQuickSimulate = 1 << 20,
		kRecordHits = 1 << 21,
		kComputeTiltPreIntegrate = 1 << 22,
		kShouldersUnderWater = 1 << 23,
		kOnStairs = 1 << 24,
		kCanPitch = 1 << 25,
		kCanRoll = 1 << 26,
		kNoCharacterCollisions = 1 << 27,
		kNotPushablePermanent = 1 << 28,
		kPossiblePathObstacle = 1 << 29,
		kShapeRequiresZRot = 1 << 30,
		kSwimAtWaterSurface = 1 << 31,
	};

	class bhkCharacterController :
		public NiRefObject,                                 // 000
		public BSTEventSource<bhkCharacterMoveFinishEvent>  // 010
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharacterController;
		inline static constexpr auto VTABLE = VTABLE_bhkCharacterController;

		~bhkCharacterController() override;  // 00

		// add
		virtual void          GetPositionImpl(hkVector4& a_pos, bool a_applyCenterOffset) const = 0;                    // 02
		virtual void          SetPositionImpl(const hkVector4& a_pos, bool a_applyCenterOffset, bool a_forceWarp) = 0;  // 03
		virtual void          GetTransformImpl(hkTransform& a_tranform) const = 0;                                      // 04
		virtual void          SetTransformImpl(const hkTransform& a_tranform) = 0;                                      // 05
		virtual void          GetLinearVelocityImpl(hkVector4& a_velocity) const = 0;                                   // 06
		virtual void          SetLinearVelocityImpl(const hkVector4& a_velocity) = 0;                                   // 07
		virtual void          GetCollisionFilterInfo(CFilter& a_collisionFilterInfo) const = 0;                         // 08
		virtual void          Unk_09(void) = 0;                                                                         // 09
		virtual void          Unk_0A(void) = 0;                                                                         // 0A
		virtual void          Unk_0B(void) = 0;                                                                         // 0B
		virtual void          Unk_0C(void) = 0;                                                                         // 0C
		virtual void          CheckSupportImpl() = 0;                                                                   // 0D
		virtual void          Unk_0E(void) = 0;                                                                         // 0E
		virtual bhkWorld*     GetHavokWorld() const = 0;                                                                // 0F
		virtual hkpRigidBody* GetRigidBody() const = 0;                                                                 // 10
		virtual float         GetVDBAlpha() const = 0;                                                                  // 11
		virtual void          Unk_12(void) = 0;                                                                         // 12
		virtual void          RotateImpl(hkTransform& a_tranform) = 0;                                                  // 13

		inline void GetPosition(hkVector4& a_pos, bool a_applyCenterOffset) const { return GetPositionImpl(a_pos, a_applyCenterOffset); }

		static bool IsHurtfulBody(hkpRigidBody* a_body)
		{
			using func_t = decltype(&bhkCharacterController::IsHurtfulBody);
			static REL::Relocation<func_t> func{ RELOCATION_ID(76456, 78298) };
			return func(a_body);
		}

		void ProcessHurtfulBody(hkpRigidBody* a_body, const hkContactPoint* a_contactPoint)
		{
			using func_t = decltype(&bhkCharacterController::ProcessHurtfulBody);
			static REL::Relocation<func_t> func{ RELOCATION_ID(76460, 78302) };
			func(this, a_body, a_contactPoint);
		}

		// hkpWorld::LinearCast sweep test against a_pos, validated against the fGoodPosCheckDepth_HAVOK
		// and fGoodPosCastCheckDepth_HAVOK ini settings; applies via the position/velocity setters on success.
		bool TryMoveTo(const hkVector4& a_pos, void* a_arg2, bool a_ignoreDepth)
		{
			using func_t = decltype(&bhkCharacterController::TryMoveTo);
			static REL::Relocation<func_t> func{ RELOCATION_ID(76421, 78260) };
			return func(this, a_pos, a_arg2, a_ignoreDepth);
		}

		// members
		//std::uint64_t						pad068;						// 068
		hkVector4                                              forwardVec;                 // 070
		hkStepInfo                                             stepInfo;                   // 080
		hkVector4                                              outVelocity;                // 090
		hkVector4                                              initialVelocity;            // 0A0
		hkVector4                                              velocityMod;                // 0B0
		hkVector4                                              direction;                  // 0C0
		hkVector4                                              rotCenter;                  // 0D0
		hkVector4                                              pushDelta;                  // 0E0
		hkVector4                                              fakeSupportStart;           // 0F0
		hkVector4                                              up;                         // 100
		hkVector4                                              supportNorm;                // 110
		BSBound                                                collisionBound;             // 120
		BSBound                                                bumperCollisionBound;       // 150
		hkVector4                                              deltaPos;                   // 180
		bhkICharOrientationController*                         orientationCtrl;            // 190
		std::uint64_t                                          pad198;                     // 198
		hkpSurfaceInfo                                         surfaceInfo;                // 1A0
		hkpCharacterContext                                    context;                    // 1E0
		REX::EnumSet<CHARACTER_FLAGS, std::uint32_t>           flags;                      // 218
		hkpCharacterStateType                                  wantState;                  // 218
		float                                                  velocityTime;               // 220
		float                                                  rotMod;                     // 224
		float                                                  rotModTime;                 // 228
		float                                                  calculatePitchTimer;        // 22C
		float                                                  acrobatics;                 // 230
		float                                                  center;                     // 234
		float                                                  waterHeight;                // 238
		float                                                  jumpHeight;                 // 23C
		float                                                  fallStartHeight;            // 240
		float                                                  fallTime;                   // 244
		float                                                  gravity;                    // 248
		float                                                  pitchAngle;                 // 24C
		float                                                  rollAngle;                  // 250
		float                                                  pitchMult;                  // 254
		float                                                  scale;                      // 258
		float                                                  swimFloatHeight;            // 25C
		float                                                  actorHeight;                // 260
		float                                                  speedPct;                   // 264
		std::uint32_t                                          pushCount;                  // 268
		std::uint32_t                                          unk26C;                     // 26C
		std::uint64_t                                          unk270;                     // 270
		std::uint64_t                                          unk278;                     // 278
		NiPointer<bhkShape>                                    shapes[2];                  // 280
		float                                                  radius;                     // 290
		float                                                  height;                     // 294
		float                                                  destRadius;                 // 298
		float                                                  lodDistance;                // 29C
		std::uint32_t                                          size;                       // 2A0
		std::uint32_t                                          priority;                   // 2A4
		std::int32_t                                           supportCount;               // 2A8
		std::uint32_t                                          pad2AC;                     // 2AC
		hkRefPtr<hkpRigidBody>                                 supportBody;                // 2B0
		float                                                  bumpedForce;                // 2B8
		std::uint32_t                                          pad2BC;                     // 2BC
		hkRefPtr<hkpRigidBody>                                 bumpedBody;                 // 2C0
		hkRefPtr<hkpRigidBody>                                 bumpedCharCollisionObject;  // 2C8
		BSTHashMap<NiPointer<bhkRigidBody>, DamageImpactData*> damageImpacts;              // 2D0
		float                                                  zNormal;                    // 300
		MATERIAL_ID                                            surfaceMaterial;            // 304
		std::uint32_t                                          unk308;                     // 308
		float                                                  unk30C;                     // 30C
		float                                                  unk310;                     // 310
		std::uint32_t                                          contactPointsCount;         // 314
		std::uint32_t                                          collisionFilterGroup;       // 318
		bool                                                   unk31C;                     // 31C
		std::uint8_t                                           unk31D;                     // 31D
		std::uint8_t                                           unk31E;                     // 31E
		std::uint8_t                                           unk31F;                     // 31F
		std::uint16_t                                          unk320;                     // 320
		std::uint16_t                                          unk322;                     // 322
		std::uint32_t                                          unk324;                     // 324
		std::uint64_t                                          unk328;                     // 328
	};
	static_assert(sizeof(bhkCharacterController) == 0x330);
}
