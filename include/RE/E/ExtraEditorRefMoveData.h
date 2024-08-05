#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class ExtraEditorRefMoveData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraEditorRefMoveData;
		inline static constexpr auto VTABLE = VTABLE_ExtraEditorRefMoveData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kEditorRefMoveData;

		~ExtraEditorRefMoveData() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kEditorRefMoveData; }

		// members
		NiPoint3      realAngle;     // 10
		NiPoint3      realLocation;  // 1C
		NiPoint3      oldLocation;   // 28
		std::uint32_t pad34;         // 34
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraEditorRefMoveData) == 0x38);
}
