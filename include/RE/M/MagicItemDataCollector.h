#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MagicItemTraversalFunctor.h"

namespace RE
{
	class MagicItem;

	class MagicItemDataCollector : public MagicItemTraversalFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicItemDataCollector;
		inline static constexpr auto VTABLE = VTABLE_MagicItemDataCollector;

		enum class Flags
		{
			kNone = 0,
			kSkipCostiest = 1 << 0,
			kSkipProjectiles = 1 << 1,
			kSkipArea = 1 << 2,
			kOnlyFirstEffect = 1 << 3
		};

		MagicItemDataCollector() = delete;
		MagicItemDataCollector(const MagicItem* a_magicItem);
		~MagicItemDataCollector() override = default;

		// override (MagicItemTraversalFunctor)
		BSContainer::ForEachResult operator()(Effect* a_effect) override;

		// members
		BSTArray<Effect*>                      projectileEffectList;       // 10
		Effect*                                costliestEffect;            // 28
		std::int32_t                           maxCost;                    // 30
		std::uint32_t                          pad34;                      // 34
		Effect*                                largestAreaEffect;          // 38
		float                                  highestArea;                // 40
		stl::enumeration<Flags, std::uint32_t> flags;                      // 44
		bool                                   summonsExtraLargeCreature;  // 48
		std::uint8_t                           pad49;                      // 49
		std::uint16_t                          pad4A;                      // 4A
		std::uint32_t                          pad4C;                      // 4C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MagicItemDataCollector) == 0x50);
}
