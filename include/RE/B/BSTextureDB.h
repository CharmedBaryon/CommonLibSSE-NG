#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiTexture;

	namespace BSTextureDB
	{
		struct DBTraits
		{
		public:
			inline static constexpr auto          RTTI = RTTI_BSTextureDB__DBTraits;
			inline static constexpr std::uint32_t LOAD_QUEUE_SIZE = 8;
			inline static constexpr std::uint32_t RELEASE_QUEUE_SIZE = 32;

			using U_Type = NiPointer<NiTexture>;

			struct ArgsType
			{
			public:
				// members
				std::uint32_t texLoadLevel;  // 00
				bool          isCubeMap;     // 04
				bool          unk05;         // 05
				bool          unk06;         // 06
				std::uint8_t  pad07;         // 07
			};
			static_assert(sizeof(ArgsType) == 0x8);
		};
		static_assert(std::is_empty_v<DBTraits>);
	}
}
