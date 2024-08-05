#include "RE/M/MagicCaster.h"

#include "RE/E/Effect.h"
#include "RE/E/EffectSetting.h"
#include "RE/H/hkpCollidable.h"

namespace RE
{
	MagicTarget* MagicCaster::FindPickTarget(NiPoint3& a_targetLocation, TESObjectCELL** a_targetCell, bhkPickData& a_pickData)
	{
		using func_t = decltype(&MagicCaster::FindPickTarget);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33676, 34456) };
		return func(this, a_targetLocation, a_targetCell, a_pickData);
	}

	bool MagicCaster::FindTargets(float a_effectivenessMult, std::uint32_t& a_targetCount, TESBoundObject* a_source, bool a_loadCast, bool a_adjustOnlyHostileEffectiveness)
	{
		using func_t = decltype(&MagicCaster::FindTargets);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33632, 34410) };
		return func(this, a_effectivenessMult, a_targetCount, a_source, a_loadCast, a_adjustOnlyHostileEffectiveness);
	}

	void MagicCaster::FinishCast()
	{
		using func_t = decltype(&MagicCaster::FinishCast);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33657, 34435) };
		return func(this);
	}

	float MagicCaster::GetCurrentSpellCost()
	{
		using func_t = decltype(&MagicCaster::GetCurrentSpellCost);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33426, 34204) };
		return func(this);
	}

	void MagicCaster::InterruptCast(bool a_refund)
	{
		using func_t = decltype(&MagicCaster::InterruptCast);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33630, 34408) };
		return func(this, a_refund);
	}

	void MagicCaster::PlayReleaseSound(MagicItem* a_item)
	{
		using func_t = decltype(&MagicCaster::PlayReleaseSound);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33675, 34448) };
		return func(this, a_item);
	}

	void MagicCaster::SetCurrentSpell(MagicItem* a_item)
	{
		using func_t = decltype(&MagicCaster::SetCurrentSpell);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33644, 34422) };
		return func(this, a_item);
	}

	bool MagicCaster::TestProjectilePlacement(const Effect& a_effect, const bhkPickData& a_pickData)
	{
		if (auto baseEffect = a_effect.baseEffect) {
			if (baseEffect->data.delivery == RE::MagicSystem::Delivery::kTargetLocation) {
				if (baseEffect->data.projectileBase) {
					if (a_pickData.unkC0) {
						return false;
					}

					if (!a_pickData.rayOutput.rootCollidable) {
						return false;
					}

					auto broadPhaseHandle = a_pickData.rayOutput.rootCollidable->broadPhaseHandle;
					if ((broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x01 &&
						(broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x0D &&
						(broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x11) {
						return false;
					}
				}
			}
		}

		return true;
	}

	void MagicCaster::UpdateImpl(float a_delta)
	{
		using func_t = decltype(&MagicCaster::UpdateImpl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33622, 34400) };
		return func(this, a_delta);
	}
}
