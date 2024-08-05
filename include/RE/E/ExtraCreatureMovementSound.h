#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraCreatureMovementSound : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCreatureMovementSound;
		inline static constexpr auto VTABLE = VTABLE_ExtraCreatureMovementSound;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCreatureMovementSound;

		~ExtraCreatureMovementSound() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kCreatureMovementSound; }

		// members
		BSSoundHandle handle;  // 10
		std::uint32_t pad1C;   // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraCreatureMovementSound) == 0x20);
}
