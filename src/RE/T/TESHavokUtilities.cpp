#include "RE/T/TESHavokUtilities.h"

namespace RE
{
	namespace TESHavokUtilities
	{
		void AddExplosionImpulse(NiAVObject* a_obj3D, hkVector4& a_pos, float a_force, const HitData* a_hitData)
		{
			using func_t = decltype(&AddExplosionImpulse);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25468, 26005) };
			return func(a_obj3D, a_pos, a_force, a_hitData);
		}

		TESObjectREFR* FindCollidableRef(const hkpCollidable& a_linkedCollidable)
		{
			using func_t = decltype(&FindCollidableRef);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25466, 26003) };
			return func(a_linkedCollidable);
		}

		NiAVObject* FindCollidableObject(const hkpCollidable& a_linkedCollidable)
		{
			using func_t = decltype(&FindCollidableObject);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15644, 15870) };
			return func(a_linkedCollidable);
		}

		float GetDamageForImpact(float a_mass, float a_speed)
		{
			using func_t = decltype(&GetDamageForImpact);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25478, 26018) };
			return func(a_mass, a_speed);
		}

		void PopTemporaryMass(bhkRigidBody* a_body)
		{
			using func_t = decltype(&PopTemporaryMass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25484, 26024) };
			return func(a_body);
		}

		void PushTemporaryMass(bhkRigidBody* a_body, float a_mass)
		{
			using func_t = decltype(&PushTemporaryMass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25483, 26023) };
			return func(a_body, a_mass);
		}

		float ScaleGameplayImpulseForce(float a_inputForce, bhkRigidBody* a_body, bool a_factorMass)
		{
			using func_t = decltype(&ScaleGameplayImpulseForce);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25467, 26004) };
			return func(a_inputForce, a_body, a_factorMass);
		}
	}
}
