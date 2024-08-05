#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSOutfit : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSOutfit;
		inline static constexpr auto VTABLE = VTABLE_BGSOutfit;
		inline static constexpr auto FORMTYPE = FormType::Outfit;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSOutfit() override;  // 00

		// override (TESForm)
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		void ForEachItem(std::function<BSContainer::ForEachResult(TESForm*)> a_callback) const
		{
			for (auto& item : outfitItems) {
				if (item && a_callback(item) == BSContainer::ForEachResult::kStop) {
					return;
				}
			}
		}

		// members
		BSTArray<TESForm*> outfitItems;  // 20 - INAM
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSOutfit) == 0x38);
}
