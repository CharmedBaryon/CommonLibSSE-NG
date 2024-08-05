#include "RE/P/Projectile.h"
#include "RE/A/AIProcess.h"
#include "RE/E/Effect.h"
#include "RE/F/FormTraits.h"
#include "RE/M/MagicCaster.h"

using namespace REL;

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	bool Projectile::IsMissileProjectile()
	{
		return RelocateVirtual<bool(Projectile*)>(0xA2, 0xA3, this);
	}

	bool Projectile::IsGrenadeProjectile()
	{
		return RelocateVirtual<bool(Projectile*)>(0xA3, 0xA4, this);
	}

	bool Projectile::IsFlameProjectile()
	{
		return RelocateVirtual<bool(Projectile*)>(0xA4, 0xA5, this);
	}

	bool Projectile::IsBeamProjectile()
	{
		return RelocateVirtual<bool(Projectile*)>(0xA5, 0xA6, this);
	}

	void Projectile::Unk_A6()
	{
		RelocateVirtual<void(Projectile*)>(0xA6, 0xA7, this);
	}

	bool Projectile::IsBarrierProjectile()
	{
		return RelocateVirtual<bool(Projectile*)>(0xA7, 0xA8, this);
	}

	void Projectile::OnKill()
	{
		RelocateVirtual<void(Projectile*)>(0xA8, 0xA9, this);
	}

	void Projectile::Process3D()
	{
		RelocateVirtual<void(Projectile*)>(0xA9, 0xAA, this);
	}

	void Projectile::PostLoad3D(NiAVObject* a_root)
	{
		RelocateVirtual<void(Projectile*, NiAVObject*)>(0xAA, 0xAB, this, a_root);
	}

	void Projectile::UpdateImpl(float a_delta)
	{
		RelocateVirtual<decltype(&Projectile::UpdateImpl)>(0xAB, 0xAC, this, a_delta);
	}

	bool Projectile::ProcessImpacts()
	{
		return RelocateVirtual<bool(Projectile*)>(0xAC, 0xAD, this);
	}

	void Projectile::Update3D()
	{
		RelocateVirtual<void(Projectile*)>(0xAD, 0xAE, this);
	}

	void Projectile::Unk_AE()
	{
		RelocateVirtual<void(Projectile*)>(0xAE, 0xAF, this);
	}

	float Projectile::GetPowerSpeedMult() const
	{
		return RelocateVirtual<float(const Projectile*)>(0xAF, 0xB0, this);
	}

	float Projectile::GetWeaponSpeedMult() const
	{
		return RelocateVirtual<float(const Projectile*)>(0xB0, 0xB1, this);
	}

	bool Projectile::GetStopMainSoundAfterImpact()
	{
		return RelocateVirtual<bool(Projectile*)>(0xB1, 0xB2, this);
	}

	void Projectile::ReportHavokDeactivation()
	{
		RelocateVirtual<void(Projectile*)>(0xB2, 0xB3, this);
	}

	bool Projectile::TurnOff(Actor* a_owner, bool a_noDeactivateSound)
	{
		return RelocateVirtual<bool(Projectile*, Actor*, bool)>(0xB3, 0xB4, this, a_owner, a_noDeactivateSound);
	}

	bool Projectile::IsPermanent() const
	{
		return RelocateVirtual<decltype(&Projectile::IsPermanent)>(0xB4, 0xB5, this);
	}

	float Projectile::GetGravity()
	{
		return RelocateVirtual<float(Projectile*)>(0xB5, 0xB6, this);
	}

	void Projectile::CleanUpPointersOnDisable()
	{
		RelocateVirtual<void(Projectile*)>(0xB6, 0xB7, this);
	}

	bool Projectile::RunTargetPick()
	{
		return RelocateVirtual<bool(Projectile*)>(0xB7, 0xB8, this);
	}

	bool Projectile::GetKillOnCollision()
	{
		return RelocateVirtual<bool(Projectile*)>(0xB8, 0xB9, this);
	}

	bool Projectile::ShouldBeLimited()
	{
		return RelocateVirtual<bool(Projectile*)>(0xB9, 0xBA, this);
	}

	bool Projectile::TargetsWholeBody()
	{
		return RelocateVirtual<bool(Projectile*)>(0xBA, 0xBB, this);
	}

	std::uint32_t Projectile::GetCollisionGroup()
	{
		return RelocateVirtual<std::uint32_t(Projectile*)>(0xBB, 0xBC, this);
	}

	bhkShape* Projectile::GetCollisionShape()
	{
		return RelocateVirtual<bhkShape*(Projectile*)>(0xBC, 0xBD, this);
	}

	void Projectile::AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7)
	{
		RelocateVirtual<decltype(&Projectile::AddImpact)>(0xBD, 0xBE, this, a_ref, a_targetLoc, a_velocity, a_collidable, a_arg6, a_arg7);
	}

	bool Projectile::HandleHits(hkpCollidable* a_collidable)
	{
		return RelocateVirtual<bool(Projectile*, hkpCollidable*)>(0xBE, 0xBF, this, a_collidable);
	}

	void Projectile::OnTriggerEnter()
	{
		RelocateVirtual<void(Projectile*)>(0xBF, 0xC0, this);
	}

	void Projectile::Handle3DLoaded()
	{
		RelocateVirtual<decltype(&Projectile::Handle3DLoaded)>(0xC0, 0xC1, this);
	}

	bool Projectile::ShouldUseDesiredTarget()
	{
		return RelocateVirtual<bool(Projectile*)>(0xC1, 0xC2, this);
	}
#endif

	Projectile::Manager* Projectile::Manager::GetSingleton()
	{
		REL::Relocation<Manager**> singleton{ RELOCATION_ID(514313, 400473) };
		return *singleton;
	}

	Projectile::LaunchData::LaunchData(BGSProjectile* a_bproj, Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles) :
		origin(a_origin),
		contactNormal(NiPoint3()),
		projectileBase(a_bproj),
		shooter(a_shooter),
		combatController(a_shooter->GetActorRuntimeData().combatController),
		weaponSource(nullptr),
		ammoSource(nullptr),
		angleZ(a_angles.z),
		angleX(a_angles.x),
		unk50(nullptr),
		desiredTarget(nullptr),
		unk60(0.0f),
		unk64(0.0f),
		parentCell(a_shooter->GetParentCell()),
		spell(nullptr),
		castingSource(MagicSystem::CastingSource::kOther),
		pad7C(0),
		enchantItem(nullptr),
		poison(nullptr),
		area(0),
		power(1.0f),
		scale(1.0f),
		alwaysHit(false),
		noDamageOutsideCombat(false),
		autoAim(true),
		chainShatter(false),
		useOrigin(false),
		deferInitialization(false),
		forceConeOfFire(false)
	{
		stl::emplace_vtable(this);
	}

	Projectile::LaunchData::LaunchData(Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles, MagicItem* a_spell) :
		LaunchData(a_spell->GetAVEffect()->data.projectileBase, a_shooter, a_origin, a_angles)
	{
		const auto costliestEffect = a_spell->GetCostliestEffectItem();

		spell = a_spell;
		area = costliestEffect ? costliestEffect->GetArea() : 0;
		useOrigin = true;
		autoAim = false;
	}

	Projectile::LaunchData::LaunchData(Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles, TESAmmo* a_ammo, TESObjectWEAP* a_weap) :
		LaunchData(a_ammo->GetRuntimeData().data.projectile, a_shooter, a_origin, a_angles)
	{
		weaponSource = a_weap;
		ammoSource = a_ammo;
		useOrigin = true;
		autoAim = false;
	}

	BGSProjectile* Projectile::GetProjectileBase() const
	{
		auto obj = GetObjectReference();
		return obj ? obj->As<BGSProjectile>() : nullptr;
	}

	float Projectile::GetHeight() const
	{
		if (const auto baseProjectile = GetProjectileBase()) {
			return baseProjectile->data.collisionRadius * 2;
		}
		return 0.0f;
	}

	float Projectile::GetSpeed() const
	{
		if (const auto baseProjectile = GetProjectileBase()) {
			return baseProjectile->data.speed * GetPowerSpeedMult() * GetWeaponSpeedMult() * GetProjectileRuntimeData().speedMult;
		}
		return 0.0f;
	}

	ProjectileHandle* Projectile::Launch(ProjectileHandle* a_result, LaunchData& a_data) noexcept
	{
		using func_t = decltype(&Projectile::Launch);
		static REL::Relocation<func_t> func{ RELOCATION_ID(42928, 44108) };
		return func(a_result, a_data);
	}

	ProjectileHandle* Projectile::LaunchSpell(ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, const NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept
	{
		LaunchData launchData(a_shooter, a_origin, a_angles, a_spell);
		return Launch(a_result, launchData);
	}

	ProjectileHandle* Projectile::LaunchSpell(ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, MagicSystem::CastingSource a_source) noexcept
	{
		const auto caster = a_shooter->GetMagicCaster(a_source);
		if (!caster) {
			return a_result;
		}

		NiPoint3 origin;
		if (const auto node = caster->GetMagicNode()) {
			origin = node->world.translate;
		} else {
			origin = a_shooter->GetPosition();
			const auto bound_max = a_shooter->GetBoundMax();
			const auto bound_min = a_shooter->GetBoundMin();
			origin.z += (bound_max.z - bound_min.z) * 0.7f;
		}

		ProjectileRot angles{ a_shooter->GetAimAngle(), a_shooter->GetAimHeading() };

		return LaunchSpell(a_result, a_shooter, a_spell, origin, angles);
	}

	ProjectileHandle* Projectile::LaunchArrow(ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap, const NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept
	{
		LaunchData launchData(a_shooter, a_origin, a_angles, a_ammo, a_weap);
		return Launch(a_result, launchData);
	}

	ProjectileHandle* Projectile::LaunchArrow(ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap) noexcept
	{
		NiAVObject* fireNode;

		if (const auto currentProcess = a_shooter->GetActorRuntimeData().currentProcess) {
			const auto& biped = a_shooter->GetBiped2();
			fireNode = a_weap->IsCrossbow() ? currentProcess->GetMagicNode(biped) : currentProcess->GetWeaponNode(biped);
		} else {
			fireNode = a_weap->GetFireNode(a_shooter->IsPlayerRef() ? a_shooter->GetCurrent3D() : a_shooter->Get3D2());
		}

		NiPoint3      origin;
		ProjectileRot angles{};

		if (fireNode) {
			origin = fireNode->world.translate;
			a_shooter->Unk_A0(fireNode, angles.x, angles.z, origin);
		} else {
			origin = a_shooter->GetPosition();
			origin.z += 96.0f;

			angles.x = a_shooter->GetAimAngle();
			angles.z = a_shooter->GetAimHeading();
		}

		return LaunchArrow(a_result, a_shooter, a_ammo, a_weap, origin, angles);
	}
}
