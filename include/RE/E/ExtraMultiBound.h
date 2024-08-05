#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiBound;

	class ExtraMultiBound : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraMultiBound;
		inline static constexpr auto VTABLE = VTABLE_ExtraMultiBound;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kMultiBound;

		~ExtraMultiBound() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kMultiBound; }

		// members
		NiPointer<BSMultiBound> bound;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraMultiBound) == 0x18);
}
