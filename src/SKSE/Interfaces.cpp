#include "SKSE/Interfaces.h"

#include "RE/V/VirtualMachine.h"

#include "SKSE/API.h"
#include "SKSE/Logger.h"

#include <Windows.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace SKSE
{
	bool ScaleformInterface::Register(RegCallback* a_callback, const char* a_name) const
	{
		auto result = GetProxy().Register(a_name, reinterpret_cast<void*>(a_callback));
		if (!result) {
			log::error("Failed to register {} for scaleform interface callback", a_name);
		}
		return result;
	}

	void ScaleformInterface::Register(RegInvCallback* a_callback) const
	{
		GetProxy().RegisterForInventory(reinterpret_cast<void*>(a_callback));
	}

	void SerializationInterface::SetUniqueID(std::uint32_t a_uid) const
	{
		GetProxy().SetUniqueID(GetPluginHandle(), a_uid);
	}

	void SerializationInterface::SetRevertCallback(EventCallback* a_callback) const
	{
		GetProxy().SetRevertCallback(GetPluginHandle(), reinterpret_cast<void*>(a_callback));
	}

	void SerializationInterface::SetSaveCallback(EventCallback* a_callback) const
	{
		GetProxy().SetSaveCallback(GetPluginHandle(), reinterpret_cast<void*>(a_callback));
	}

	void SerializationInterface::SetLoadCallback(EventCallback* a_callback) const
	{
		GetProxy().SetLoadCallback(GetPluginHandle(), reinterpret_cast<void*>(a_callback));
	}

	void SerializationInterface::SetFormDeleteCallback(FormDeleteCallback* a_callback) const
	{
		GetProxy().SetFormDeleteCallback(GetPluginHandle(), reinterpret_cast<void*>(a_callback));
	}

	bool SerializationInterface::WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const void* a_buf, std::uint32_t a_length) const
	{
		return GetProxy().WriteRecord(a_type, a_version, a_buf, a_length);
	}

	bool SerializationInterface::OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const
	{
		return GetProxy().OpenRecord(a_type, a_version);
	}

	bool SerializationInterface::WriteRecordData(const void* a_buf, std::uint32_t a_length) const
	{
		return GetProxy().WriteRecordData(a_buf, a_length);
	}

	bool SerializationInterface::WriteRecordDataEx(std::uint32_t& a_diff, const void* a_buf, std::uint32_t a_length) const
	{
		a_diff += a_length;
		return GetProxy().WriteRecordData(a_buf, a_length);
	}

	bool SerializationInterface::GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_length) const
	{
		return GetProxy().GetNextRecordInfo(&a_type, &a_version, &a_length);
	}

	std::uint32_t SerializationInterface::ReadRecordData(void* a_buf, std::uint32_t a_length) const
	{
		return GetProxy().ReadRecordData(a_buf, a_length);
	}

	std::uint32_t SerializationInterface::ReadRecordDataEx(std::uint32_t& a_diff, void* a_buf, std::uint32_t a_length) const
	{
		const auto result = GetProxy().ReadRecordData(a_buf, a_length);
		a_diff -= result;
		return result;
	}

	bool PapyrusInterface::Register_Impl(RegFunction1* a_fn) const
	{
		assert(a_fn);
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		if (vm) {
			a_fn(vm);
			return true;
		} else {
			auto result = GetProxy().Register(reinterpret_cast<void*>(a_fn));
			if (!result) {
				log::error("Failed to register for papyrus interface");
			}
			return result;
		}
	}

	bool PapyrusInterface::Register_Impl(RegFunction2* a_fn) const
	{
		assert(a_fn);
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		if (vm) {
			a_fn(vm);
			return true;
		} else {
			auto result = GetProxy().Register(reinterpret_cast<void*>(a_fn));
			if (!result) {
				log::error("Failed to register for papyrus interface");
			}
			return result;
		}
	}

	bool MessagingInterface::Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const
	{
		auto result = GetProxy().Dispatch(GetPluginHandle(), a_messageType, a_data, a_dataLen, a_receiver);
		if (!result) {
			log::warn("Failed to dispatch message to {}", (a_receiver ? a_receiver : "all listeners"));
		}
		return result;
	}

	bool MessagingInterface::RegisterListener(const char* a_sender, EventCallback* a_callback) const
	{
		auto result = GetProxy().RegisterListener(GetPluginHandle(), a_sender, reinterpret_cast<void*>(a_callback));
		if (!result) {
			log::error("Failed to register messaging listener for {}", a_sender);
		}
		return result;
	}

	void* TrampolineInterface::AllocateFromBranchPool(std::size_t a_size) const
	{
		return GetProxy().AllocateFromBranchPool(GetPluginHandle(), a_size);
	}

	void* TrampolineInterface::AllocateFromLocalPool(std::size_t a_size) const
	{
		return GetProxy().AllocateFromLocalPool(GetPluginHandle(), a_size);
	}

	[[nodiscard]] const PluginDeclaration* PluginDeclaration::GetSingleton() noexcept
	{
		return reinterpret_cast<const PluginDeclaration*>(GetProcAddress(reinterpret_cast<HMODULE>(&__ImageBase), "SKSEPlugin_Version"));
	}

	const PluginVersionData* PluginVersionData::GetSingleton() noexcept
	{
		return reinterpret_cast<const PluginVersionData*>(REX::W32::GetProcAddress(REX::W32::GetCurrentModule(), "SKSEPlugin_Version"));
	}

}
