#pragma once

#include "RE/B/BGSPackageDataPointerTemplate.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class PackageTarget;

	class BGSPackageDataTargetSelector : public BGSPackageDataPointerTemplate<IPackageData, PackageTarget /*, kPackageDataTargetSelectorTypeName*/>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataTargetSelector;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataTargetSelector;

		~BGSPackageDataTargetSelector() override;  // 00
	};
	static_assert(offsetof(BGSPackageDataTargetSelector, pointer) == 0x10);
	static_assert(sizeof(BGSPackageDataTargetSelector) == 0x18);
}
