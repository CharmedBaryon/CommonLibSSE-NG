#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class BGSPackageDataFloat : public BGSNamedPackageData<IPackageData>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataFloat;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataFloat;

		~BGSPackageDataFloat() override;  // 00

		// override (BGSNamedPackageData<IPackageData>)
		bool                               GetDataAsString(BSString* a_dst) const override;  // 0A
		[[nodiscard]] const BSFixedString& GetTypeName() const override;                     // 0B

		// members
		float         value;  // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(offsetof(BGSPackageDataFloat, value) == 0x10);
	static_assert(sizeof(BGSPackageDataFloat) == 0x18);
}
