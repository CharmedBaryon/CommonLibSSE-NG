#pragma once

#include "RE/F/FileID.h"

namespace RE
{
	namespace BSResource
	{
		struct ID : public FileID
		{
		public:
			void GenerateFromPath(const char* a_path)
			{
				using func_t = decltype(&ID::GenerateFromPath);
				static REL::Relocation<func_t> func{ RELOCATION_ID(68635, 69979) };
				return func(this, a_path);
			}

			// members
			std::uint32_t dir{ 0 };  // 0
		};
		static_assert(sizeof(ID) == 0xC);
	}
}
