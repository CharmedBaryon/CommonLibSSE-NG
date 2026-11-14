#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"

namespace RE
{
	class NiCamera;

	class UpdateStarText
	{
	public:
		inline static constexpr auto RTTI = RTTI___UpdateStarText;
		inline static constexpr auto VTABLE = VTABLE___UpdateStarText;

		virtual std::int32_t Unk_00(void* a_unk);

		// members
		std::uint64_t      unk08;   // 08
		std::uint64_t      unk10;   // 10
		std::uint32_t      unk18;   // 18
		std::uint32_t      pad1C;   // 1C
		std::uint64_t      unk20;   // 20
		BSTArray<GFxValue> unk28;   // 28
		NiCamera*          camera;  // 40
		std::uint32_t      unk48;   // 48
		std::uint32_t      pad4C;   // 4C
	};
	static_assert(sizeof(UpdateStarText) == 0x50);
}
