#pragma once

namespace RE
{
	class bhkRigidBody;
	class bhkSimpleShapePhantom;
	class bhkWorld;
	class HitData;
	class hkpCollidable;
	class hkVector4;
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
		void           LinearCastPhantom(bhkSimpleShapePhantom* a_phantom, bhkWorld* a_world, float* a_startPos, float* a_endPos, float* a_hitResult, TESObjectREFR** a_hitRef, float a_phantomSize);
		bool           CheckCharacterCollision(bhkSimpleShapePhantom* a_phantom, TESObjectREFR* a_character, float* a_pos, float a_casterSize, float a_checkHeight);
	}
}
