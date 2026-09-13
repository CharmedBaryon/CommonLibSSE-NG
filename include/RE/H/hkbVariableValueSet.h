#pragma once

#include "RE//H/hkVector4.h"
#include "RE/H/hkArray.h"
#include "RE/H/hkRefVariant.h"

namespace RE
{
	union hkbVariableValue
	{
		bool         b;
		std::int32_t i;
		float        f;
	};
	static_assert(sizeof(hkbVariableValue) == 0x4);

	/// The minimum and maximum value for a word-sized behavior variable.
	struct hkbVariableBounds
	{
		hkbVariableValue m_min;
		hkbVariableValue m_max;

	private:
	};
	static_assert(sizeof(hkbVariableBounds) == 0x8);

	/// A set of behavior variable values.  The user must keep track of the types of the variables.
	class hkbVariableValueSet : public hkReferencedObject
	{
	public:
		int AddBool(bool a_value);
		int AddInt(std::int32_t a_value);
		int AddFloat(float a_value);

	private:
		// The values of variables that fit into a word.  For all other variables, this array stores the index
		// into one of the other arrays below.
		hkArray<hkbVariableValue> m_wordVariableValues;

		// The values of the variables that fit into a quadword.
		hkArray<hkVector4> m_quadVariableValues;

		// The values of the variables that are variants.
		hkArray<hkRefVariant> m_variantVariableValues;
	};
	static_assert(sizeof(hkbVariableValueSet) == 0x40);

}
