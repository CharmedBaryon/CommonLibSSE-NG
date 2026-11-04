#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class TESTopic;

	class BGSPackageDataTopic : public BGSNamedPackageData<IPackageData>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataTopic;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataTopic;

		~BGSPackageDataTopic() override;  // 00

		// members
		std::uint32_t kind;   // 10 - 0: topic form, otherwise: index into a table of named topics
		std::uint32_t pad14;  // 14
		union
		{
			TESTopic*     topic;  // kind == 0
			std::uint32_t index;  // kind != 0
		};                        // 18
	};
	static_assert(offsetof(BGSPackageDataTopic, kind) == 0x10);
	static_assert(sizeof(BGSPackageDataTopic) == 0x20);
}
