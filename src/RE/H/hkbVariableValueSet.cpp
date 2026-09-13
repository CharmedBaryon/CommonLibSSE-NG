#include "RE/H/hkbVariableValueSet.h"

namespace RE
{
	int hkbVariableValueSet::AddBool(bool a_value)
	{
		if (m_wordVariableValues.data()) {
			hkbVariableValue value;
			value.b = a_value;
			int index = m_wordVariableValues.size();
			m_wordVariableValues.push_back(value);
			return index;
		}

		return -1;
	}

	int hkbVariableValueSet::AddInt(std::int32_t a_value)
	{
		if (m_wordVariableValues.data()) {
			hkbVariableValue value;
			value.i = a_value;
			int index = m_wordVariableValues.size();
			m_wordVariableValues.push_back(value);
			return index;
		}

		return -1;
	}

	int hkbVariableValueSet::AddFloat(float a_value)
	{
		if (m_wordVariableValues.data()) {
			hkbVariableValue value;
			value.f = a_value;
			int index = m_wordVariableValues.size();
			m_wordVariableValues.push_back(value);
			return index;
		}

		return -1;
	}
}
