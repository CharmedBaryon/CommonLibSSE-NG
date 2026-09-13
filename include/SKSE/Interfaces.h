#pragma once

#include "SKSE/Logger.h"
#include "SKSE/Version.h"

namespace RE
{
	class GFxMovieView;
	class GFxValue;
	class InventoryEntryData;

	namespace BSScript
	{
		namespace Internal
		{
			class VirtualMachine;
		}

		class IVirtualMachine;
	}
}

namespace SKSE
{
	using PluginHandle = std::uint32_t;

	struct PluginInfo
	{
		enum
		{
			kVersion = 1
		};

		std::uint32_t infoVersion;
		const char*   name;
		std::uint32_t version;
	};

	class SKSEDelayFunctorManager;
	class SKSEObjectRegistry;
	class SKSEPersistentObjectStorage;
	class TaskDelegate;
	class UIDelegate_v1;

	namespace Impl
	{
		struct SKSEInterface
		{
			std::uint32_t skseVersion;
			std::uint32_t runtimeVersion;
			std::uint32_t editorVersion;
			std::uint32_t isEditor;
			void* (*QueryInterface)(std::uint32_t);
			PluginHandle (*GetPluginHandle)();
			std::uint32_t (*GetReleaseIndex)();
			const void* (*GetPluginInfo)(const char*);
		};

		struct SKSEMessagingInterface
		{
			std::uint32_t interfaceVersion;
			bool (*RegisterListener)(PluginHandle, const char*, void*);
			bool (*Dispatch)(PluginHandle, std::uint32_t, void*, std::uint32_t, const char*);
			void* (*GetEventDispatcher)(std::uint32_t);
		};

		struct SKSEObjectInterface
		{
			std::uint32_t interfaceVersion;
			SKSEDelayFunctorManager& (*GetDelayFunctorManager)();
			SKSEObjectRegistry& (*GetObjectRegistry)();
			SKSEPersistentObjectStorage& (*GetPersistentObjectStorage)();
		};

		struct SKSEPapyrusInterface
		{
			std::uint32_t interfaceVersion;
			bool (*Register)(void*);
		};

		struct SKSEScaleformInterface
		{
			std::uint32_t interfaceVersion;
			bool (*Register)(const char*, void*);
			void (*RegisterForInventory)(void*);
		};

		struct SKSESerializationInterface
		{
			std::uint32_t version;
			void (*SetUniqueID)(PluginHandle, std::uint32_t);
			void (*SetRevertCallback)(PluginHandle, void*);
			void (*SetSaveCallback)(PluginHandle, void*);
			void (*SetLoadCallback)(PluginHandle, void*);
			void (*SetFormDeleteCallback)(PluginHandle, void*);
			bool (*WriteRecord)(std::uint32_t, std::uint32_t, const void*, std::uint32_t);
			bool (*OpenRecord)(std::uint32_t, std::uint32_t);
			bool (*WriteRecordData)(const void*, std::uint32_t);
			bool (*GetNextRecordInfo)(std::uint32_t*, std::uint32_t*, std::uint32_t*);
			std::uint32_t (*ReadRecordData)(void*, std::uint32_t);
			bool (*ResolveHandle)(std::uint64_t, std::uint64_t*);
			bool (*ResolveFormID)(std::uint32_t, std::uint32_t*);
		};

		struct SKSETaskInterface
		{
			std::uint32_t interfaceVersion;
			void (*AddTask)(void*);
			void (*AddUITask)(void*);
		};

		struct SKSETrampolineInterface
		{
			std::uint32_t interfaceVersion;
			void* (*AllocateFromBranchPool)(PluginHandle, std::size_t);
			void* (*AllocateFromLocalPool)(PluginHandle, std::size_t);
		};

		class TaskDelegate
		{
		public:
			virtual void Run() = 0;
			virtual void Dispose() = 0;
		};

		class UIDelegate_v1
		{
		public:
			virtual void Run() = 0;
			virtual void Dispose() = 0;
		};
	}

	class QueryInterface
	{
	protected:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSEInterface&>(*this);
		}

	private:
		[[nodiscard]] constexpr static REL::Version MakeVersion(std::uint32_t a_version) noexcept
		{
			return {
				static_cast<std::uint16_t>((a_version >> 8 * 3) & 0x0FF),
				static_cast<std::uint16_t>((a_version >> 8 * 2) & 0x0FF),
				static_cast<std::uint16_t>((a_version >> 8 / 2) & 0xFFF),
				static_cast<std::uint16_t>((a_version >> 8 * 0) & 0x00F)
			};
		}

	public:
		[[nodiscard]] std::uint32_t EditorVersion() const noexcept { return GetProxy().editorVersion; }
		[[nodiscard]] std::uint32_t SKSEVersion() const noexcept { return GetProxy().skseVersion; }
		[[nodiscard]] PluginHandle  GetPluginHandle() const { return GetProxy().GetPluginHandle(); }
		const PluginInfo*           GetPluginInfo(const char* a_name) const { return static_cast<const PluginInfo*>(GetProxy().GetPluginInfo(a_name)); }
		[[nodiscard]] std::uint32_t GetReleaseIndex() const { return GetProxy().GetReleaseIndex(); }
		[[nodiscard]] bool          IsEditor() const noexcept { return GetProxy().isEditor != 0; }
		[[nodiscard]] REL::Version  RuntimeVersion() const noexcept { return MakeVersion(GetProxy().runtimeVersion); }
	};

#ifdef ENABLE_SKYRIM_AE
	class PreLoadInterface :
		public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kTrampoline = 7
		};

		[[nodiscard]] void* QueryInterface(std::uint32_t a_id) const { return GetProxy().QueryInterface(a_id); }

		template <class T>
		T* QueryInterface(std::uint32_t a_id) const noexcept
		{
			auto result = static_cast<T*>(QueryInterface(a_id));
			if (result && result->Version() > T::kVersion)
				log::error("interface definition is out of date");

			return result;
		}
	};
#endif

	class LoadInterface :
		public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kScaleform = 1,
			kPapyrus = 2,
			kSerialization = 3,
			kTask = 4,
			kMessaging = 5,
			kObject = 6,
			kTrampoline = 7,
			kTotal
		};

		[[nodiscard]] void* QueryInterface(std::uint32_t a_id) const { return GetProxy().QueryInterface(a_id); }

		template <class T>
		T* QueryInterface(std::uint32_t a_id) const noexcept
		{
			auto result = static_cast<T*>(QueryInterface(a_id));
			if (result && result->Version() > T::kVersion)
				log::error("interface definition is out of date");

			return result;
		}
	};

	class ScaleformInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSEScaleformInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 2
		};

		using RegCallback = bool(RE::GFxMovieView* a_view, RE::GFxValue* a_root);
		using RegInvCallback = void(RE::GFxMovieView* a_view, RE::GFxValue* a_object, RE::InventoryEntryData* a_item);

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		bool Register(RegCallback* a_callback, const char* a_name) const;
		void Register(RegInvCallback* a_callback) const;
	};

	class SerializationInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSESerializationInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 4
		};

		using EventCallback = void(SerializationInterface* a_intfc);
		using FormDeleteCallback = void(RE::VMHandle a_handle);

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().version; }

		void SetUniqueID(std::uint32_t a_uid) const;
		void SetRevertCallback(EventCallback* a_callback) const;
		void SetSaveCallback(EventCallback* a_callback) const;
		void SetLoadCallback(EventCallback* a_callback) const;
		void SetFormDeleteCallback(FormDeleteCallback* a_callback) const;

		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const void* a_buf, std::uint32_t a_length) const;
		bool OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const;
		bool WriteRecordData(const void* a_buf, std::uint32_t a_length) const;
		bool WriteRecordDataEx(std::uint32_t& a_diff, const void* a_buf, std::uint32_t a_length) const;

		template <class T, std::enable_if_t<std::negation_v<std::is_pointer<T>>, int> = 0>
		inline bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T& a_buf) const
		{
			return WriteRecord(a_type, a_version, std::addressof(a_buf), sizeof(T));
		}

		template <class T, std::size_t N, std::enable_if_t<std::is_array_v<T>, int> = 0>
		inline bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T (&a_buf)[N]) const
		{
			return WriteRecord(a_type, a_version, std::addressof(a_buf), sizeof(T) * N);
		}

		template <class T, std::enable_if_t<std::negation_v<std::is_pointer<T>>, int> = 0>
		bool WriteRecordData(const T& a_buf) const
		{
			return WriteRecordData(std::addressof(a_buf), sizeof(T));
		}

		template <class T, std::enable_if_t<std::negation_v<std::is_pointer<T>>, int> = 0>
		bool WriteRecordDataEx(std::uint32_t& a_diff, const T& a_buf) const
		{
			return WriteRecordDataEx(a_diff, std::addressof(a_buf), sizeof(T));
		}

		template <class T, std::size_t N, std::enable_if_t<std::is_array_v<T>, int> = 0>
		bool WriteRecordData(const T (&a_buf)[N]) const
		{
			return WriteRecordData(std::addressof(a_buf), sizeof(T) * N);
		}

		template <class T, std::size_t N, std::enable_if_t<std::is_array_v<T>, int> = 0>
		bool WriteRecordDataEx(std::uint32_t& a_diff, const T (&a_buf)[N]) const
		{
			return WriteRecordDataEx(a_diff, std::addressof(a_buf), sizeof(T) * N);
		}

		bool GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_length) const;

		std::uint32_t ReadRecordData(void* a_buf, std::uint32_t a_length) const;
		std::uint32_t ReadRecordDataEx(std::uint32_t& a_diff, void* a_buf, std::uint32_t a_length) const;

		template <class T, std::enable_if_t<std::negation_v<std::is_pointer<T>>, int> = 0>
		std::uint32_t ReadRecordData(T& a_buf) const
		{
			return ReadRecordData(std::addressof(a_buf), sizeof(T));
		}

		template <class T, std::enable_if_t<std::negation_v<std::is_pointer<T>>, int> = 0>
		std::uint32_t ReadRecordDataEx(std::uint32_t& a_diff, T& a_buf) const
		{
			return ReadRecordDataEx(a_diff, std::addressof(a_buf), sizeof(T));
		}

		template <class T, std::size_t N, std::enable_if_t<std::is_array_v<T>, int> = 0>
		std::uint32_t ReadRecordData(T (&a_buf)[N]) const
		{
			return ReadRecordData(std::addressof(a_buf), sizeof(T) * N);
		}

		template <class T, std::size_t N, std::enable_if_t<std::is_array_v<T>, int> = 0>
		std::uint32_t ReadRecordDataEx(std::uint32_t& a_diff, T (&a_buf)[N]) const
		{
			return ReadRecordDataEx(a_diff, std::addressof(a_buf), sizeof(T) * N);
		}

		bool ResolveHandle(RE::VMHandle a_oldHandle, RE::VMHandle& a_newHandle) const
		{
			return GetProxy().ResolveHandle(a_oldHandle, &a_newHandle);
		}

		bool ResolveFormID(RE::FormID a_oldFormID, RE::FormID& a_newFormID) const
		{
			return GetProxy().ResolveFormID(a_oldFormID, &a_newFormID);
		}
	};

	class TaskInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSETaskInterface&>(*this);
		}

		class Task :
			public Impl::TaskDelegate
		{
		public:
			explicit Task(std::function<void()> a_task) noexcept :
				_impl(std::move(a_task))
			{}

			void Run() override { _impl(); }
			void Dispose() override { delete this; }

		private:
			std::function<void()> _impl;
		};

		class UITask :
			public Impl::UIDelegate_v1
		{
		public:
			explicit UITask(std::function<void()> a_task) noexcept :
				_impl(std::move(a_task))
			{}

			void Run() override { _impl(); }
			void Dispose() override { delete this; }

		private:
			std::function<void()> _impl;
		};

	public:
		enum
		{
			kVersion = 2
		};

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		void AddTask(TaskDelegate* a_task) const { GetProxy().AddTask(a_task); }
		void AddTask(std::function<void()> a_task) const { GetProxy().AddTask(new Task(std::move(a_task))); }
		void AddUITask(UIDelegate_v1* a_task) const { GetProxy().AddUITask(a_task); }
		void AddUITask(std::function<void()> a_task) const { GetProxy().AddUITask(new UITask(std::move(a_task))); }
	};

	class PapyrusInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSEPapyrusInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 1
		};

		using RegFunction1 = bool(RE::BSScript::Internal::VirtualMachine* a_vm);
		using RegFunction2 = bool(RE::BSScript::IVirtualMachine* a_vm);

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		template <class Last>
		bool Register(Last a_last) const
		{
			return Register_Impl(a_last);
		}

		template <class First, class... Rest>
		bool Register(First a_first, Rest... a_rest) const
		{
			return Register_Impl(a_first) && Register(a_rest...);
		}

	private:
		bool Register_Impl(RegFunction1* a_fn) const;
		bool Register_Impl(RegFunction2* a_fn) const;
	};

	class MessagingInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSEMessagingInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 2
		};

		enum : std::uint32_t
		{
			kPostLoad,
			kPostPostLoad,
			kPreLoadGame,
			kPostLoadGame,
			kSaveGame,
			kDeleteGame,
			kInputLoaded,
			kNewGame,
			kDataLoaded,

			kTotal
		};

		enum class Dispatcher : std::uint32_t
		{
			kModEvent = 0,
			kCameraEvent,
			kCrosshairEvent,
			kActionEvent,
			kNiNodeUpdateEvent,

			kTotal
		};

		struct Message
		{
			const char*   sender;
			std::uint32_t type;
			std::uint32_t dataLen;
			void*         data;
		};

		using EventCallback = void(Message* a_msg);

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		bool Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const;
		bool RegisterListener(EventCallback* a_handler) const { return RegisterListener("SKSE", a_handler); }
		bool RegisterListener(const char* a_sender, EventCallback* a_callback) const;

		[[nodiscard]] void* GetEventDispatcher(Dispatcher a_dispatcherID) const
		{
			return GetProxy().GetEventDispatcher(std::to_underlying(a_dispatcherID));
		}
	};

	class ObjectInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSEObjectInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t                Version() const noexcept { return GetProxy().interfaceVersion; }
		[[nodiscard]] SKSEDelayFunctorManager&     GetDelayFunctorManager() const { return GetProxy().GetDelayFunctorManager(); }
		[[nodiscard]] SKSEObjectRegistry&          GetObjectRegistry() const { return GetProxy().GetObjectRegistry(); }
		[[nodiscard]] SKSEPersistentObjectStorage& GetPersistentObjectStorage() const { return GetProxy().GetPersistentObjectStorage(); }
	};

	class TrampolineInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::SKSETrampolineInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }
		[[nodiscard]] void*         AllocateFromBranchPool(std::size_t a_size) const;
		[[nodiscard]] void*         AllocateFromLocalPool(std::size_t a_size) const;
	};

	struct PluginVersionData
	{
	public:
		enum
		{
			kVersion = 1,
		};

		enum
		{
			kVersionIndependent_AddressLibraryPostAE = 1 << 0,
			kVersionIndependent_Signatures = 1 << 1,
			kVersionIndependent_StructsPost629 = 1 << 2,
		};

		enum
		{
			kVersionIndependentEx_NoStructUse = 1 << 0,
			kVersionIndependentEx_AddressLibraryV5 = 1 << 1,
		};

		constexpr void PluginVersion(REL::Version a_version) noexcept { pluginVersion = a_version.pack(); }

		[[nodiscard]] constexpr REL::Version GetPluginVersion() const noexcept { return REL::Version::unpack(pluginVersion); }

		constexpr void PluginName(std::string_view a_plugin) noexcept { SetCharBuffer(a_plugin, std::span{ pluginName }); }

		[[nodiscard]] constexpr std::string_view GetPluginName() const noexcept { return std::string_view{ pluginName }; }

		constexpr void AuthorName(std::string_view a_name) noexcept { SetCharBuffer(a_name, std::span{ author }); }

		[[nodiscard]] constexpr std::string_view GetAuthorName() const noexcept { return std::string_view{ author }; }

		constexpr void AuthorEmail(std::string_view a_email) noexcept { SetCharBuffer(a_email, std::span{ supportEmail }); }

		[[nodiscard]] constexpr std::string_view GetAuthorEmail() const noexcept { return std::string_view{ supportEmail }; }

		constexpr void UsesAddressLibrary() noexcept { versionIndependence |= kVersionIndependent_AddressLibraryPostAE; }
		constexpr void UsesSigScanning() noexcept { versionIndependence |= kVersionIndependent_Signatures; }
		constexpr void UsesUpdatedStructs() noexcept { versionIndependence |= kVersionIndependent_StructsPost629; }

		constexpr void UsesNoStructs() noexcept { versionIndependenceEx |= kVersionIndependentEx_NoStructUse; }

		constexpr void MinimumRequiredXSEVersion(REL::Version a_version) noexcept { xseMinimum = a_version.pack(); }

		constexpr void CompatibleVersions(std::initializer_list<REL::Version> a_versions) noexcept
		{
			assert(a_versions.size() < std::size(compatibleVersions) - 1);
			std::transform(
				a_versions.begin(),
				a_versions.end(),
				std::begin(compatibleVersions),
				[](const REL::Version& a_version) noexcept { return a_version.pack(); });
		}

		[[nodiscard]] static const PluginVersionData* GetSingleton() noexcept;

		const std::uint32_t dataVersion{ kVersion };
		std::uint32_t       pluginVersion = 0;
		char                pluginName[256] = {};
		char                author[256] = {};
		char                supportEmail[252] = {};
		std::uint32_t       versionIndependenceEx = kVersionIndependentEx_AddressLibraryV5;
		std::uint32_t       versionIndependence = 0;
		std::uint32_t       compatibleVersions[16] = {};
		std::uint32_t       xseMinimum = 0;

	private:
		static constexpr void SetCharBuffer(
			std::string_view a_src,
			std::span<char>  a_dst) noexcept
		{
			assert(a_src.size() < a_dst.size());
			std::fill(a_dst.begin(), a_dst.end(), '\0');
			std::copy(a_src.begin(), a_src.end(), a_dst.begin());
		}
	};
	STATIC_ASSERT_OFFSET(PluginVersionData, dataVersion, 0x000);
	STATIC_ASSERT_OFFSET(PluginVersionData, pluginVersion, 0x004);
	STATIC_ASSERT_OFFSET(PluginVersionData, pluginName, 0x008);
	STATIC_ASSERT_OFFSET(PluginVersionData, author, 0x108);
	STATIC_ASSERT_OFFSET(PluginVersionData, supportEmail, 0x208);
	STATIC_ASSERT_OFFSET(PluginVersionData, versionIndependenceEx, 0x304);
	STATIC_ASSERT_OFFSET(PluginVersionData, versionIndependence, 0x308);
	STATIC_ASSERT_OFFSET(PluginVersionData, compatibleVersions, 0x30C);
	STATIC_ASSERT_OFFSET(PluginVersionData, xseMinimum, 0x34C);
	static_assert(sizeof(PluginVersionData) == 0x350);

	enum class VersionIndependence
	{
		AddressLibraryPre1_6_629,
		AddressLibraryPost1_6_629,
		AddressLibrary,
		SignatureScanning
	};

	enum class StructCompatibility : std::uint32_t
	{
		Dependent = PluginVersionData::kVersionIndependentEx_AddressLibraryV5,
		Independent = PluginVersionData::kVersionIndependentEx_AddressLibraryV5 | PluginVersionData::kVersionIndependentEx_NoStructUse
	};

	struct PluginDeclaration
	{
	public:
		template <std::size_t N>
		class String
		{
		public:
			constexpr String() = default;

			constexpr String(std::string_view a_string) noexcept
			{
				std::span<char> buffer(_buffer, N);
				std::fill(buffer.begin(), buffer.end(), '\0');
				std::copy(a_string.begin(), a_string.end(), buffer.begin());
			}

			constexpr String(const char* a_string) noexcept
			{
				std::string_view string(a_string);
				std::span<char>  buffer(_buffer, N);
				std::fill(buffer.begin(), buffer.end(), '\0');
				std::copy(string.begin(), string.end(), buffer.begin());
			}

			[[nodiscard]] constexpr operator const char*() const noexcept
			{
				return _buffer;
			}

			[[nodiscard]] constexpr operator std::string_view() const noexcept
			{
				return _buffer;
			}

		private:
			char _buffer[N]{};
		};

		class VersionNumber
		{
		public:
			using value_type = typename REL::Version::value_type;

			constexpr VersionNumber(value_type a_major = 1, value_type a_minor = 0, value_type a_patch = 0,
				value_type a_build = 0) noexcept :
				_packed(REL::Version{ a_major, a_minor, a_patch, a_build }.pack())
			{}

			constexpr VersionNumber(REL::Version a_version) noexcept :
				_packed(a_version.pack()) {}

			constexpr VersionNumber& operator=(REL::Version a_version) noexcept
			{
				_packed = a_version.pack();
				return *this;
			}

			[[nodiscard]] constexpr operator REL::Version() const noexcept
			{
				return REL::Version::unpack(_packed);
			}

			[[nodiscard]] constexpr explicit operator std::uint32_t() const noexcept
			{
				return _packed;
			}

		private:
			std::uint32_t _packed{};
		};

		class RuntimeCompatibility
		{
		public:
			static constexpr std::size_t MaxCompatibleVersions = 16;

			constexpr RuntimeCompatibility() = default;

			template <class... Args>
				requires(sizeof...(Args) <= MaxCompatibleVersions && (std::convertible_to<Args, VersionNumber> && ...))
			constexpr RuntimeCompatibility(Args... a_compatibleVersions) noexcept :
				_addressLibrary(false), _compatibleVersions({ VersionNumber(a_compatibleVersions)... })
			{
			}

			constexpr RuntimeCompatibility(VersionIndependence a_versionIndependence, bool a_requiresPost629Structs = false) noexcept :
				_addressLibrary(a_versionIndependence == VersionIndependence::AddressLibrary),
				_signatureScanning(a_versionIndependence == VersionIndependence::SignatureScanning),
				_structsPost629(a_requiresPost629Structs) {}

			[[nodiscard]] constexpr bool UsesAddressLibrary() const noexcept
			{
				return _addressLibrary;
			}

			[[nodiscard]] constexpr bool UsesSignatureScanning() const noexcept
			{
				return _signatureScanning;
			}

			[[nodiscard]] constexpr bool Targets629Structs() const noexcept
			{
				return _structsPost629;
			}

			[[nodiscard]] constexpr bool IsVersionIndependent() const noexcept
			{
				return UsesAddressLibrary() || UsesSignatureScanning();
			}

			[[nodiscard]] constexpr std::array<VersionNumber, 16> GetCompatibleRuntimeVersions() const noexcept
			{
				return _compatibleVersions;
			}

		private:
			const bool                           _addressLibrary: 1 = true;
			const bool                           _signatureScanning: 1 = false;
			const bool                           _structsPost629: 1 = false;
			[[maybe_unused]] const std::uint8_t  _pad0: 5 = 0;
			[[maybe_unused]] const std::uint8_t  _pad1{ 0 };
			[[maybe_unused]] const std::uint16_t _pad2{ 0 };
			std::array<VersionNumber, 16>        _compatibleVersions{};
		};
		static_assert(sizeof(RuntimeCompatibility) == 0x44);

		struct PluginDeclarationInfo
		{
			/**
		     * The version number of the plugin.
		     */
			const VersionNumber Version{ 1, 0, 0, 0 };

			/**
		     * The plugin's name (maximum of 256 characters).
		     */
			const String<256> Name{};

			/**
		     * The name of the plugin's author (maximum of 256 characters).
		     */
			const String<256> Author{};

			/**
		     * A support email address for the plugin (maximum of 256 characters).
		     */
			const String<252> SupportEmail{};

			/**
			 * Defines the compatibility with structure layout of the plugin.
			 *
			 * For most of modern CommonLibSSE-era plugin development structs in Skyrim have remained
			 * unchanged. In AE 1.6.629, however, the layout of some structs changed. If this is flagged
			 * as independent, then SKSE will let your plugin work with runtimes before and after this
			 * change. CommonLibSSE NG defaults to flagging a plugin independent because it supports
			 * both struct layouts in a single plugin. If your plugin has any RE'd structs that have
			 * changed you should override this.
			 */
			const StructCompatibility StructCompatibility{ StructCompatibility::Independent };

			/**
		     * A definition of the runtime compatibility for the plugin.
		     *
		     * <p>
		     * This can be either an indicator of how version-independence is achieved (either through using Address Library
		     * or signature scanning, indicated with a value from <code>SKSE::VersionIndependence</code>, or a list of up to
		     * 16 version numbers of Skyrim runtimes that are supported by this plugin.
		     * </p>
		     */
			const RuntimeCompatibility RuntimeCompatibility{};

			/**
		     * The minimum SKSE version required for the plugin; this should almost always be left <code>0</code>.
		     */
			const VersionNumber MinimumSKSEVersion{ 0 };
		};
		static_assert(offsetof(PluginDeclarationInfo, Version) == 0x000);
		static_assert(offsetof(PluginDeclarationInfo, Name) == 0x004);
		static_assert(offsetof(PluginDeclarationInfo, Author) == 0x104);
		static_assert(offsetof(PluginDeclarationInfo, SupportEmail) == 0x204);
		static_assert(offsetof(PluginDeclarationInfo, StructCompatibility) == 0x300);
		static_assert(offsetof(PluginDeclarationInfo, RuntimeCompatibility) == 0x304);
		static_assert(offsetof(PluginDeclarationInfo, MinimumSKSEVersion) == 0x348);

		constexpr PluginDeclaration(PluginDeclarationInfo info) noexcept :
			_data(std::move(info)) {}

		[[nodiscard]] constexpr REL::Version GetVersion() const noexcept
		{
			return _data.Version;
		}

		[[nodiscard]] constexpr std::string_view GetName() const noexcept
		{
			return _data.Name;
		}

		[[nodiscard]] constexpr std::string_view GetAuthor() const noexcept
		{
			return _data.Author;
		}

		[[nodiscard]] constexpr std::string_view GetSupportEmail() const noexcept
		{
			return _data.SupportEmail;
		}

		[[nodiscard]] constexpr StructCompatibility GetStructCompatibility() const noexcept
		{
			return _data.StructCompatibility;
		}

		[[nodiscard]] constexpr const RuntimeCompatibility& GetRuntimeCompatibility() const noexcept
		{
			return _data.RuntimeCompatibility;
		}

		[[nodiscard]] constexpr REL::Version GetMinimumSKSEVersion() const noexcept
		{
			return _data.MinimumSKSEVersion;
		}

		[[nodiscard]] static const PluginDeclaration* GetSingleton() noexcept;

	private:
		enum
		{
			kVersion = 1,
		};

		[[maybe_unused]] const std::uint32_t         _dataVersion{ kVersion };
		[[maybe_unused]] const PluginDeclarationInfo _data;
	};
	static_assert(sizeof(PluginDeclaration) == 0x350);
}

#define SKSE_EXPORT extern "C" [[maybe_unused]] __declspec(dllexport)
#ifdef ENABLE_SKYRIM_AE
#	define SKSE_PLUGIN_PRELOAD(...) SKSE_EXPORT bool SKSEPlugin_Preload(__VA_ARGS__)
#endif
#define SKSE_PLUGIN_LOAD(...) SKSE_EXPORT bool SKSEPlugin_Load(__VA_ARGS__)
#define SKSE_PLUGIN_QUERY(...) SKSE_EXPORT bool SKSEPlugin_Query(__VA_ARGS__)
#define SKSE_PLUGIN_VERSION SKSE_EXPORT constinit SKSE::PluginVersionData SKSEPlugin_Version

#define SKSEPluginInfo(...)                                                                                                   \
	SKSE_EXPORT constinit ::SKSE::PluginDeclaration SKSEPlugin_Version({ __VA_ARGS__ });                                      \
	SKSE_EXPORT bool                                SKSEPlugin_Query(::SKSE::QueryInterface*, ::SKSE::PluginInfo* pluginInfo) \
	{                                                                                                                         \
		pluginInfo->infoVersion = ::SKSE::PluginInfo::kVersion;                                                               \
		pluginInfo->name = SKSEPlugin_Version.GetName().data();                                                               \
		pluginInfo->version = static_cast<std::uint32_t>(SKSEPlugin_Version.GetVersion().pack());                             \
		return true;                                                                                                          \
	}

// DEPRECATED
#define SKSEPluginLoad SKSE_PLUGIN_LOAD
// DEPRECATED
#define SKSEPluginVersion SKSE_PLUGIN_VERSION
// DEPRECATED
#define SKSEPluginQuery SKSE_PLUGIN_QUERY
