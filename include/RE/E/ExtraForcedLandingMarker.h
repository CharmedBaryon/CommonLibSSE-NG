#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraForcedLandingMarker : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraForcedLandingMarker;
		inline static constexpr auto VTABLE = VTABLE_ExtraForcedLandingMarker;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kForcedLandingMarker;

		~ExtraForcedLandingMarker() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kForcedLandingMarker; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return landingMarker != a_rhs->landingMarker; }

		// members
		ObjectRefHandle landingMarker;  // 10
		std::uint32_t   pad14;          // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraForcedLandingMarker) == 0x18);
}
