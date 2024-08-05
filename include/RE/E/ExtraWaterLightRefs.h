#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESObjectREFR;

	class ExtraWaterLightRefs : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraWaterLightRefs;
		inline static constexpr auto VTABLE = VTABLE_ExtraWaterLightRefs;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kWaterLightRefs;

		~ExtraWaterLightRefs() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kWaterLightRefs; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return refs != a_rhs->refs; }

		// members
		BSSimpleList<TESObjectREFR*> refs;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraWaterLightRefs) == 0x20);
}
