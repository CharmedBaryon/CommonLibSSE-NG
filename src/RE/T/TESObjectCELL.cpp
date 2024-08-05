#include "RE/T/TESObjectCELL.h"

#include "RE/B/BGSEncounterZone.h"
#include "RE/E/ExtraNorthRotation.h"
#include "RE/N/NiMath.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESRegionList.h"
#include "RE/T/TESWorldSpace.h"

namespace RE
{
	void TESObjectCELL::ForEachReference(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		auto&           runtimeData = GetRuntimeData();
		BSSpinLockGuard locker(runtimeData.spinLock);
		for (const auto& ref : runtimeData.references) {
			if (ref && a_callback(ref.get()) == BSContainer::ForEachResult::kStop) {
				break;
			}
		}
	}

	void TESObjectCELL::ForEachReferenceInRange(const NiPoint3& a_origin, float a_radius, std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		const float squaredRadius = a_radius * a_radius;
		ForEachReference([&](TESObjectREFR* ref) {
			const auto distance = a_origin.GetSquaredDistance(ref->GetPosition());
			return distance <= squaredRadius ?
			           a_callback(ref) :
			           BSContainer::ForEachResult::kContinue;
		});
	}

	TESNPC* TESObjectCELL::GetActorOwner()
	{
		auto owner = GetOwner();
		return owner && owner->Is(FormType::NPC) ? static_cast<TESNPC*>(owner) : nullptr;
	}

	bhkWorld* TESObjectCELL::GetbhkWorld() const
	{
		using func_t = decltype(&TESObjectCELL::GetbhkWorld);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18536, 18995) };
		return func(this);
	}

	EXTERIOR_DATA* TESObjectCELL::GetCoordinates()
	{
		return IsExteriorCell() ? GetRuntimeData().cellData.exterior : nullptr;
	}

	TESFaction* TESObjectCELL::GetFactionOwner()
	{
		auto owner = GetOwner();
		return owner && owner->Is(FormType::Faction) ? static_cast<TESFaction*>(owner) : nullptr;
	}

	INTERIOR_DATA* TESObjectCELL::GetLighting()
	{
		return IsInteriorCell() ? GetRuntimeData().cellData.interior : nullptr;
	}

	BGSLocation* TESObjectCELL::GetLocation() const
	{
		using func_t = decltype(&TESObjectCELL::GetLocation);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18474, 18905) };
		return func(this);
	}

	float TESObjectCELL::GetNorthRotation()
	{
		if (IsExteriorCell()) {
			return GetRuntimeData().worldSpace->northRotation;
		} else {
			auto xNorth = extraList.GetByType<ExtraNorthRotation>();
			return xNorth ? xNorth->northRot : static_cast<float>(0.0);
		}
	}

	TESForm* TESObjectCELL::GetOwner()
	{
		auto& runtimeData = GetRuntimeData();
		auto  owner = extraList.GetOwner();
		if (owner) {
			return owner;
		}

		BGSEncounterZone* zone = nullptr;
		if (runtimeData.loadedData) {
			zone = runtimeData.loadedData->encounterZone;
		} else {
			zone = extraList.GetEncounterZone();
			if (!zone && IsExteriorCell()) {
				zone = runtimeData.worldSpace ? runtimeData.worldSpace->encounterZone : nullptr;
			}
		}

		return zone ? zone->data.zoneOwner : nullptr;
	}

	float TESObjectCELL::GetExteriorWaterHeight() const
	{
		auto& runtimeData = GetRuntimeData();
		if (cellFlags.none(Flag::kHasWater) || cellFlags.any(Flag::kIsInteriorCell)) {
			return -NI_INFINITY;
		}

		if (runtimeData.waterHeight < 2147483600.0f) {
			return runtimeData.waterHeight;
		}

		return runtimeData.worldSpace ? runtimeData.worldSpace->GetDefaultWaterHeight() : -NI_INFINITY;
	}

	TESRegionList* TESObjectCELL::GetRegionList(bool a_createIfMissing)
	{
		using func_t = decltype(&TESObjectCELL::GetRegionList);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18540, 18999) };
		return func(this, a_createIfMissing);
	}

	bool TESObjectCELL::GetWaterHeight(const NiPoint3& a_pos, float& a_waterHeight)
	{
		using func_t = decltype(&TESObjectCELL::GetWaterHeight);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18543, 19002) };
		return func(this, a_pos, a_waterHeight);
	}

	bool TESObjectCELL::IsAttached() const
	{
		return cellState == CellState::kAttached;
	}

	bool TESObjectCELL::IsExteriorCell() const
	{
		return !IsInteriorCell();
	}

	bool TESObjectCELL::IsInteriorCell() const
	{
		return cellFlags.all(Flag::kIsInteriorCell);
	}

	void TESObjectCELL::SetActorOwner(TESNPC* a_owner)
	{
		SetOwner(a_owner);
	}

	void TESObjectCELL::SetFactionOwner(TESFaction* a_owner)
	{
		SetOwner(a_owner);
	}

	void TESObjectCELL::SetFogColor(Color a_near, Color a_far)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogColorNear = a_near;
				lighting->fogColorFar = a_far;
			}
		}
	}

	void TESObjectCELL::SetFogPlanes(float a_near, float a_far)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogNear = a_near;
				lighting->fogFar = a_far;
			}
		}
	}

	void TESObjectCELL::SetFogPower(float a_power)
	{
		if (!UsesSkyLighting()) {
			auto lighting = GetLighting();
			if (lighting) {
				lighting->fogPower = a_power;
			}
		}
	}

	void TESObjectCELL::SetHandChanged(bool a_changed)
	{
		if (a_changed) {
			cellFlags.set(Flag::kHandChanged);
		} else {
			cellFlags.reset(Flag::kHandChanged);
		}
		AddChange(ChangeFlags::kFlags);
	}

	void TESObjectCELL::SetOwner(TESForm* a_owner)
	{
		extraList.SetOwner(a_owner);
		AddChange(ChangeFlags::kOwnership);
	}

	void TESObjectCELL::SetPublic(bool a_public)
	{
		if (a_public) {
			cellFlags.set(Flag::kPublicArea);
		} else {
			cellFlags.reset(Flag::kPublicArea);
		}
		AddChange(ChangeFlags::kFlags);
	}

	bool TESObjectCELL::UsesSkyLighting() const
	{
		return cellFlags.all(Flag::kUseSkyLighting);
	}
}
