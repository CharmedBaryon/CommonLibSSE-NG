#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/H/hkRefPtr.h"

namespace RE
{
	namespace BSCurrent
	{
		struct ActionArray
		{
			__m128*       buffer;         // 00
			std::uint32_t bufferSize;     // 08
			std::uint32_t effectiveSize;  // 0C
			std::uint32_t count;          // 10
			std::uint32_t pad14;          // 14
		};
		static_assert(sizeof(ActionArray) == 0x18);
	}

	class hkReferencedObject;

	class ExtraWaterData : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraWaterData;
		inline static constexpr auto VTABLE = VTABLE_ExtraWaterData;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kWaterData;

		~ExtraWaterData() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kWaterData; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02

		// members
		std::uint64_t                unk10;         // 10
		hkRefPtr<hkReferencedObject> unk18;         // 18
		BSCurrent::ActionArray*      currentArray;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraWaterData) == 0x28);
}
