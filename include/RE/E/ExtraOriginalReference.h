#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraOriginalReference : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraOriginalReference;
		inline static constexpr auto VTABLE = VTABLE_ExtraOriginalReference;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kOriginalReference;

		~ExtraOriginalReference() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kOriginalReference; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return reference != a_rhs->reference; }

		// members
		ObjectRefHandle reference;  // 10
		std::uint32_t   pad14;      // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraOriginalReference) == 0x18);
}
