#pragma once

#include "RE/B/BSModelDB.h"

namespace RE
{
	namespace TESModelDB
	{
		class TESProcessor : public BSModelDB::BSModelProcessor
		{
		public:
			inline static constexpr auto RTTI = RTTI_TESModelDB____TESProcessor;
			inline static constexpr auto VTABLE = VTABLE_TESModelDB____TESProcessor;

			~TESProcessor() override;

			// override (BSModelDM::BSModelProcessor)
			void PostCreate(const BSModelDB::DBTraits::ArgsType& a_args, const char* modelName, NiPointer<NiNode>& a_root, std::uint32_t& a_typeOut) override;
		};
	}
}
