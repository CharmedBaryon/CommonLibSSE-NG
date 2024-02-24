#pragma once

#include "REX/W32/BASE.h"

namespace RE
{
	namespace BSResource
	{
		struct Info
		{
		public:
			// members
			REX::W32::FILETIME modifyTime;  // 00
			REX::W32::FILETIME createTime;  // 08
			std::uint64_t      fileSize;    // 10
		};
		static_assert(sizeof(Info) == 0x18);
	}
}
