#pragma once

#include "RE/M/MemoryManager.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class EffectSetting;

	struct Effect
	{
	public:
		struct EffectItem  // EFIT
		{
		public:
			EffectItem();
			~EffectItem() = default;

			// members
			float         magnitude;  // 0
			std::uint32_t area;       // 4
			std::uint32_t duration;   // 8
		};
		static_assert(sizeof(EffectItem) == 0xC);

		Effect();
		~Effect() = default;

		TES_HEAP_REDEFINE_NEW();

		void          Copy(const Effect* a_other);
		float         GetMagnitude() const;
		std::uint32_t GetArea() const;
		std::uint32_t GetDuration() const;
		bool          IsHostile() const;
		bool          IsMatch(EffectSetting* a_base, float a_mag, std::uint32_t a_area, std::uint32_t a_dur, float a_cost);
		void          SetDuration(std::int32_t a_duration);
		void          SetMagnitude(float a_magnitude);

		// members
		EffectItem     effectItem;  // 00 - EFIT
		std::uint32_t  pad0C;       // 0C
		EffectSetting* baseEffect;  // 10 - EFID
		float          cost;        // 18
		std::uint32_t  pad1C;       // 1C
		TESCondition   conditions;  // 20 - CTDA
	};
	static_assert(sizeof(Effect) == 0x28);
}
