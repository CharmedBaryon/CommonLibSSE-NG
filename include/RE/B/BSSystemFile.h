#pragma once

#include "REX/W32/BASE.h"

namespace RE
{
	namespace BSResource
	{
		class BSSystemFile
		{
		public:
			struct Info
			{
				// members
				REX::W32::FILETIME accessTime;  // 00
				REX::W32::FILETIME modifyTime;  // 08
				REX::W32::FILETIME createTime;  // 10
				std::uint64_t      fileSize;    // 18
			};
			static_assert(sizeof(Info) == 0x20);

			BSSystemFile();

			// members
			std::uint32_t flags{ 1 };                              // 00
			std::uint32_t pad04{ 0 };                              // 04
			void*         file{ REX::W32::INVALID_HANDLE_VALUE };  // 08
		};
		static_assert(sizeof(BSSystemFile) == 0x10);
	}
}
