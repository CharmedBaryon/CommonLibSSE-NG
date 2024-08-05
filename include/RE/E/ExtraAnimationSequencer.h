#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class BGSAnimationSequencer;

	class ExtraAnimationSequencer : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraAnimationSequencer;
		inline static constexpr auto VTABLE = VTABLE_ExtraAnimationSequencer;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kAnimationSequencer;

		~ExtraAnimationSequencer() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kAnimationSequencer; }

		// members
		BGSAnimationSequencer* sequencer;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraAnimationSequencer) == 0x18);
}
