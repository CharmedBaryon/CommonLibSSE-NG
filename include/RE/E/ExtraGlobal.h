#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESGlobal;

	class ExtraGlobal : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraGlobal;
		inline static constexpr auto VTABLE = VTABLE_ExtraGlobal;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kGlobal;

		~ExtraGlobal() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kGlobal; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return global != a_rhs->global; }

		// members
		TESGlobal* global;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraGlobal) == 0x18);
}
