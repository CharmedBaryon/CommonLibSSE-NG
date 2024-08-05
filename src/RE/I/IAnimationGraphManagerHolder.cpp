#include "RE/I/IAnimationGraphManagerHolder.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	bool IAnimationGraphManagerHolder::GetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_out) const
	{
		return GetAnimationGraphManagerImpl(a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out) const
	{
		return GetGraphVariableImpl1(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableInt(const BSFixedString& a_variableName, std::int32_t& a_out) const
	{
		return GetGraphVariableImpl2(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out) const
	{
		return GetGraphVariableImpl3(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_out) const
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::GetGraphVariableNiPoint3);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32192, 32884) };
		return func(this, a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::SetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_in)
	{
		return SetAnimationGraphManagerImpl(a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableBool(const BSFixedString& a_variableName, bool a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableBool);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32141, 32885) };
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableInt(const BSFixedString& a_variableName, std::int32_t a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableInt);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32142, 32886) };
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableFloat(const BSFixedString& a_variableName, float a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableFloat);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32143, 32887) };
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_in) const
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableNiPoint3);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32144, 32888) };
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::UpdateAnimationGraphManager(const BSAnimationUpdateData& a_updateData)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::UpdateAnimationGraphManager);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32155, 32899) };
		return func(this, a_updateData);
	}
}
