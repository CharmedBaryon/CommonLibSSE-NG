#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSLines;
	class NiAVObject;

	class ExtraEditorRef3DData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraEditorRef3DData;
		inline static constexpr auto VTABLE = VTABLE_ExtraEditorRef3DData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kEditorRef3DData;

		~ExtraEditorRef3DData() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kEditorRef3DData; }

		// members
		NiPointer<NiAVObject> data3D;     // 10
		NiPointer<BSLines>    dataBound;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraEditorRef3DData) == 0x20);
}
