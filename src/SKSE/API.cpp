#include "SKSE/API.h"

#include "SKSE/Interfaces.h"
#include "SKSE/Logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

namespace SKSE
{
	namespace Impl
	{
		class API
		{
		public:
			[[nodiscard]] static API* GetSingleton()
			{
				static API singleton;
				return std::addressof(singleton);
			}

			void Init(InitInfo, const SKSE::QueryInterface* a_intfc);
			void InitLog();
			void InitTrampoline();

			InitInfo info;

			std::string  pluginName{};
			std::string  pluginAuthor{};
			REL::Version pluginVersion{};

			std::uint32_t                           skseVersion{};
			PluginHandle                            pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t                           releaseIndex{ 0 };
			std::function<const void*(const char*)> pluginInfoAccessor;

			ScaleformInterface*     scaleformInterface{ nullptr };
			PapyrusInterface*       papyrusInterface{ nullptr };
			SerializationInterface* serializationInterface{ nullptr };
			TaskInterface*          taskInterface{ nullptr };
			MessagingInterface*     messagingInterface{ nullptr };
			ObjectInterface*        objectInterface{ nullptr };
			TrampolineInterface*    trampolineInterface{ nullptr };

			SKSEDelayFunctorManager*     delayFunctorManager{ nullptr };
			SKSEObjectRegistry*          objectRegistry{ nullptr };
			SKSEPersistentObjectStorage* persistentObjectStorage{ nullptr };

			template <class T>
			[[nodiscard]] RE::BSTEventSource<T>* GetEventDispatcher(MessagingInterface::Dispatcher a_id) const
			{
				assert(messagingInterface);
				return static_cast<RE::BSTEventSource<T>*>(messagingInterface->GetEventDispatcher(a_id));
			}

			RE::BSTEventSource<ModCallbackEvent>*  modCallbackEventSource{ nullptr };
			RE::BSTEventSource<CameraEvent>*       cameraEventSource{ nullptr };
			RE::BSTEventSource<CrosshairRefEvent>* crosshairRefEventSource{ nullptr };
			RE::BSTEventSource<ActionEvent>*       actionEventSource{ nullptr };
			RE::BSTEventSource<NiNodeUpdateEvent>* niNodeUpdateEventSource{ nullptr };

			std::mutex                         apiLock;
			std::vector<std::function<void()>> apiInitRegs;
			bool                               apiInit{ false };
		};

		void API::Init(InitInfo a_info, const SKSE::QueryInterface* a_intfc)
		{
			info = a_info;

			static std::once_flag once;
			std::call_once(once, [&]() {
#ifdef ENABLE_SKYRIM_AE
				if (const auto data = PluginVersionData::GetSingleton()) {
					pluginName = data->GetPluginName();
					pluginAuthor = data->GetAuthorName();
					pluginVersion = data->GetPluginVersion();
				} else {
#endif
					std::vector<char> buf(REX::W32::MAX_PATH, '\0');
					const auto        size = REX::W32::GetModuleFileNameA(REX::W32::GetCurrentModule(), buf.data(), REX::W32::MAX_PATH);
					if (size) {
						std::filesystem::path p(buf.begin(), buf.begin() + size);
						pluginName = p.stem().string();
					}
#ifdef ENABLE_SKYRIM_AE
				}
#endif

				skseVersion = a_intfc->SKSEVersion();
				pluginHandle = a_intfc->GetPluginHandle();
				releaseIndex = a_intfc->GetReleaseIndex();
				pluginInfoAccessor = reinterpret_cast<const Impl::SKSEInterface*>(a_intfc)->GetPluginInfo;
			});
		}

		void API::InitLog()
		{
			if (info.log) {
				static std::once_flag once;
				std::call_once(once, [&]() {
					auto path = log::log_directory();
					if (!path)
						return;

					*path /= std::format("{}.log", info.logName ? info.logName : SKSE::GetPluginName());

					std::vector<spdlog::sink_ptr> sinks{
						std::make_shared<spdlog::sinks::msvc_sink_mt>()
					};

					if (info.logRotate > 0) {
						constexpr auto maxSize = std::numeric_limits<std::size_t>::max();
						sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path->string(), maxSize, info.logRotate, true));
					} else {
						sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
					}

					auto logger = std::make_shared<spdlog::logger>("global", sinks.begin(), sinks.end());
					logger->set_level(static_cast<spdlog::level::level_enum>(info.logLevel));
					logger->flush_on(static_cast<spdlog::level::level_enum>(info.logLevel));

					spdlog::set_default_logger(std::move(logger));
					spdlog::set_pattern(info.logPattern ? info.logPattern : "[%T.%e] [%=5t] [%L] %v");

#ifdef ENABLE_SKYRIM_AE
					log::info("{} v{}", GetPluginName(), GetPluginVersion());
#endif
				});
			}
		}

		void API::InitTrampoline()
		{
			if (info.trampoline) {
				static std::once_flag once;
				std::call_once(once, [&]() {
					auto& trampoline = SKSE::GetTrampoline();
					if (const auto intfc = GetTrampolineInterface()) {
						if (const auto mem = intfc->AllocateFromBranchPool(info.trampolineSize))
							trampoline.set_trampoline(mem, info.trampolineSize);
						else
							trampoline.create(info.trampolineSize);
					}
				});
			}
		}
	}

#ifdef ENABLE_SKYRIM_AE
	void Init(const PreLoadInterface* a_intfc, InitInfo a_info) noexcept
	{
		static std::once_flag once;
		std::call_once(once, [&]() {
			auto api = Impl::API::GetSingleton();
			api->Init(a_info, a_intfc);
			api->InitLog();

			api->trampolineInterface = a_intfc->QueryInterface<TrampolineInterface>(PreLoadInterface::kTrampoline);

			api->InitTrampoline();
		});
	}
#endif

	void Init(const LoadInterface* a_intfc, InitInfo a_info) noexcept
	{
		static std::once_flag once;
		std::call_once(once, [&]() {
			auto api = Impl::API::GetSingleton();
			api->Init(a_info, a_intfc);
			api->InitLog();

			api->scaleformInterface = a_intfc->QueryInterface<ScaleformInterface>(LoadInterface::kScaleform);
			api->papyrusInterface = a_intfc->QueryInterface<PapyrusInterface>(LoadInterface::kPapyrus);
			api->serializationInterface = a_intfc->QueryInterface<SerializationInterface>(LoadInterface::kSerialization);
			api->taskInterface = a_intfc->QueryInterface<TaskInterface>(LoadInterface::kTask);
			api->trampolineInterface = a_intfc->QueryInterface<TrampolineInterface>(LoadInterface::kTrampoline);

			api->messagingInterface = a_intfc->QueryInterface<MessagingInterface>(LoadInterface::kMessaging);
			if (api->messagingInterface) {
				api->modCallbackEventSource = api->GetEventDispatcher<ModCallbackEvent>(MessagingInterface::Dispatcher::kModEvent);
				api->cameraEventSource = api->GetEventDispatcher<CameraEvent>(MessagingInterface::Dispatcher::kCameraEvent);
				api->crosshairRefEventSource = api->GetEventDispatcher<CrosshairRefEvent>(MessagingInterface::Dispatcher::kCrosshairEvent);
				api->actionEventSource = api->GetEventDispatcher<ActionEvent>(MessagingInterface::Dispatcher::kActionEvent);
				api->niNodeUpdateEventSource = api->GetEventDispatcher<NiNodeUpdateEvent>(MessagingInterface::Dispatcher::kNiNodeUpdateEvent);
			}

			api->objectInterface = a_intfc->QueryInterface<ObjectInterface>(LoadInterface::kObject);
			if (api->objectInterface) {
				api->delayFunctorManager = std::addressof(api->objectInterface->GetDelayFunctorManager());
				api->objectRegistry = std::addressof(api->objectInterface->GetObjectRegistry());
				api->persistentObjectStorage = std::addressof(api->objectInterface->GetPersistentObjectStorage());
			}

			const std::scoped_lock lock{ api->apiLock };
			if (!api->apiInit) {
				api->apiInit = true;
				auto& regs = api->apiInitRegs;
				for (const auto& reg : regs) {
					reg();
				}
				regs.clear();
				regs.shrink_to_fit();
			}

			api->InitTrampoline();
		});
	}

	void RegisterForAPIInitEvent(std::function<void()> a_fn)
	{
		auto                   api = Impl::API::GetSingleton();
		const std::scoped_lock lock{ api->apiLock };
		if (!api->apiInit) {
			api->apiInitRegs.push_back(a_fn);
			return;
		}

		a_fn();
	}

	std::uint32_t GetSKSEVersion() noexcept
	{
		return Impl::API::GetSingleton()->skseVersion;
	}

	std::string_view GetPluginName() noexcept
	{
		return Impl::API::GetSingleton()->pluginName;
	}

	std::string_view GetPluginAuthor() noexcept
	{
		return Impl::API::GetSingleton()->pluginAuthor;
	}

	REL::Version GetPluginVersion() noexcept
	{
		return Impl::API::GetSingleton()->pluginVersion;
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return Impl::API::GetSingleton()->pluginHandle;
	}

	const PluginInfo* GetPluginInfo(std::string_view a_plugin) noexcept
	{
		if (const auto& accessor = Impl::API::GetSingleton()->pluginInfoAccessor) {
			if (const auto result = accessor(a_plugin.data())) {
				return static_cast<const PluginInfo*>(result);
			}
		}

		log::error("failed to get plugin info for {}", a_plugin);
		return nullptr;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return Impl::API::GetSingleton()->releaseIndex;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return Impl::API::GetSingleton()->messagingInterface;
	}

	const ScaleformInterface* GetScaleformInterface() noexcept
	{
		return Impl::API::GetSingleton()->scaleformInterface;
	}

	const PapyrusInterface* GetPapyrusInterface() noexcept
	{
		return Impl::API::GetSingleton()->papyrusInterface;
	}

	const SerializationInterface* GetSerializationInterface() noexcept
	{
		return Impl::API::GetSingleton()->serializationInterface;
	}

	const TaskInterface* GetTaskInterface() noexcept
	{
		return Impl::API::GetSingleton()->taskInterface;
	}

	const ObjectInterface* GetObjectInterface() noexcept
	{
		return Impl::API::GetSingleton()->objectInterface;
	}

	const TrampolineInterface* GetTrampolineInterface() noexcept
	{
		return Impl::API::GetSingleton()->trampolineInterface;
	}

	const SKSEDelayFunctorManager* GetDelayFunctorManager() noexcept
	{
		return Impl::API::GetSingleton()->delayFunctorManager;
	}

	const SKSEObjectRegistry* GetObjectRegistry() noexcept
	{
		return Impl::API::GetSingleton()->objectRegistry;
	}

	const SKSEPersistentObjectStorage* GetPersistentObjectStorage() noexcept
	{
		return Impl::API::GetSingleton()->persistentObjectStorage;
	}

	RE::BSTEventSource<ModCallbackEvent>* GetModCallbackEventSource() noexcept
	{
		return Impl::API::GetSingleton()->modCallbackEventSource;
	}

	RE::BSTEventSource<CameraEvent>* GetCameraEventSource() noexcept
	{
		return Impl::API::GetSingleton()->cameraEventSource;
	}

	RE::BSTEventSource<CrosshairRefEvent>* GetCrosshairRefEventSource() noexcept
	{
		return Impl::API::GetSingleton()->crosshairRefEventSource;
	}

	RE::BSTEventSource<ActionEvent>* GetActionEventSource() noexcept
	{
		return Impl::API::GetSingleton()->actionEventSource;
	}

	RE::BSTEventSource<NiNodeUpdateEvent>* GetNiNodeUpdateEventSource() noexcept
	{
		return Impl::API::GetSingleton()->niNodeUpdateEventSource;
	}
}

namespace SKSE
{
	void Init(const LoadInterface* a_intfc, const bool a_log) noexcept
	{
		Init(a_intfc, { .log = a_log });
	}

	void AllocTrampoline(std::size_t a_size, bool) noexcept
	{
		auto api = Impl::API::GetSingleton();
		api->info.trampoline = true;
		api->info.trampolineSize = a_size;
		api->InitTrampoline();
	}
}
