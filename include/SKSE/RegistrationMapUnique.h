#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BGSRefAlias.h"
#include "RE/B/BSFixedString.h"
#include "RE/F/FunctionArguments.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/T/TypeTraits.h"
#include "RE/V/VirtualMachine.h"

#include "SKSE/API.h"
#include "SKSE/Impl/RegistrationTraits.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Logger.h"

namespace SKSE
{
	namespace Impl
	{
		template <class Filter>
		class EventFilterUnique
		{
		public:
			using EventFilter = std::pair<Filter, bool>;
			using EventFilterHandleMap = std::map<EventFilter, std::set<RE::VMHandle>>;

			using PassFilterFunc = std::function<bool(const Filter&, bool)>;

			class RegistrationMapUniqueBase
			{
			public:
				RegistrationMapUniqueBase() = delete;
				RegistrationMapUniqueBase(const std::string_view& a_eventName);
				RegistrationMapUniqueBase(const RegistrationMapUniqueBase& a_rhs);
				RegistrationMapUniqueBase(RegistrationMapUniqueBase&& a_rhs) noexcept;
				~RegistrationMapUniqueBase();

				RegistrationMapUniqueBase& operator=(const RegistrationMapUniqueBase& a_rhs);
				RegistrationMapUniqueBase& operator=(RegistrationMapUniqueBase&& a_rhs) noexcept;

				bool Register(RE::TESForm* a_form, const Filter& a_filter, bool a_matchFilter);
				bool Register(RE::ActiveEffect* a_activeEffect, const Filter& a_filter, bool a_matchFilter);
				bool Register(RE::BGSRefAlias* a_alias, const Filter& a_filter, bool a_matchFilter);
				bool Unregister(RE::TESForm* a_form, const Filter& a_filter, bool a_matchFilter);
				bool Unregister(RE::ActiveEffect* a_activeEffect, const Filter& a_filter, bool a_matchFilter);
				bool Unregister(RE::BGSRefAlias* a_alias, const Filter& a_filter, bool a_matchFilter);
				void UnregisterAll(const RE::TESForm* a_form);
				void UnregisterAll(RE::ActiveEffect* a_activeEffect);
				void UnregisterAll(RE::BGSRefAlias* a_alias);
				void UnregisterAll(RE::VMHandle a_handle);
				void UnregisterAll(RE::FormID a_uniqueID);
				void Clear();
				bool Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
				bool Save(SerializationInterface* a_intfc);
				bool Load(SerializationInterface* a_intfc);
				void Revert(SerializationInterface*);

			protected:
				using Lock = std::recursive_mutex;
				using Locker = std::lock_guard<Lock>;

				bool Register(const void* a_object, RE::FormID a_formID, EventFilter a_filter, RE::VMTypeID a_typeID);
				bool Unregister(const void* a_object, RE::FormID a_formID, EventFilter a_filter, RE::VMTypeID a_typeID);
				void UnregisterAll(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID);

				std::map<RE::FormID, EventFilterHandleMap> _regs;
				std::string                                _eventName;
				mutable Lock                               _lock;
			};

			template <class Enable, class... Args>
			class RegistrationMapUnique;

			template <class... Args>
			class RegistrationMapUnique<
				std::enable_if_t<
					std::conjunction_v<
						RE::BSScript::is_return_convertible<Args>...>>,
				Args...> :
				public RegistrationMapUniqueBase
			{
			private:
				using super = RegistrationMapUniqueBase;

			public:
				RegistrationMapUnique() = delete;
				RegistrationMapUnique(const RegistrationMapUnique&) = default;
				RegistrationMapUnique(RegistrationMapUnique&&) = default;

				inline RegistrationMapUnique(const std::string_view& a_eventName) :
					super(a_eventName)
				{}

				~RegistrationMapUnique() = default;

				RegistrationMapUnique& operator=(const RegistrationMapUnique&) = default;
				RegistrationMapUnique& operator=(RegistrationMapUnique&&) = default;

				inline void SendEvent(const RE::TESObjectREFR* a_target, PassFilterFunc a_callback, Args... a_args)
				{
					RE::BSFixedString eventName(this->_eventName);

					if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
						const auto targetFormID = a_target->GetFormID();
						if (auto it = this->_regs.find(targetFormID); it != this->_regs.end()) {
							for (auto& [eventFilter, handles] : it->second) {
								if (a_callback(eventFilter.first, eventFilter.second)) {
									for (auto& handle : handles) {
										auto args = RE::MakeFunctionArguments(std::forward<Args>(a_args)...);
										vm->SendEvent(handle, eventName, args);
									}
								}
							}
						}
					}
				}

				inline void QueueEvent(RE::TESObjectREFR* a_target, PassFilterFunc a_callback, Args... a_args)
				{
					std::tuple args(VMArg(std::forward<Args>(a_args))...);
					auto       task = GetTaskInterface();
					assert(task);
					if (task) {
						task->AddTask([a_target, a_callback, args, this]() mutable {
							SendEvent_Tuple(a_target, a_callback, std::move(args), index_sequence_for_tuple<decltype(args)>{});
						});
					}
				}

			private:
				template <class Tuple, std::size_t... I>
				inline void SendEvent_Tuple(RE::TESObjectREFR* a_target, PassFilterFunc a_callback, Tuple&& a_tuple, std::index_sequence<I...>)
				{
					SendEvent(a_target, a_callback, std::get<I>(std::forward<Tuple>(a_tuple)).Unpack()...);
				}
			};

			template <>
			class RegistrationMapUnique<void> : public RegistrationMapUniqueBase
			{
			private:
				using super = RegistrationMapUniqueBase;

			public:
				RegistrationMapUnique() = delete;
				RegistrationMapUnique(const RegistrationMapUnique&) = default;
				RegistrationMapUnique(RegistrationMapUnique&&) = default;

				inline RegistrationMapUnique(const std::string_view& a_eventName) :
					super(a_eventName)
				{}

				~RegistrationMapUnique() = default;

				RegistrationMapUnique& operator=(const RegistrationMapUnique&) = default;
				RegistrationMapUnique& operator=(RegistrationMapUnique&&) = default;

				inline void SendEvent(const RE::TESObjectREFR* a_target, PassFilterFunc a_callback)
				{
					RE::BSFixedString eventName(this->_eventName);

					if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
						const auto targetFormID = a_target->GetFormID();
						if (auto it = this->_regs.find(targetFormID); it != this->_regs.end()) {
							for (auto& [eventFilter, handles] : it->second) {
								if (a_callback(eventFilter.first, eventFilter.second)) {
									for (auto& handle : handles) {
										auto args = RE::MakeFunctionArguments();
										vm->SendEvent(handle, eventName, args);
									}
								}
							}
						}
					}
				}

				inline void QueueEvent(RE::TESObjectREFR* a_target, PassFilterFunc a_callback)
				{
					auto task = GetTaskInterface();
					assert(task);
					task->AddTask([a_target, a_callback, this]() {
						SendEvent(a_target, std::move(a_callback));
					});
				}
			};
		};

		template <class Filter>
		EventFilterUnique<Filter>::RegistrationMapUniqueBase::RegistrationMapUniqueBase(const std::string_view& a_eventName) :
			_regs(),
			_eventName(a_eventName),
			_lock()
		{}

		template <class Filter>
		EventFilterUnique<Filter>::RegistrationMapUniqueBase::RegistrationMapUniqueBase(const RegistrationMapUniqueBase& a_rhs) :
			_regs(),
			_eventName(a_rhs._eventName),
			_lock()
		{
			a_rhs._lock.lock();
			_regs = a_rhs._regs;
			a_rhs._lock.unlock();

			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& reg : _regs) {
					for (auto& keyHandles : reg.second) {
						for (auto& handle : keyHandles.second) {
							policy->PersistHandle(handle);
						}
					}
				}
			}
		}

		template <class Filter>
		EventFilterUnique<Filter>::RegistrationMapUniqueBase::RegistrationMapUniqueBase(RegistrationMapUniqueBase&& a_rhs) noexcept :
			_regs(),
			_eventName(a_rhs._eventName),
			_lock()
		{
			Locker locker(a_rhs._lock);
			_regs = std::move(a_rhs._regs);
			a_rhs._regs.clear();
		}

		template <class Filter>
		EventFilterUnique<Filter>::RegistrationMapUniqueBase::~RegistrationMapUniqueBase()
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& reg : _regs) {
					for (auto& keyHandles : reg.second) {
						for (auto& handle : keyHandles.second) {
							policy->ReleaseHandle(handle);
						}
					}
				}
			}
		}

		template <class Filter>
		typename EventFilterUnique<Filter>::RegistrationMapUniqueBase& EventFilterUnique<Filter>::RegistrationMapUniqueBase::operator=(const RegistrationMapUniqueBase& a_rhs)
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
				for (auto& reg : _regs) {
					for (auto& keyHandles : reg.second) {
						for (auto& handle : keyHandles.second) {
							policy->PersistHandle(handle);
						}
					}
				}
			}

			return *this;
		}

		template <class Filter>
		typename EventFilterUnique<Filter>::RegistrationMapUniqueBase& EventFilterUnique<Filter>::RegistrationMapUniqueBase::operator=(RegistrationMapUniqueBase&& a_rhs) noexcept
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

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Register(RE::TESForm* a_form, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_form);

			const auto reference = a_form->AsReference();
			const auto formID = reference ? reference->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_form, formID, { a_filter, a_matchFilter }, static_cast<RE::VMTypeID>(a_form->GetFormType()));
			}

			return false;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Register(RE::ActiveEffect* a_activeEffect, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_activeEffect);

			const auto target = a_activeEffect->GetTargetActor();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_activeEffect, formID, { a_filter, a_matchFilter }, RE::ActiveEffect::VMTYPEID);
			}

			return false;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Register(RE::BGSRefAlias* a_alias, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_alias);

			const auto target = a_alias->GetActorReference();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Register(a_alias, formID, { a_filter, a_matchFilter }, RE::BGSRefAlias::VMTYPEID);
			}

			return false;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Unregister(RE::TESForm* a_form, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_form);

			const auto reference = a_form->AsReference();
			const auto formID = reference ? reference->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_form, formID, { a_filter, a_matchFilter }, static_cast<RE::VMTypeID>(a_form->GetFormType()));
			}

			return false;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Unregister(RE::ActiveEffect* a_activeEffect, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_activeEffect);

			const auto target = a_activeEffect->GetTargetActor();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_activeEffect, formID, { a_filter, a_matchFilter }, RE::ActiveEffect::VMTYPEID);
			}

			return false;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Unregister(RE::BGSRefAlias* a_alias, const Filter& a_filter, bool a_matchFilter)
		{
			assert(a_alias);

			const auto target = a_alias->GetActorReference();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				return Unregister(a_alias, formID, { a_filter, a_matchFilter }, RE::BGSRefAlias::VMTYPEID);
			}

			return false;
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(const RE::TESForm* a_form)
		{
			assert(a_form);

			const auto reference = a_form->AsReference();
			const auto formID = reference ? reference->GetFormID() : 0;

			if (formID != 0) {
				UnregisterAll(a_form, formID, static_cast<RE::VMTypeID>(a_form->GetFormType()));
			}
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(RE::ActiveEffect* a_activeEffect)
		{
			assert(a_activeEffect);

			const auto target = a_activeEffect->GetTargetActor();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				UnregisterAll(a_activeEffect, formID, RE::ActiveEffect::VMTYPEID);
			}
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(RE::BGSRefAlias* a_alias)
		{
			assert(a_alias);

			const auto target = a_alias->GetActorReference();
			const auto formID = target ? target->GetFormID() : 0;

			if (formID != 0) {
				UnregisterAll(a_alias, formID, RE::BGSRefAlias::VMTYPEID);
			}
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(RE::VMHandle a_handle)
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return;
			}

			Locker locker(_lock);
			for (auto& reg : _regs) {
				for (auto& keyHandle : reg.second) {
					if (auto result = keyHandle.second.erase(a_handle); result != 0) {
						policy->ReleaseHandle(a_handle);
					}
				}
			}
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(RE::FormID a_uniqueID)
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return;
			}

			Locker locker(_lock);
			auto   it = _regs.find(a_uniqueID);
			if (it != _regs.end()) {
				for (auto& keyHandles : it->second) {
					for (auto& handle : keyHandles.second) {
						policy->ReleaseHandle(handle);
					}
				}
				_regs.erase(it);
			}
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::Clear()
		{
			auto   vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto   policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			Locker locker(_lock);
			if (policy) {
				for (auto& reg : _regs) {
					for (auto& keyHandle : reg.second) {
						for (auto& handle : keyHandle.second) {
							policy->ReleaseHandle(handle);
						}
					}
				}
			}
			_regs.clear();
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
		{
			assert(a_intfc);
			if (!a_intfc->OpenRecord(a_type, a_version)) {
				log::error("Failed to open record!");
				return false;
			}

			return Save(a_intfc);
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Save(SerializationInterface* a_intfc)
		{
			assert(a_intfc);
			Locker locker(_lock);

			// Reg count
			const std::size_t numRegs = _regs.size();
			if (!a_intfc->WriteRecordData(numRegs)) {
				log::error("Failed to save reg count ({})!", numRegs);
				return false;
			}
			for (auto& reg : _regs) {
				//FormID
				if (!a_intfc->WriteRecordData(reg.first)) {
					log::error("Failed to save handle formID ({:X})", reg.first);
					return false;
				}
				std::size_t numUniqueHandle = reg.second.size();
				if (!a_intfc->WriteRecordData(numUniqueHandle)) {
					log::error("Failed to save handle count ({})!", numUniqueHandle);
					return false;
				}
				// UniqueHandle
				for (auto& [key, handles] : reg.second) {
					// EventFilter
					auto [eventFilter, match] = key;
					if (!eventFilter.Save(a_intfc)) {
						log::error("Failed to save event filters!");
						return false;
					}
					if (!a_intfc->WriteRecordData(match)) {
						log::error("Failed to save reg key as bool ({})!", match);
						return false;
					}
					//handle set
					std::size_t numHandles = handles.size();
					if (!a_intfc->WriteRecordData(numHandles)) {
						log::error("Failed to save handle count ({})!", numHandles);
						return false;
					}
					for (auto& handle : handles) {
						if (!a_intfc->WriteRecordData(handle)) {
							log::error("Failed to save handle ({})", handle);
							return false;
						}
					}
				}
			}

			return true;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Load(SerializationInterface* a_intfc)
		{
			assert(a_intfc);
			std::size_t numRegs;
			a_intfc->ReadRecordData(numRegs);

			Locker locker(_lock);
			_regs.clear();

			//FormID
			RE::FormID formID;
			// KeyHandle
			std::size_t numKeyHandle;
			// Handle
			std::size_t  numHandles;
			RE::VMHandle vmHandle;

			for (std::size_t i = 0; i < numRegs; ++i) {
				a_intfc->ReadRecordData(formID);
				if (!a_intfc->ResolveFormID(formID, formID)) {
					log::warn("Failed to resolve target formID ({:X})", formID);
					continue;
				}
				a_intfc->ReadRecordData(numKeyHandle);
				for (std::size_t j = 0; j < numKeyHandle; ++j) {
					// filter
					Filter eventFilter{};
					if (!eventFilter.Load(a_intfc)) {
						log::error("Failed to save event filters!");
						continue;
					}
					bool match;
					a_intfc->ReadRecordData(match);
					EventFilter curKey = { eventFilter, match };
					// handles
					a_intfc->ReadRecordData(numHandles);
					for (std::size_t k = 0; k < numHandles; ++k) {
						a_intfc->ReadRecordData(vmHandle);
						if (a_intfc->ResolveHandle(vmHandle, vmHandle)) {
							_regs[formID][curKey].insert(vmHandle);
						}
					}
				}
			}

			return true;
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::Revert(SerializationInterface*)
		{
			Clear();
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Register(const void* a_object, RE::FormID a_formID, EventFilter a_filter, RE::VMTypeID a_typeID)
		{
			assert(a_object);
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return false;
			}

			const auto invalidHandle = policy->EmptyHandle();
			auto       handle = policy->GetHandleForObject(a_typeID, a_object);
			if (handle == invalidHandle) {
				log::error("Failed to create handle!");
				return false;
			}

			_lock.lock();
			auto result = _regs[a_formID][a_filter].insert(handle);
			_lock.unlock();

			if (result.second) {
				policy->PersistHandle(handle);
			}

			return result.second;
		}

		template <class Filter>
		bool EventFilterUnique<Filter>::RegistrationMapUniqueBase::Unregister(const void* a_object, RE::FormID a_formID, EventFilter a_filter, RE::VMTypeID a_typeID)
		{
			assert(a_object);
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return false;
			}

			const auto invalidHandle = policy->EmptyHandle();
			const auto handle = policy->GetHandleForObject(a_typeID, a_object);
			if (handle == invalidHandle) {
				log::error("Failed to create handle!");
				return false;
			}

			Locker locker(_lock);
			if (auto formIt = _regs.find(a_formID); formIt != _regs.end()) {
				if (auto keyIt = formIt->second.find(a_filter); keyIt != formIt->second.end()) {
					if (auto result = keyIt->second.erase(handle); result != 0) {
						policy->ReleaseHandle(handle);
						return true;
					}
				}
			}

			return false;
		}

		template <class Filter>
		void EventFilterUnique<Filter>::RegistrationMapUniqueBase::UnregisterAll(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID)
		{
			assert(a_object);
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return;
			}

			const auto invalidHandle = policy->EmptyHandle();
			const auto handle = policy->GetHandleForObject(a_typeID, a_object);
			if (handle == invalidHandle) {
				log::error("Failed to create handle!");
				return;
			}

			Locker locker(_lock);
			if (auto it = _regs.find(a_formID); it != _regs.end()) {
				for (auto& keyHandles : it->second) {
					if (auto result = keyHandles.second.erase(handle); result != 0) {
						policy->ReleaseHandle(handle);
					}
				}
			}
		}
	}

	template <class Filter, class... Args>
	using RegistrationMapUnique = typename Impl::EventFilterUnique<Filter>::template RegistrationMapUnique<void, Args...>;
}
