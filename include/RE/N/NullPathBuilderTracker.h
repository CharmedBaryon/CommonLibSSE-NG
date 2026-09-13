#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/I/IPathBuilderTracker.h"

namespace RE
{
	class NullPathBuilderTracker :
		public IPathBuilderTracker,                          // 00
		public BSTSingletonImplicit<NullPathBuilderTracker>  // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_NullPathBuilderTracker;
		inline static constexpr auto VTABLE = VTABLE_NullPathBuilderTracker;

		~NullPathBuilderTracker() override;  // 00

		void Unk_01(void) override;  // 01
		void Unk_02(void) override;  // 02
	};
	STATIC_ASSERT_SIZE(NullPathBuilderTracker, 0x8);
}
