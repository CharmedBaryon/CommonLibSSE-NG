#include "RE/S/Sun.h"

namespace RE
{
	void Sun::SubmitOcclusionQuery(std::uint32_t a_renderFlags, BSShaderAccumulator* a_accumulator, NiCamera* a_camera)
	{
		using func_t = decltype(&Sun::SubmitOcclusionQuery);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25799, 26353) };
		return func(this, a_renderFlags, a_accumulator, a_camera);
	}

	void Sun::UpdateOcclusionQueries()
	{
		using func_t = decltype(&Sun::UpdateOcclusionQueries);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25801, 26355) };
		return func(this);
	}
}
