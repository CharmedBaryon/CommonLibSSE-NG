#pragma once

namespace RE
{
	class HitData;
	class hkVector4;
	class bhkRigidBody;
	class hkpCollidable;
	class NiAVObject;
	class TESObjectREFR;

	namespace TESHavokUtilities
	{
		void           AddExplosionImpulse(NiAVObject* a_obj3D, hkVector4& a_pos, float a_force, const HitData* a_hitData);
		TESObjectREFR* FindCollidableRef(const hkpCollidable& a_linkedCollidable);
		NiAVObject*    FindCollidableObject(const hkpCollidable& a_linkedCollidable);
		float          GetDamageForImpact(float a_mass, float a_speed);
		void           PopTemporaryMass(bhkRigidBody* a_body);
		void           PushTemporaryMass(bhkRigidBody* a_body, float a_mass);
		float          ScaleGameplayImpulseForce(float a_inputForce, bhkRigidBody* a_body, bool a_factorMass);
	}
}
