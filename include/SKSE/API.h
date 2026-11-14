#pragma once

#include "RE/B/BSTEvent.h"

#include "SKSE/Events.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Version.h"

namespace SKSE
{
	class PreLoadInterface;
	class LoadInterface;

	class MessagingInterface;
	class ScaleformInterface;
	class PapyrusInterface;
	class SerializationInterface;
	class TaskInterface;
	class ObjectInterface;
	class TrampolineInterface;

	struct PluginInfo;

	struct InitInfo
	{
		bool log{ true };
#ifndef NDEBUG
		spdlog::level::level_enum logLevel{ spdlog::level::debug };
#else
		spdlog::level::level_enum logLevel{ spdlog::level::info };
#endif
		const char* logName{ nullptr };
		const char* logPattern{ nullptr };
		std::size_t logRotate{ 0 };
		bool        trampoline{ false };
		std::size_t trampolineSize{ 0 };
	};

#ifdef ENABLE_SKYRIM_AE
	void Init(const PreLoadInterface* a_intfc, InitInfo a_info = {}) noexcept;
#endif
	void Init(const LoadInterface* a_intfc, InitInfo a_info = {}) noexcept;

	void RegisterForAPIInitEvent(std::function<void()> a_fn);

	[[nodiscard]] std::string_view GetPluginName() noexcept;
	[[nodiscard]] std::string_view GetPluginAuthor() noexcept;
	[[nodiscard]] REL::Version     GetPluginVersion() noexcept;

	[[nodiscard]] PluginHandle      GetPluginHandle() noexcept;
	[[nodiscard]] const PluginInfo* GetPluginInfo(std::string_view a_plugin) noexcept;
	[[nodiscard]] std::uint32_t     GetReleaseIndex() noexcept;
	[[nodiscard]] std::uint32_t     GetSKSEVersion() noexcept;

	[[nodiscard]] const ScaleformInterface*          GetScaleformInterface() noexcept;
	[[nodiscard]] const PapyrusInterface*            GetPapyrusInterface() noexcept;
	[[nodiscard]] const SerializationInterface*      GetSerializationInterface() noexcept;
	[[nodiscard]] const TaskInterface*               GetTaskInterface() noexcept;
	[[nodiscard]] const MessagingInterface*          GetMessagingInterface() noexcept;
	[[nodiscard]] const ObjectInterface*             GetObjectInterface() noexcept;
	[[nodiscard]] const TrampolineInterface*         GetTrampolineInterface() noexcept;
	[[nodiscard]] const SKSEDelayFunctorManager*     GetDelayFunctorManager() noexcept;
	[[nodiscard]] const SKSEObjectRegistry*          GetObjectRegistry() noexcept;
	[[nodiscard]] const SKSEPersistentObjectStorage* GetPersistentObjectStorage() noexcept;

	[[nodiscard]] RE::BSTEventSource<ModCallbackEvent>*  GetModCallbackEventSource() noexcept;
	[[nodiscard]] RE::BSTEventSource<CameraEvent>*       GetCameraEventSource() noexcept;
	[[nodiscard]] RE::BSTEventSource<CrosshairRefEvent>* GetCrosshairRefEventSource() noexcept;
	[[nodiscard]] RE::BSTEventSource<ActionEvent>*       GetActionEventSource() noexcept;
	[[nodiscard]] RE::BSTEventSource<NiNodeUpdateEvent>* GetNiNodeUpdateEventSource() noexcept;
}

namespace SKSE
{
	// DEPRECATED
	[[deprecated("Use SKSE::Init(..., {}) instead")]] void Init(const LoadInterface* a_intfc, bool a_log) noexcept;
	// DEPRECATED
	[[deprecated("Use SKSE::Init(..., {}) instead")]] void AllocTrampoline(std::size_t a_size, bool a_trySKSEReserve = true) noexcept;
}
