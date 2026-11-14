#pragma once

#include "RE/B/BGSPackageDataBasicTemplate.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/I/IAITarget.h"

namespace RE
{
	class BGSPackageDataRefOLD : public BGSPackageDataBasicTemplate<IAITarget, ObjectRefHandle /*, kPackageDataRefTypeName*/>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataRefOLD;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataRefOLD;

		~BGSPackageDataRefOLD() override;  // 00
	};
	static_assert(offsetof(BGSPackageDataRefOLD, value) == 0x18);
	static_assert(sizeof(BGSPackageDataRefOLD) == 0x20);
}
