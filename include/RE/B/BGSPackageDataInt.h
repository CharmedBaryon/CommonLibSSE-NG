#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class BGSPackageDataInt : public BGSNamedPackageData<IPackageData>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataInt;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataInt;

		~BGSPackageDataInt() override;  // 00

		// override (BGSNamedPackageData<IPackageData>)
		bool                               GetDataAsString(BSString* a_dst) const override;  // 0A
		[[nodiscard]] const BSFixedString& GetTypeName() const override;                     // 0B

		// members
		std::int32_t  value;  // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(offsetof(BGSPackageDataInt, value) == 0x10);
	static_assert(sizeof(BGSPackageDataInt) == 0x18);
}
