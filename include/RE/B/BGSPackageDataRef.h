#pragma once

#include "RE/B/BGSPackageDataPointerTemplate.h"
#include "RE/I/IAITarget.h"

namespace RE
{
	class PackageTarget;

	class BGSPackageDataRef : public BGSPackageDataPointerTemplate<IAITarget, PackageTarget /*, kPackageDataRef2TypeName*/>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataRef;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataRef;

		~BGSPackageDataRef() override;  // 00
	};
	static_assert(offsetof(BGSPackageDataRef, pointer) == 0x18);
	static_assert(sizeof(BGSPackageDataRef) == 0x20);
}
