#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkContactPoint.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStepInfo.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkpCharacterControl.h"
#include "RE/H/hkpEntityListener.h"
#include "RE/H/hkpWorldPostSimulationListener.h"
#include "REX/REX/EnumSet.h"

namespace RE
{
	class hkpRigidBody;
	class hkpShape;
	class hkpCdPointCollector;
	class hkpCharacterRigidBodyListener;
	class hkpSimpleConstraintContactMgr;

	class hkpCharacterRigidBody :
		public hkReferencedObject,             // 00
		public hkpEntityListener,              // 10
		public hkpWorldPostSimulationListener  // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpCharacterRigidBody;
		inline static constexpr auto VTABLE = VTABLE_hkpCharacterRigidBody;

		struct SupportInfo
		{
			hkContactPoint point;
			hkpRigidBody*  rigidBody;
		};

		struct VertPointInfo
		{
			hkContactPoint                 vertPoint;
			hkpSimpleConstraintContactMgr* mgr;
		};

		~hkpCharacterRigidBody() override;  // 00

		// override (hkpEntityListener)
		void EntityAddedCallback(hkpEntity* a_entity) override;    // 01
		void EntityRemovedCallback(hkpEntity* a_entity) override;  // 02

		// override (hkpWorldPostSimulationListener)
		void PostSimulationCallback(hkpWorld* a_world) override;  // 01

		// add
		void                                   SetLinearVelocity(const hkVector4& a_newVel, float a_timestep);
		virtual void                           CheckSupport(const hkStepInfo& a_stepInfo, hkpSurfaceInfo& a_ground);                                                   // 03
		virtual hkpSurfaceInfo::SupportedState GetSupportInfo(const hkStepInfo& a_stepInfo, hkArray<SupportInfo>& a_supportInfo) const;                                // 04
		virtual void                           GetGround(const hkArray<SupportInfo>& a_supportInfo, bool a_useDynamicBodyVelocities, hkpSurfaceInfo& a_ground) const;  // 05

		// members
		hkpRigidBody*                  character;                    // 20
		hkpCharacterRigidBodyListener* listener;                     // 28
		hkVector4                      up;                           // 30
		float                          unweldingHeightOffsetFactor;  // 40
		float                          maxSlopeCosine;               // 44
		float                          maxSpeedForSimplexSolver;     // 48
		float                          supportDistance;              // 4C
		float                          hardSupportDistance;          // 50
		hkVector4                      acceleration;                 // 60
		float                          maxForce;                     // 70
		hkArray<VertPointInfo>         verticalContactPoints;        // 78
	};
	static_assert(sizeof(hkpCharacterRigidBody) == 0x90);

}
