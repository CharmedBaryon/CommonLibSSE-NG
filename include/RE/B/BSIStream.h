#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	namespace BSResource
	{
		class Stream;
	}

	class BSIStream
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSIStream;
		inline static constexpr auto VTABLE = VTABLE_BSIStream;

		virtual ~BSIStream() = default;  // 00

		[[nodiscard]] void* DecompressLipData();

		// members
		BSTSmartPointer<BSResource::Stream> stream;    // 08
		bool                                eof;       // 10
		std::uint8_t                        pad11[7];  // 11
		BSFixedString                       name;      // 18
	};
	static_assert(sizeof(BSIStream) == 0x20);
}
