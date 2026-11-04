#pragma once

#include "RE/I/IPackageDataAIWorldLocationHandle.h"

namespace RE
{
	class IAIWorldLocation;

	class BGSPackageDataLocationWrapper : public IPackageDataAIWorldLocationHandle
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataLocationWrapper;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataLocationWrapper;

		~BGSPackageDataLocationWrapper() override;  // 00

		// members
		IAIWorldLocation* location;  // 10
	};
	static_assert(offsetof(BGSPackageDataLocationWrapper, location) == 0x10);
	static_assert(sizeof(BGSPackageDataLocationWrapper) == 0x18);
}
