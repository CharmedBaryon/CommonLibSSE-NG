#pragma once

#include "RE/D/DBTraits.h"
#include "RE/E/ErrorCodes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	namespace BSModelDB
	{
		BSResource::ErrorCode Demand(const char* a_modelPath, NiPointer<NiNode>& a_modelOut, const DBTraits::ArgsType& a_args)
		{
			using func_t = decltype(&BSModelDB::Demand);
			REL::Relocation<func_t> func{ RELOCATION_ID(74040, 75782) };
			return func(a_modelPath, a_modelOut, a_args);
		}
	}
}
