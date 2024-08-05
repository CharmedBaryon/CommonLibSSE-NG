#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTTuple.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraScriptedAnimDependence : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraScriptedAnimDependence;
		inline static constexpr auto VTABLE = VTABLE_ExtraScriptedAnimDependence;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kScriptedAnimDependence;

		~ExtraScriptedAnimDependence() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kScriptedAnimDependence; }

		// members
		BSTArray<BSTTuple<ObjectRefHandle, std::uint32_t>> dependentManagers;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraScriptedAnimDependence) == 0x28);
}
