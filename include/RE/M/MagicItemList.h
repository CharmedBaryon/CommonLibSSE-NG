#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/G/GPtr.h"
#include "RE/M/MagicItemData.h"

namespace RE
{
	class GFxMovieView;
	class TESObjectREFR;

	struct MagicItemList
	{
	public:
		struct Item
		{
		public:
			// members
			MagicItemData data;   // 00
			GFxValue      obj;    // 18
			std::uint64_t unk38;  // 38
			std::uint64_t unk40;  // 40
		};
		static_assert(sizeof(Item) == 0x48);

		Item* GetSelectedItem();
		void  Update();
		void  Update(TESObjectREFR* a_owner);

		// members
		GPtr<GFxMovieView> view;       // 00
		GFxValue           root;       // 08
		GFxValue           entryList;  // 20
		BSTArray<Item*>    items;      // 38
		bool               unk50;      // 50
		std::uint8_t       pad51;      // 51
		std::uint16_t      pad52;      // 52
		std::uint32_t      pad54;      // 54

	private:
		void Update_Impl(TESObjectREFR* a_owner);
	};
	static_assert(sizeof(MagicItemList) == 0x58);
}
