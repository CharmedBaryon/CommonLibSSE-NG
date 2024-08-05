#include "RE/M/MagicItem.h"
#include "RE/E/Effect.h"

namespace RE
{
	float MagicItem::CalculateMagickaCost(Actor* a_caster) const
	{
		return CalculateCost(a_caster);
	}

	float MagicItem::CalculateTotalGoldValue(Actor* a_caster) const
	{
		return CalculateCost(a_caster);
	}

	MagicItemDataCollector MagicItem::CollectData() const
	{
		MagicItemDataCollector ans(this);
		Traverse(ans);
		return ans;
	}

	EffectSetting* MagicItem::GetAVEffect() const
	{
		using func_t = decltype(&MagicItem::GetAVEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11194, 11302) };
		return func(this);
	}

	bool MagicItem::IsValid() const
	{
		using func_t = decltype(&MagicItem::IsValid);
		REL::Relocation<func_t> func{ RELOCATION_ID(11183, 11290) };
		return func(this);
	}

	Effect* MagicItem::GetCostliestEffectItem(MagicSystem::Delivery a_delivery, bool a_positiveArea) const
	{
		using func_t = decltype(&MagicItem::GetCostliestEffectItem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11216, 11335) };
		return func(this, a_delivery, a_positiveArea);
	}

	float MagicItem::CalculateCost(Actor* a_caster) const
	{
		using func_t = decltype(&MagicItem::CalculateTotalGoldValue);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11213, 11321) };
		return func(this, a_caster);
	}

	auto MagicItem::GetData()
		-> Data*
	{
		return GetData2();
	}

	auto MagicItem::GetData() const
		-> const Data*
	{
		return GetData1();
	}

	std::int32_t MagicItem::GetLargestArea() const
	{
		using func_t = decltype(&MagicItem::GetLargestArea);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11219, 11338) };
		return func(this);
	}

	std::uint32_t MagicItem::GetLongestDuration() const
	{
		using func_t = decltype(&MagicItem::GetLongestDuration);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11218, 11337) };
		return func(this);
	}

	bool MagicItem::HasEffect(EffectArchetype a_archetype)
	{
		using func_t = decltype(&MagicItem::HasEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11207, 11315) };
		return func(this, a_archetype);
	}

	bool MagicItem::IsHostile() const
	{
		return hostileCount > 0;
	}

	bool MagicItem::IsPermanent() const
	{
		using func_t = decltype(&MagicItem::IsPermanent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11183, 11290) };
		return func(this);
	}

	Effect* MagicItem::GetEffectIsMatch(EffectSetting* a_base, float a_mag, ::uint32_t a_area, ::uint32_t a_dur, float a_cost)
	{
		auto it = std::find_if(effects.begin(), effects.end(),
			[&](const auto& effect) { return effect && effect->IsMatch(a_base, a_mag, a_area, a_dur, a_cost); });
		return it != effects.end() ? *it : nullptr;
	}

	void MagicItem::Traverse(MagicItemTraversalFunctor& a_visitor) const
	{
		using func_t = decltype(&MagicItem::Traverse);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11222, 11341) };
		return func(this, a_visitor);
	}
}
