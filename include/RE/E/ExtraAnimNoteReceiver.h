#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraAnimNoteReceiver : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraAnimNoteReceiver;
		inline static constexpr auto VTABLE = VTABLE_ExtraAnimNoteReceiver;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kAnimNoteReceiver;

		~ExtraAnimNoteReceiver() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kAnimNoteReceiver; }

		// members
		void* unk10;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraAnimNoteReceiver) == 0x18);
}
