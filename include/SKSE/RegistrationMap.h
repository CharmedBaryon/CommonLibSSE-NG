#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BGSBaseAlias.h"
#include "RE/B/BSFixedString.h"
#include "RE/F/FunctionArguments.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/T/TESForm.h"
#include "RE/T/TypeTraits.h"
#include "RE/V/VirtualMachine.h"

#include "SKSE/API.h"
#include "SKSE/Impl/RegistrationTraits.h"
#include "SKSE/Interfaces.h"

namespace SKSE
{
	namespace Impl
	{
		template <class Filter>
		class EventFilter
		{
		public:
			class RegistrationMapBase
			{
			public:
				RegistrationMapBase() = delete;
				RegistrationMapBase(const std::string_view& a_eventName);
				RegistrationMapBase(const RegistrationMapBase& a_rhs);
				RegistrationMapBase(RegistrationMapBase&& a_rhs);
				~RegistrationMapBase();

				RegistrationMapBase& operator=(const RegistrationMapBase& a_rhs);
				RegistrationMapBase& operator=(RegistrationMapBase&& a_rhs);

				bool Register(const RE::TESForm* a_form, Filter a_filter);
				bool Register(const RE::BGSBaseAlias* a_alias, Filter a_filter);
				bool Register(const RE::ActiveEffect* a_activeEffect, Filter a_filter);
				bool Unregister(const RE::TESForm* a_form, Filter a_filter);
				bool Unregister(const RE::BGSBaseAlias* a_alias, Filter a_filter);
				bool Unregister(const RE::ActiveEffect* a_activeEffect, Filter a_filter);
				void UnregisterAll(const RE::TESForm* a_form);
				void UnregisterAll(const RE::BGSBaseAlias* a_alias);
				void UnregisterAll(const RE::ActiveEffect* a_activeEffect);
				void UnregisterAll(RE::VMHandle a_handle);
				void Clear();
				bool Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
				bool Save(SerializationInterface* a_intfc);
				bool Load(SerializationInterface* a_intfc);
				void Revert(SerializationInterface*);

			protected:
				using Lock = std::recursive_mutex;
				using Locker = std::lock_guard<Lock>;

				bool Register(const void* a_object, Filter a_filter, RE::VMTypeID a_typeID);
				bool Unregister(const void* a_object, Filter a_filter, RE::VMTypeID a_typeID);
				void UnregisterAll(const void* a_object, RE::VMTypeID a_typeID);

				bool SaveFilter(SerializationInterface* a_intfc, Filter a_filter);
				bool LoadFilter(SerializationInterface* a_intfc, Filter& a_filter);

				std::map<Filter, std::set<RE::VMHandle>> _regs;
				std::string                              _eventName;
				mutable Lock                             _lock;
			};

			template <class Enable, class... Args>
			class RegistrationMap;

			template <class... Args>
			class RegistrationMap<
				std::enable_if_t<
					std::conjunction_v<
						RE::BSScript::is_return_convertible<Args>...>>,
				Args...> :
				public RegistrationMapBase
			{
			private:
				using super = RegistrationMapBase;

			public:
				RegistrationMap() = delete;
				RegistrationMap(const RegistrationMap&) = default;
				RegistrationMap(RegistrationMap&&) = default;

				inline RegistrationMap(const std::string_view& a_eventName) :
					super(a_eventName)
				{}

				~RegistrationMap() = default;

				RegistrationMap& operator=(const RegistrationMap&) = default;
				RegistrationMap& operator=(RegistrationMap&&) = default;

				inline void SendEvent(Filter a_filter, Args... a_args)
				{
					RE::BSFixedString eventName(this->_eventName);

					if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
						if (auto it = this->_regs.find(a_filter); it != this->_regs.end()) {
							for (auto& handle : it->second) {
								auto copy = std::make_tuple(a_args...);
								std::apply([&](auto&&... a_copy) {
									auto args = RE::MakeFunctionArguments(std::forward<Args>(a_copy)...);
									vm->SendEvent(handle, eventName, args);
								},
									copy);
							}
						}
					}
				}

				inline void QueueEvent(Filter a_filter, Args... a_args)
				{
					std::tuple args(VMArg(std::forward<Args>(a_args))...);
					auto       task = GetTaskInterface();
					assert(task);
					if (task) {
						task->AddTask([a_filter, args, this]() mutable {
							SendEvent_Tuple(std::move(a_filter), std::move(args), index_sequence_for_tuple<decltype(args)>{});
						});
					}
				}

			private:
				template <class Tuple, std::size_t... I>
				inline void SendEvent_Tuple(Filter a_filter, Tuple&& a_tuple, std::index_sequence<I...>)
				{
					SendEvent(a_filter, std::get<I>(std::forward<Tuple>(a_tuple)).Unpack()...);
				}
			};

			template <>
			class RegistrationMap<void> : public RegistrationMapBase
			{
			private:
				using super = RegistrationMapBase;

			public:
				RegistrationMap() = delete;
				RegistrationMap(const RegistrationMap&) = default;
				RegistrationMap(RegistrationMap&&) = default;

				inline RegistrationMap(const std::string_view& a_eventName) :
					super(a_eventName)
				{}

				~RegistrationMap() = default;

				RegistrationMap& operator=(const RegistrationMap&) = default;
				RegistrationMap& operator=(RegistrationMap&&) = default;

				inline void SendEvent(Filter a_filter)
				{
					RE::BSFixedString eventName(this->_eventName);

					if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
						if (auto it = this->_regs.find(a_filter); it != this->_regs.end()) {
							for (auto& handle : it->second) {
								auto args = RE::MakeFunctionArguments();
								vm->SendEvent(handle, eventName, args);
							}
						}
					}
				}

				inline void QueueEvent(Filter a_filter)
				{
					auto task = GetTaskInterface();
					assert(task);
					task->AddTask([a_filter, this]() {
						SendEvent(std::move(a_filter));
					});
				}
			};
		};

		template <class Filter>
		EventFilter<Filter>::RegistrationMapBase::RegistrationMapBase(const std::string_view& a_eventName) :
			_regs(),
			_eventName(a_eventName),
			_lock()
		{}

		template <class Filter>
		EventFilter<Filter>::RegistrationMapBase::RegistrationMapBase(const RegistrationMapBase& a_rhs) :
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
					for (auto& handle : reg.second) {
						policy->PersistHandle(handle);
					}
				}
			}
		}

		template <class Filter>
		EventFilter<Filter>::RegistrationMapBase::RegistrationMapBase(RegistrationMapBase&& a_rhs) :
			_regs(),
			_eventName(a_rhs._eventName),
			_lock()
		{
			Locker locker(a_rhs._lock);
			_regs = std::move(a_rhs._regs);
			a_rhs._regs.clear();
		}

		template <class Filter>
		EventFilter<Filter>::RegistrationMapBase::~RegistrationMapBase()
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			if (auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr) {
				for (auto& reg : _regs) {
					for (auto& handle : reg.second) {
						policy->ReleaseHandle(handle);
					}
				}
			}
		}

		template <class Filter>
		typename EventFilter<Filter>::RegistrationMapBase& EventFilter<Filter>::RegistrationMapBase::operator=(const RegistrationMapBase& a_rhs)
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
					for (auto& handle : reg.second) {
						policy->PersistHandle(handle);
					}
				}
			}

			return *this;
		}

		template <class Filter>
		typename EventFilter<Filter>::RegistrationMapBase& EventFilter<Filter>::RegistrationMapBase::operator=(RegistrationMapBase&& a_rhs)
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
		bool EventFilter<Filter>::RegistrationMapBase::Register(const RE::TESForm* a_form, Filter a_filter)
		{
			assert(a_form);
			return Register(a_form, std::move(a_filter), static_cast<RE::VMTypeID>(a_form->GetFormType()));
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Register(const RE::BGSBaseAlias* a_alias, Filter a_filter)
		{
			assert(a_alias);
			return Register(a_alias, std::move(a_filter), a_alias->GetVMTypeID());
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Register(const RE::ActiveEffect* a_activeEffect, Filter a_filter)
		{
			assert(a_activeEffect);
			return Register(a_activeEffect, std::move(a_filter), RE::ActiveEffect::VMTYPEID);
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Unregister(const RE::TESForm* a_form, Filter a_filter)
		{
			assert(a_form);
			return Unregister(a_form, std::move(a_filter), static_cast<RE::VMTypeID>(a_form->GetFormType()));
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Unregister(const RE::BGSBaseAlias* a_alias, Filter a_filter)
		{
			assert(a_alias);
			return Unregister(a_alias, std::move(a_filter), a_alias->GetVMTypeID());
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Unregister(const RE::ActiveEffect* a_activeEffect, Filter a_filter)
		{
			assert(a_activeEffect);
			return Unregister(a_activeEffect, std::move(a_filter), RE::ActiveEffect::VMTYPEID);
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::UnregisterAll(const RE::TESForm* a_form)
		{
			assert(a_form);
			UnregisterAll(a_form, static_cast<RE::VMTypeID>(a_form->GetFormType()));
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::UnregisterAll(const RE::BGSBaseAlias* a_alias)
		{
			assert(a_alias);
			UnregisterAll(a_alias, a_alias->GetVMTypeID());
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::UnregisterAll(const RE::ActiveEffect* a_activeEffect)
		{
			assert(a_activeEffect);
			UnregisterAll(a_activeEffect, RE::ActiveEffect::VMTYPEID);
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::UnregisterAll(RE::VMHandle a_handle)
		{
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			if (!policy) {
				log::error("Failed to get handle policy!");
				return;
			}

			Locker locker(_lock);
			for (auto& reg : _regs) {
				if (auto result = reg.second.erase(a_handle); result != 0) {
					policy->ReleaseHandle(a_handle);
				}
			}
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::Clear()
		{
			auto   vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto   policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			Locker locker(_lock);
			if (policy) {
				for (auto& reg : _regs) {
					for (auto& handle : reg.second) {
						policy->ReleaseHandle(handle);
					}
				}
			}
			_regs.clear();
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
		{
			assert(a_intfc);
			if (!a_intfc->OpenRecord(a_type, a_version)) {
				log::error("Failed to open record!");
				return false;
			}

			return Save(a_intfc);
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::SaveFilter(SerializationInterface* a_intfc, Filter a_filter)
		{
			if constexpr (std::is_same_v<std::string, Filter>) {
				std::size_t length = a_filter.length() + 1;
				if (!a_intfc->WriteRecordData(length) || !a_intfc->WriteRecordData(a_filter.c_str(), static_cast<std::uint32_t>(length))) {
					return false;
				}
				return true;
			} else {
				return a_intfc->WriteRecordData(a_filter);
			}
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Save(SerializationInterface* a_intfc)
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
				// filter
				if (!SaveFilter(a_intfc, reg.first)) {
					return false;
				}
				// Handle count
				std::size_t numHandles = reg.second.size();
				if (!a_intfc->WriteRecordData(numHandles)) {
					log::error("Failed to save handle count ({})!", numHandles);
					return false;
				}
				// Handle
				for (auto& handle : reg.second) {
					if (!a_intfc->WriteRecordData(handle)) {
						log::error("Failed to save handle ({})", handle);
						return false;
					}
				}
			}

			return true;
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::LoadFilter(SerializationInterface* a_intfc, Filter& a_filter)
		{
			if constexpr (std::is_same_v<std::string, Filter>) {
				std::size_t length = 0;
				if (!a_intfc->ReadRecordData(length)) {
					return false;
				}
				a_filter.reserve(length);
				return a_intfc->ReadRecordData(a_filter.data(), static_cast<std::uint32_t>(length));
			} else if constexpr (std::is_same_v<RE::FormID, Filter>) {
				if (!a_intfc->ReadRecordData(a_filter)) {
					return false;
				}
				return a_intfc->ResolveFormID(a_filter, a_filter);
			} else {
				return a_intfc->ReadRecordData(a_filter);
			}
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Load(SerializationInterface* a_intfc)
		{
			assert(a_intfc);
			std::size_t numRegs;
			a_intfc->ReadRecordData(numRegs);

			Locker locker(_lock);
			_regs.clear();

			Filter filter{};
			// Handle count
			std::size_t numHandles;
			// Handle
			RE::VMHandle handle;

			for (std::size_t i = 0; i < numRegs; ++i) {
				bool loadedFilter = LoadFilter(a_intfc, filter);
				a_intfc->ReadRecordData(numHandles);
				for (std::size_t j = 0; j < numHandles; ++j) {
					a_intfc->ReadRecordData(handle);
					if (a_intfc->ResolveHandle(handle, handle) && loadedFilter) {
						_regs[filter].insert(handle);
					}
				}
			}

			return true;
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::Revert(SerializationInterface*)
		{
			Clear();
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Register(const void* a_object, Filter a_filter, RE::VMTypeID a_typeID)
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
			auto result = _regs[a_filter].insert(handle);
			_lock.unlock();

			if (result.second) {
				policy->PersistHandle(handle);
			}

			return result.second;
		}

		template <class Filter>
		bool EventFilter<Filter>::RegistrationMapBase::Unregister(const void* a_object, Filter a_filter, RE::VMTypeID a_typeID)
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
			if (auto it = _regs.find(a_filter); it != _regs.end()) {
				if (auto result = it->second.erase(handle); result != 0) {
					policy->ReleaseHandle(handle);
					return true;
				}
			}

			return false;
		}

		template <class Filter>
		void EventFilter<Filter>::RegistrationMapBase::UnregisterAll(const void* a_object, RE::VMTypeID a_typeID)
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
			for (auto& reg : _regs) {
				if (auto result = reg.second.erase(handle); result != 0) {
					policy->ReleaseHandle(handle);
				}
			}
		}
	}

	template <class Filter, class... Args>
	using RegistrationMap = typename Impl::EventFilter<Filter>::template RegistrationMap<void, Args...>;
}
