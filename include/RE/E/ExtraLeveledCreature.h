#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class TESActorBase;

	class ExtraLeveledCreature : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraLeveledCreature;
		inline static constexpr auto VTABLE = VTABLE_ExtraLeveledCreature;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kLeveledCreature;

		~ExtraLeveledCreature() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kLeveledCreature; }

		// members
		TESActorBase* originalBase;  // 10
		TESActorBase* templateBase;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraLeveledCreature) == 0x20);
}
