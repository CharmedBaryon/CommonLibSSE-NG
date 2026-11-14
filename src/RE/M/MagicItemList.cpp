#include "RE/M/MagicItemList.h"

#include "RE/P/PlayerCharacter.h"

namespace RE
{
	MagicItemList::Item* MagicItemList::GetSelectedItem()
	{
		if (unk50) {
			return nullptr;
		}

		GFxValue selectedIndex;
		auto     success = root.GetMember("selectedIndex", &selectedIndex);
		if (!success || !selectedIndex.IsNumber()) {
			return nullptr;
		}

		auto idx = static_cast<std::int32_t>(selectedIndex.GetNumber());
		if (idx < 0 || static_cast<std::size_t>(idx) >= items.size()) {
			return nullptr;
		}

		return items[idx];
	}

	void MagicItemList::Update()
	{
		auto player = PlayerCharacter::GetSingleton();
		Update(player);
	}

	void MagicItemList::Update(TESObjectREFR* a_owner)
	{
		Update_Impl(a_owner);
	}

	void MagicItemList::Update_Impl(TESObjectREFR* a_owner)
	{
		using func_t = decltype(&MagicItemList::Update_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51223, 52098) };
		return func(this, a_owner);
	}
}
