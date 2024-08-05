#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraReflectedRefs : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraReflectedRefs;
		inline static constexpr auto VTABLE = VTABLE_ExtraReflectedRefs;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kReflectedRefs;

		~ExtraReflectedRefs() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kReflectedRefs; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02

		// members
		BSTArray<ObjectRefHandle> refs;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraReflectedRefs) == 0x28);
}
