#pragma once

#include "RE/B/BGSLoadFormData.h"
#include "RE/B/BGSLoadGameBuffer.h"

namespace RE
{
	class BGSLoadFormBuffer :
		public BGSLoadGameBuffer,  // 00
		public BGSLoadFormData     // 28
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSLoadFormBuffer;
		inline static constexpr auto VTABLE = VTABLE_BGSLoadFormBuffer;

		~BGSLoadFormBuffer() override;

		// override (BGSLoadGameBuffer)
		std::uint8_t GetVersion(void) override;  // 01 - { return version; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSLoadFormBuffer) == 0x50);
}
