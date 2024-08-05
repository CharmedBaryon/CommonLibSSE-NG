#pragma once
#include "RE/M/MemoryPage.h"
namespace RE
{
	namespace BSScript
	{
		struct IMemoryPagePolicy
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IMemoryPagePolicy;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IMemoryPagePolicy;

			enum class AllocationStatus
			{
				kSuccess,
				kFailed,
				kOutOfMemory
			};

			enum class NewPageStrategy
			{
				kNormal,
				kIgnoreMemoryLimit
			};

			virtual ~IMemoryPagePolicy();  // 00

			// add
			virtual std::uint32_t    MaximumPageSize() = 0;                                                                                         // 01
			virtual AllocationStatus AllocatePage(std::uint32_t a_pageSize, NewPageStrategy a_stategy, BSTAutoPointer<MemoryPage>& a_newPage) = 0;  // 02
			virtual AllocationStatus GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) = 0;                                            // 03
			virtual void             DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) = 0;                                                        // 04
		};
		static_assert(sizeof(IMemoryPagePolicy) == 0x8);
	}
}
