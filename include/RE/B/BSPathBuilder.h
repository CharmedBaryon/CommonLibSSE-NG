#pragma once

#include "RE/B/BSPathing.h"  // BSPathingSolution
#include "RE/B/BSPathingRequest.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IPathBuilder.h"

namespace RE
{
	class ScrapHeap;

	class BSPathBuilder : public IPathBuilder
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathBuilder;
		inline static constexpr auto VTABLE = VTABLE_BSPathBuilder;

		~BSPathBuilder() override;  // 00
		void Build() override;      // 01

		// members
		BSTSmartPointer<BSPathingRequest>  request;      // 08 - refcount at +08 (BSIntrusiveRefCounted), virtual dtor
		BSTSmartPointer<BSPathingSolution> solution;     // 10 - refcount at +00, sized delete (size 0xB0)
		ScrapHeap*                         threadScrap;  // 18 - MemoryManager::GetThreadScrapHeap()
		bool                               flag20;       // 20
		std::uint8_t                       pad21[7];     // 21
	};
	STATIC_ASSERT_SIZE(BSPathBuilder, 0x28);
}
