#pragma once

namespace RE
{
	class BGSDistantTreeBlock;
	class BGSTerrainNode;

	namespace BGSBttDB
	{
		struct DBTraits
		{
		public:
			inline static constexpr auto          RTTI = RTTI_BGSBttDB__DBTraits;
			inline static constexpr std::uint32_t LOAD_QUEUE_SIZE = 8;
			inline static constexpr std::uint32_t RELEASE_QUEUE_SIZE = 2;

			using U_Type = BGSDistantTreeBlock*;

			struct ArgsType
			{
			public:
				// members
				BGSTerrainNode* node;   // 00
				std::uint32_t   level;  // 08
				std::uint32_t   pad0C;  // 0C
			};
			static_assert(sizeof(ArgsType) == 0x10);
		};
		static_assert(std::is_empty_v<DBTraits>);
	}
}
