#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IAITarget.h"

namespace RE
{
	class TESBoundObject;

	class BGSPackageDataObjectList : public BGSNamedPackageData<IAITarget>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataObjectList;
		inline static constexpr auto VTABLE = VTABLE_BGSPackageDataObjectList;

		struct Entry
		{
		public:
			// members
			std::byte       unk00[0x10];  // 00 - vtable and unknown
			ObjectRefHandle ref;          // 10
			std::uint32_t   pad14;        // 14
			TESBoundObject* baseObject;   // 18 - resolved from ref when null
			std::uint32_t   unk20;        // 20
			std::uint32_t   unk24;        // 24
			float           unk28;        // 28
			float           unk2C;        // 2C
		};
		static_assert(sizeof(Entry) == 0x30);

		~BGSPackageDataObjectList() override;  // 00

		// members
		void*           unk18;    // 18 - points back to this object
		BSTArray<Entry> objects;  // 20
		float           radius;   // 38
		std::uint32_t   pad3C;    // 3C
	};
	static_assert(offsetof(BGSPackageDataObjectList, objects) == 0x20);
	static_assert(offsetof(BGSPackageDataObjectList, radius) == 0x38);
	static_assert(sizeof(BGSPackageDataObjectList) == 0x40);
}
