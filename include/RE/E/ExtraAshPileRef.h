#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraAshPileRef : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraAshPileRef;
		inline static constexpr auto VTABLE = VTABLE_ExtraAshPileRef;
		inline static auto           EXTRADATATYPE = ExtraDataType::kAshPileRef;

		ExtraAshPileRef();
		explicit ExtraAshPileRef(ObjectRefHandle a_ashPileRef);
		~ExtraAshPileRef() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kAshPileRef; }

		// members
		ObjectRefHandle ashPileRef;  // 10
		std::uint32_t   pad14;       // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraAshPileRef) == 0x18);
}
