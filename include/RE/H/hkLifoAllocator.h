#pragma once

#include "RE/H/hkMemoryAllocator.h"

namespace RE
{
	class hkLifoAllocator : public hkMemoryAllocator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLifoAllocator;
		inline static constexpr auto VTABLE = VTABLE_hkLifoAllocator;

		class Implementation;

		hkLifoAllocator() { stl::emplace_vtable(this); }

		// override (hkMemoryAllocator)
		void* BlockAlloc(std::int32_t a_numBytesIn) override  // 01
		{
			using func_t = decltype(&hkLifoAllocator::BlockAlloc);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56627, 57032) };
			return func(this, a_numBytesIn);
		}

		void BlockFree(void* a_ptr, std::int32_t a_numBytesIn) override  // 02
		{
			using func_t = decltype(&hkLifoAllocator::BlockFree);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56628, 57033) };
			return func(this, a_ptr, a_numBytesIn);
		}

		void* BufAlloc(std::int32_t& a_reqNumBytesInOut) override  // 03
		{
			using func_t = decltype(&hkLifoAllocator::BufAlloc);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56629, 57034) };
			return func(this, a_reqNumBytesInOut);
		}

		void BufFree(void* a_ptr, std::int32_t a_numBytes) override  // 04
		{
			using func_t = decltype(&hkLifoAllocator::BufFree);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56630, 57035) };
			return func(this, a_ptr, a_numBytes);
		}

		void* BufRealloc(void* a_old, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut) override  // 05
		{
			using func_t = decltype(&hkLifoAllocator::BufRealloc);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56631, 57036) };
			return func(this, a_old, a_oldNumBytes, a_reqNumBytesInOut);
		}

		void         GetMemoryStatistics([[maybe_unused]] MemoryStatistics& a_usage) override {}                                    // 08
		std::int32_t GetAllocatedSize([[maybe_unused]] const void* a_obj, std::int32_t a_numBytes) override { return a_numBytes; }  // 09

		void Init(
			hkMemoryAllocator* a_slabAllocator,
			hkMemoryAllocator* a_largeAllocator,
			hkMemoryAllocator* a_internalAllocator)
		{
			using func_t = decltype(&hkLifoAllocator::Init);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56625, 57030) };
			return func(this, a_slabAllocator, a_largeAllocator, a_internalAllocator);
		}

		void Quit()
		{
			using func_t = decltype(&hkLifoAllocator::Quit);
			static REL::Relocation<func_t> func{ RELOCATION_ID(56626, 57031) };
			return func(this);
		}

		// members
		Implementation*    impl{ nullptr };               // 08
		const std::int32_t SlabSize{ 0x4000 };            // 10
		void*              Cur{ nullptr };                // 18
		void*              End{ nullptr };                // 20
		void*              FirstNonLifoEnd{ nullptr };    // 28
		void*              CachedEmptySlab{ nullptr };    // 30
		hkMemoryAllocator* SlabAllocator{ nullptr };      // 38
		hkMemoryAllocator* LargeAllocator{ nullptr };     // 40
		hkMemoryAllocator* InternalAllocator{ nullptr };  // 48
	};
	static_assert(sizeof(hkLifoAllocator) == 0x50);
}