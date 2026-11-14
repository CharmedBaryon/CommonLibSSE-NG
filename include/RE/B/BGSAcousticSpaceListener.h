#pragma once

#include "RE/B/bhkEntityListener.h"

namespace RE
{
	class BGSAcousticSpaceListener : public bhkEntityListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAcousticSpaceListener;
		inline static constexpr auto VTABLE = VTABLE_BGSAcousticSpaceListener;

		~BGSAcousticSpaceListener() override;  // 00

		// override (bhkEntityListener)
		void EntityAddedCallback(hkpEntity* a_entity) override;              // 01 - { return; }
		void EntityRemovedCallback(hkpEntity* a_entity) override;            // 02
		void EntityDeletedCallback(hkpEntity* a_entity) override;            // 05 - { return; }
		void Update(float a_delta) override;                                 // 06 - finalizes the pending phantom exits
		bool ContactPointAddedCallback(hkpRootCdPoint& a_point) override;    // 07 - fired by bhkAcousticSpacePhantomCallbackShape's phantom-enter callback
		bool ContactPointRemovedCallback(hkpRootCdPoint& a_point) override;  // 08 - fired by its phantom-exit callback

		struct Entry
		{
			std::uint32_t refHandle;  // 00
			std::uint32_t refCount;   // 04
			std::uint64_t pad08;      // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		// members
		std::uint32_t numBuckets;   // 18
		std::uint32_t pad1C;        // 1C
		Entry*        entries;      // 20
		std::uint8_t  unk28[0x28];  // 28
	};
	static_assert(sizeof(BGSAcousticSpaceListener) == 0x50);
}
