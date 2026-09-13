#include "RE/H/hkpShapePhantom.h"

namespace RE
{
	void hkpShapePhantom::SetTransform(const hkTransform& transform)
	{
		using func_t = decltype(&hkpShapePhantom::SetTransform);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60790, 61652) };
		return func(this, transform);
	}

	void hkpShapePhantom::SetPosition(const hkVector4& position, float extraTolerance)
	{
		using func_t = decltype(&hkpShapePhantom::SetPosition);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60791, 61653) };
		return func(this, position, extraTolerance);
	}
}
