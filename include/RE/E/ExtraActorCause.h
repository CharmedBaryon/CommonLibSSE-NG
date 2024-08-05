#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class ActorCause;

	class ExtraActorCause : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraActorCause;
		inline static constexpr auto VTABLE = VTABLE_ExtraActorCause;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kActorCause;

		~ExtraActorCause() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kActorCause; }

		// members
		NiPointer<ActorCause> actorCause;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraActorCause) == 0x18);
}
