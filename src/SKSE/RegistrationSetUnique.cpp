#include "SKSE/RegistrationSetUnique.h"

#include "SKSE/Logger.h"

namespace SKSE
{
	namespace Impl
	{
		RegistrationSetUniqueBase::RegistrationSetUniqueBase(const std::string_view& a_eventName) :
			_regs(),
			_eventName(a_eventName),
			_lock()
		{}

		RegistrationSetUniqueBase::RegistrationSetUniqueBase(const RegistrationSetUniqueBase& a_rhs) :
			_regs(),
			_eventName(a_rhs._eventName),
			_lock()
		{
			a_rhs._lock.lock();
			_regs = a_rhs._regs;
			a_rhs._lock.unlock();

			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& uniqueHandle : _regs) {
					for (auto& handle : uniqueHandle.second) {
						policy->PersistHandle(handle);
					}
				}
			}
		}

		RegistrationSetUniqueBase::RegistrationSetUniqueBase(RegistrationSetUniqueBase&& a_rhs) :
			_regs(),
			_eventName(a_rhs._eventName),
			_lock()
		{
			Locker locker(a_rhs._lock);
			_regs = std::move(a_rhs._regs);
			a_rhs._regs.clear();
		}

		RegistrationSetUniqueBase::~RegistrationSetUniqueBase()
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& uniqueHandle : _regs) {
					for (auto& handle : uniqueHandle.second) {
						policy->ReleaseHandle(handle);
					}
				}
			}
		}

		RegistrationSetUniqueBase& RegistrationSetUniqueBase::operator=(const RegistrationSetUniqueBase& a_rhs)
		{
			if (this == &a_rhs) {
				return *this;
			}

			Locker lhsLocker(_lock);
			Clear();

			{
				Locker rhsLocker(a_rhs._lock);
				_regs = a_rhs._regs;
				_eventName = a_rhs._eventName;
			}

			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& uniqueHandle : _regs) {
					for (auto& handle : uniqueHandle.second) {
						policy->PersistHandle(handle);
					}
				}
			}

			return *this;
		}

		RegistrationSetUniqueBase& RegistrationSetUniqueBase::operator=(RegistrationSetUniqueBase&& a_rhs)
		{
			if (this == &a_rhs) {
				return *this;
			}

			Locker lhsLocker(_lock);
			Locker rhsLocker(a_rhs._lock);

			Clear();

			_eventName = a_rhs._eventName;

			_regs = std::move(a_rhs._regs);
			a_rhs._regs.clear();

			return *this;
		}

		bool RegistrationSetUniqueBase::Register(RE::TESForm* a_form)
		{
			assert(a_form);

			const auto reference = a_form->AsReference();
			const auto formID = reference ? reference->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_form, formID, static_cast<RE::VMTypeID>(a_form->GetFormType()));
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Register(RE::BGSRefAlias* a_alias)
		{
			assert(a_alias);

			const auto target = a_alias->GetActorReference();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_alias, formID, RE::BGSRefAlias::VMTYPEID);
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Register(RE::ActiveEffect* a_activeEffect)
		{
			assert(a_activeEffect);

			const auto target = a_activeEffect->GetTargetActor();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_activeEffect, formID, RE::ActiveEffect::VMTYPEID);
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Unregister(RE::TESForm* a_form)
		{
			assert(a_form);

			const auto reference = a_form->AsReference();
			const auto formID = reference ? reference->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_form, formID, static_cast<RE::VMTypeID>(a_form->GetFormType()));
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Unregister(RE::BGSRefAlias* a_alias)
		{
			assert(a_alias);

			const auto target = a_alias->GetActorReference();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_alias, formID, RE::BGSRefAlias::VMTYPEID);
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Unregister(RE::ActiveEffect* a_activeEffect)
		{
			assert(a_activeEffect);

			const auto target = a_activeEffect->GetTargetActor();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_activeEffect, formID, RE::ActiveEffect::VMTYPEID);
			}

			return false;
		}

		void RegistrationSetUniqueBase::Clear()
		{
			auto   vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto   policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			Locker locker(_lock);
			if (policy) {
				for (auto& uniqueHandle : _regs) {
					for (auto& handle : uniqueHandle.second) {
						policy->ReleaseHandle(handle);
					}
				}
			}
			_regs.clear();
		}

		bool RegistrationSetUniqueBase::Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
		{
			assert(a_intfc);
			if (!a_intfc->OpenRecord(a_type, a_version)) {
				log::error("Failed to open record");
				return false;
			}

			return Save(a_intfc);
		}

		bool RegistrationSetUniqueBase::Save(SerializationInterface* a_intfc)
		{
			assert(a_intfc);

			Locker            locker(_lock);
			const std::size_t numUniqueHandles = _regs.size();
			if (!a_intfc->WriteRecordData(numUniqueHandles)) {
				log::error("Failed to save unique handle count ({})", numUniqueHandles);
				return false;
			}

			for (auto& [formID, handleSet] : _regs) {
				if (!a_intfc->WriteRecordData(formID)) {
					log::error("Failed to save target formID ({:X})", formID);
					return false;
				}
				const std::size_t numHandles = handleSet.size();
				if (!a_intfc->WriteRecordData(numHandles)) {
					log::error("Failed to save handle count ({})", numHandles);
					return false;
				}
				for (auto& handle : handleSet) {
					if (!a_intfc->WriteRecordData(handle)) {
						log::error("Failed to save reg handle ({})", handle);
						return false;
					}
				}
			}

			return true;
		}

		bool RegistrationSetUniqueBase::Load(SerializationInterface* a_intfc)
		{
			assert(a_intfc);
			std::size_t numUniqueHandles;
			a_intfc->ReadRecordData(numUniqueHandles);

			Locker locker(_lock);
			_regs.clear();

			RE::FormID formID;

			std::size_t  numHandles;
			RE::VMHandle vmHandle;

			for (std::size_t i = 0; i < numUniqueHandles; ++i) {
				a_intfc->ReadRecordData(formID);
				if (!a_intfc->ResolveFormID(formID, formID)) {
					log::warn("Error reading formID ({:X})", formID);
					continue;
				}
				a_intfc->ReadRecordData(numHandles);
				for (std::size_t j = 0; j < numHandles; ++j) {
					a_intfc->ReadRecordData(vmHandle);
					if (a_intfc->ResolveHandle(vmHandle, vmHandle)) {
						_regs[formID].insert(vmHandle);
					}
				}
			}

			return true;
		}

		void RegistrationSetUniqueBase::Revert(SerializationInterface*)
		{
			Clear();
		}

		bool RegistrationSetUniqueBase::Register(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID)
		{
			assert(a_object);
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy");
				return false;
			}

			const auto invalidHandle = policy->EmptyHandle();
			const auto handle = policy->GetHandleForObject(a_typeID, a_object);
			if (handle == invalidHandle) {
				log::error("Failed to create handle");
				return false;
			}

			_lock.lock();
			auto result = _regs[a_formID].insert(handle);
			_lock.unlock();

			if (result.second) {
				policy->PersistHandle(handle);
			}

			return result.second;
		}

		bool RegistrationSetUniqueBase::Unregister(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID)
		{
			assert(a_object);
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return false;
			}

			auto invalidHandle = policy->EmptyHandle();
			auto handle = policy->GetHandleForObject(a_typeID, a_object);
			if (handle == invalidHandle) {
				log::error("Failed to create handle!");
				return false;
			}

			Locker locker(_lock);
			if (auto it = _regs.find(a_formID); it != _regs.end()) {
				if (auto result = it->second.erase(handle); result != 0) {
					policy->ReleaseHandle(handle);
					return true;
				}
			}
			return false;
		}

		bool RegistrationSetUniqueBase::Unregister(RE::VMHandle a_handle)
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return false;
			}

			Locker locker(_lock);
			for (auto& uniqueHandle : _regs) {
				if (auto result = uniqueHandle.second.erase(a_handle); result != 0) {
					policy->ReleaseHandle(a_handle);
					return true;
				}
			}

			return false;
		}

		bool RegistrationSetUniqueBase::Unregister(RE::FormID a_uniqueID)
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return false;
			}

			Locker locker(_lock);
			auto   it = _regs.find(a_uniqueID);
			if (it != _regs.end()) {
				for (auto& handle : it->second) {
					policy->ReleaseHandle(handle);
				}
				_regs.erase(it);
				return true;
			}

			return false;
		}
	}
}
