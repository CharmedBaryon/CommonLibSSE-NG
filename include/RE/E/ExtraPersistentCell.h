#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESObjectCELL;

	class ExtraPersistentCell : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraPersistentCell;
		inline static constexpr auto VTABLE = VTABLE_ExtraPersistentCell;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kPersistentCell;

		~ExtraPersistentCell() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kPersistentCell; }

		// members
		TESObjectCELL* persistentCell;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraPersistentCell) == 0x18);
}
