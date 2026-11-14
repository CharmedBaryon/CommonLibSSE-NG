#pragma once

#include "RE/B/bhkSerializable.h"

namespace RE
{
	class hkpConstraintInstance;
	class hkpRigidBody;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0), which
	// redeclares a constraint/cinfo pointer pair here -- already covered by the
	// inherited bhkRefObject::referencedObject (0x10) and bhkSerializable::cinfo
	// (0x18), so this class adds no new fields of its own.
	class bhkConstraint : public bhkSerializable
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkConstraint;
	};
	static_assert(sizeof(bhkConstraint) == 0x20);
}
