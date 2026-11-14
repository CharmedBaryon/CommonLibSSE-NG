#include "RE/H/hkbBehaviorGraphData.h"

namespace RE
{
	bool hkbBehaviorGraphData::HasEventString(hkStringPtr a_name)
	{
		if (stringData) {
			for (auto const& eventName : stringData->eventNames) {
				if (_strcmpi(eventName.c_str(), a_name.c_str()) == 0)
					return true;
			}
		}

		return false;
	}

	bool hkbBehaviorGraphData::HasVariableString(hkStringPtr a_name)
	{
		if (stringData) {
			for (auto const& varName : stringData->variableNames) {
				if (_strcmpi(varName.c_str(), a_name.c_str()) == 0)
					return true;
			}
		}

		return false;
	}

	int hkbBehaviorGraphData::AddBoolVariable(hkStringPtr a_name, bool a_value)
	{
		if (stringData && stringData->variableNames.data() && variableInfos.data() && variableInitialValues && !HasVariableString(a_name)) {
			hkbVariableInfo info;
			info.m_type = hkbVariableInfo::VariableType::VARIABLE_TYPE_BOOL;
			info.m_role.m_role = hkbRoleAttribute::ROLE_DEFAULT;
			info.m_role.m_flags = hkbRoleAttribute::FLAG_NONE;
			stringData->variableNames.push_back(a_name);
			variableInfos.push_back(info);

			return variableInitialValues->AddBool(a_value);
		}

		return -1;
	}

	int hkbBehaviorGraphData::AddIntVariable(hkStringPtr a_name, std::int32_t a_value)
	{
		if (stringData && stringData->variableNames.data() && variableInfos.data() && variableInitialValues && !HasVariableString(a_name)) {
			hkbVariableInfo info;
			info.m_type = hkbVariableInfo::VariableType::VARIABLE_TYPE_INT32;
			info.m_role.m_role = hkbRoleAttribute::ROLE_DEFAULT;
			info.m_role.m_flags = hkbRoleAttribute::FLAG_NONE;
			stringData->variableNames.push_back(a_name);
			variableInfos.push_back(info);

			return variableInitialValues->AddInt(a_value);
		}

		return -1;
	}

	int hkbBehaviorGraphData::AddFloatVariable(hkStringPtr a_name, float a_value)
	{
		if (stringData && stringData->variableNames.data() && variableInfos.data() && variableInitialValues && !HasVariableString(a_name)) {
			hkbVariableInfo info;
			info.m_type = hkbVariableInfo::VariableType::VARIABLE_TYPE_REAL;
			info.m_role.m_role = hkbRoleAttribute::ROLE_DEFAULT;
			info.m_role.m_flags = hkbRoleAttribute::FLAG_NONE;
			stringData->variableNames.push_back(a_name);
			variableInfos.push_back(info);

			return variableInitialValues->AddFloat(a_value);
		}

		return -1;
	}

	int hkbBehaviorGraphData::AddEvent(hkStringPtr a_name)
	{
		if (stringData && stringData->eventNames.data() && eventInfos.data() && !HasEventString(a_name)) {
			hkbEventInfo info;
			stringData->eventNames.push_back(a_name);
			int index = eventInfos.size();
			eventInfos.push_back(info);

			return index;
		}

		return -1;
	}
}
