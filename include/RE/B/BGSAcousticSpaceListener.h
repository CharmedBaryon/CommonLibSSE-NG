#pragma once

#include "RE/H/hkpEntityListener.h"

namespace RE
{
	class BGSAcousticSpaceListener : public hkpEntityListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAcousticSpaceListener;
		inline static constexpr auto VTABLE = VTABLE_BGSAcousticSpaceListener;

		~BGSAcousticSpaceListener() override;  // 00

		// override (hkpEntityListener)
		void EntityAddedCallback(hkpEntity* a_entity) override;    // 01 - { return; }
		void EntityRemovedCallback(hkpEntity* a_entity) override;  // 02
		void EntityDeletedCallback(hkpEntity* a_entity) override;  // 05 - { return; }

		// add
		virtual void RemoveCollidable(hkpEntity* a_entity);                             // 06
		virtual void AddCollidable(hkpEntity* a_entityA, hkpEntity* a_entityB);         // 07
		virtual void HandleCollidableExit(hkpEntity* a_entityA, hkpEntity* a_entityB);  // 08 - fired by bhkAcousticSpacePhantomCallbackShape's phantom-exit callback (paired with AddCollidable's phantom-enter callback); param types inferred by symmetry with AddCollidable, not independently confirmed

		struct Entry
		{
			std::uint32_t refHandle;  // 00
			std::uint32_t refCount;   // 04
			std::uint64_t pad08;      // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		// members
		void*         unk08;        // 08
		std::uint32_t count;        // 10
		std::uint32_t capacity;     // 14
		std::uint32_t numBuckets;   // 18
		std::uint32_t pad1C;        // 1C
		Entry*        entries;      // 20
		std::uint8_t  unk28[0x28];  // 28
	};
	static_assert(sizeof(BGSAcousticSpaceListener) == 0x50);
}
