#pragma once

#include "RE/B/BSString.h"
#include "RE/G/GFxValue.h"
#include "RE/G/GPtr.h"

namespace RE
{
	class GFxMovieView;

	struct ItemCard
	{
	public:
		ItemCard(RE::GFxMovieView* a_view)
		{
			view.reset(a_view);
			a_view->CreateObject(&obj);
			//infoText.reserve(2048);
		}

		void SetForm(const RE::TESForm* a_form)
		{
			using func_t = decltype(&ItemCard::SetForm);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51020, 51898) };
			return func(this, a_form);
		}

		void SetItem(const RE::InventoryEntryData* a_item, bool a_ignoreStolen)
		{
			using func_t = decltype(&ItemCard::SetItem);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51019, 51897) };
			return func(this, a_item, a_ignoreStolen);
		}

		TES_HEAP_REDEFINE_NEW();

		// members
		GFxValue           obj;       // 00 - kObject
		BSString           infoText;  // 18
		void*              unk28;     // 28
		std::uint32_t      unk30;     // 30
		std::uint32_t      pad34;     // 34
		GPtr<GFxMovieView> view;      // 38
	};
	static_assert(sizeof(ItemCard) == 0x40);
}
