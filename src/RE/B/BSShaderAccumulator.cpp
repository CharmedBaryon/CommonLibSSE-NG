#include "RE/B/BSShaderAccumulator.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	BSShaderAccumulator* BSShaderAccumulator::Create(std::uint32_t a_unk)
	{
		auto accumulator = malloc<BSShaderAccumulator>();
		if (accumulator) {
			accumulator->Ctor(a_unk);
		}
		return accumulator;
	}

	BSShaderAccumulator* BSShaderAccumulator::Ctor(std::uint32_t a_unk)
	{
		using func_t = decltype(&BSShaderAccumulator::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99920, 106564) };
		return func(this, a_unk);
	}

	BSShaderAccumulator* BSShaderAccumulator::GetCurrentAccumulator()
	{
		using func_t = decltype(&BSShaderAccumulator::GetCurrentAccumulator);
		static REL::Relocation<func_t> func{ RELOCATION_ID(98997, 105651) };
		return func();
	}

	void BSShaderAccumulator::SetCurrentAccumulator(BSShaderAccumulator* a_accumulator)
	{
		using func_t = decltype(&BSShaderAccumulator::SetCurrentAccumulator);
		static REL::Relocation<func_t> func{ RELOCATION_ID(98998, 105652) };
		return func(a_accumulator);
	}

	void BSShaderAccumulator::RenderFirstPersonView_End(bool a_force)
	{
		using func_t = decltype(&BSShaderAccumulator::RenderFirstPersonView_End);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99964, 106610) };
		return func(this, a_force);
	}
}
