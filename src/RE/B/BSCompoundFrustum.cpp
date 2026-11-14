#include "RE/B/BSCompoundFrustum.h"

#include "REL/Relocation.h"

namespace RE
{
	void BSCompoundFrustum::GetActivePlaneState(std::uint32_t* a_outPlaneState)
	{
		using func_t = decltype(&BSCompoundFrustum::GetActivePlaneState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(75075, 76843) };
		func(this, a_outPlaneState);
	}

	void BSCompoundFrustum::SetActivePlaneState(std::uint32_t* a_planeState)
	{
		using func_t = decltype(&BSCompoundFrustum::SetActivePlaneState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(75076, 76844) };
		func(this, a_planeState);
	}

	bool BSCompoundFrustum::Process(NiAVObject* a_object)
	{
		using func_t = decltype(&BSCompoundFrustum::Process);
		static REL::Relocation<func_t> func{ RELOCATION_ID(75057, 76821) };
		return func(this, a_object);
	}
}
