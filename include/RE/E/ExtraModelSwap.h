#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESForm;
	class TESModel;

	class ExtraModelSwap : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraModelSwap;
		inline static constexpr auto VTABLE = VTABLE_ExtraModelSwap;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kModelSwap;

		~ExtraModelSwap() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kModelSwap; }

		// members
		TESModel* modelSwap;      // 10
		TESForm*  modelSwapForm;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraModelSwap) == 0x20);
}
