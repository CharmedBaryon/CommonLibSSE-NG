#include "RE/O/Object.h"

#include "RE/I/IObjectHandlePolicy.h"
#include "RE/O/ObjectTypeInfo.h"
#include "RE/V/VirtualMachine.h"

namespace RE
{
	namespace BSScript
	{
		Object::~Object()
		{
			Dtor();
			stl::memzero(this);
		}

		VMHandle Object::GetHandle() const
		{
			using func_t = decltype(&Object::GetHandle);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97463, 104247) };
			return func(this);
		}

		ObjectTypeInfo* Object::GetTypeInfo()
		{
			return type.get();
		}

		const ObjectTypeInfo* Object::GetTypeInfo() const
		{
			return type.get();
		}

		void* Object::Resolve(VMTypeID a_typeID) const
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			auto myHandle = GetHandle();
			if (policy && policy->HandleIsType(a_typeID, myHandle) && policy->IsHandleObjectAvailable(myHandle)) {
				return policy->GetObjectForHandle(a_typeID, myHandle);
			} else {
				return nullptr;
			}
		}

		void Object::IncRef()
		{
			using func_t = decltype(&Object::IncRef);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97468, 104252) };
			return func(this);
		}

		std::uint32_t Object::DecRef()
		{
			using func_t = decltype(&Object::DecRef);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97469, 104253) };
			return func(this);
		}

		Variable* Object::GetProperty(const BSFixedString& a_name)
		{
			return const_cast<Variable*>(
				const_cast<const Object*>(this)->GetProperty(a_name));
		}

		const Variable* Object::GetProperty(const BSFixedString& a_name) const
		{
			constexpr auto INVALID = static_cast<std::uint32_t>(-1);

			auto idx = INVALID;
			for (auto cls = type.get(); cls && idx == INVALID; cls = cls->GetParent()) {
				idx = cls->GetPropertyIndex(a_name);
			}

			return idx != INVALID ? std::addressof(variables[idx]) : nullptr;
		}

		Variable* Object::GetVariable(const BSFixedString& a_name)
		{
			return const_cast<Variable*>(
				const_cast<const Object*>(this)->GetVariable(a_name));
		}

		const Variable* Object::GetVariable(const BSFixedString& a_name) const
		{
			constexpr auto INVALID = static_cast<std::uint32_t>(-1);

			auto          idx = INVALID;
			std::uint32_t offset = 0;
			for (auto cls = type.get(); cls; cls = cls->GetParent()) {
				const auto vars = cls->GetVariableIter();
				if (idx == INVALID) {
					if (vars) {
						for (std::uint32_t i = 0; i < cls->GetNumVariables(); i++) {
							const auto& var = vars[i];
							if (var.name == a_name) {
								idx = i;
								break;
							}
						}
					}
				} else {
					offset += cls->GetNumVariables();
				}
			}

			if (idx == INVALID) {
				return nullptr;
			}

			return std::addressof(variables[offset + idx]);
		}

		void Object::Dtor()
		{
			using func_t = decltype(&Object::Dtor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97462, 104246) };
			return func(this);
		}
	}
}
