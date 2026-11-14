#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/E/ErrorCodes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	namespace BSModelDB
	{
		struct DBTraits
		{
		public:
			inline static constexpr auto          RTTI = RTTI_BSModelDB__DBTraits;
			inline static constexpr std::uint32_t LOAD_QUEUE_SIZE = 8;
			inline static constexpr std::uint32_t RELEASE_QUEUE_SIZE = 2;

			using U_Type = NiPointer<NiNode>;

			struct ArgsType
			{
			public:
				// members
				std::uint32_t LODmult{ 0 };         // 0
				std::uint32_t texLoadLevel{ 3 };    // 4
				bool          unk8{ true };         // 8
				bool          unk9{ false };        // 9
				bool          unkA{ true };         // A
				bool          postProcess{ true };  // B
			};
			static_assert(sizeof(ArgsType) == 0xC);
		};
		static_assert(std::is_empty_v<DBTraits>);

		class BSModelProcessor : public BSTSingletonExplicit<BSModelProcessor>
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSModelDB__BSModelProcessor;
			inline static constexpr auto VTABLE = VTABLE_BSModelDB__BSModelProcessor;

			virtual ~BSModelProcessor();

			// add
			virtual void PostCreate(const DBTraits::ArgsType& a_args, const char* modelName, NiPointer<NiNode>& a_root, std::uint32_t& a_typeOut);
		};

		BSResource::ErrorCode Demand(const char* a_modelPath, NiPointer<NiNode>& a_modelOut, const DBTraits::ArgsType& a_args);
	}
}
