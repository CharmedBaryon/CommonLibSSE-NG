#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class BGSLocationRefType;

	class ExtraLocationRefType : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraLocationRefType;
		inline static constexpr auto VTABLE = VTABLE_ExtraLocationRefType;
		inline static auto           EXTRADATATYPE = ExtraDataType::kLocationRefType;

		~ExtraLocationRefType() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kLocationRefType; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return locRefType != a_rhs->locRefType; }

		// members
		BGSLocationRefType* locRefType;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraLocationRefType) == 0x18);
}
