#pragma once

#include "REL/Version.h"

#include "REX/W32/ADVAPI32.h"
#include "REX/W32/KERNEL32.h"

namespace REL
{
	class Segment
	{
	public:
		enum Name : std::size_t
		{
			textx,
			idata,
			rdata,
			data,
			pdata,
			tls,
			textw,
			gfids,
			total
		};

		Segment() noexcept = default;

		Segment(std::uintptr_t a_proxyBase, std::uintptr_t a_address, std::uintptr_t a_size) noexcept :
			_proxyBase(a_proxyBase),
			_address(a_address),
			_size(a_size)
		{}

		[[nodiscard]] std::uintptr_t address() const noexcept { return _address; }

		[[nodiscard]] std::size_t offset() const noexcept { return address() - _proxyBase; }

		[[nodiscard]] std::size_t size() const noexcept { return _size; }

		[[nodiscard]] void* pointer() const noexcept { return reinterpret_cast<void*>(address()); }

		template <class T>
		[[nodiscard]] T* pointer() const noexcept
		{
			return static_cast<T*>(pointer());
		}

	private:
		friend class Module;

		std::uintptr_t _proxyBase{ 0 };
		std::uintptr_t _address{ 0 };
		std::size_t    _size{ 0 };
	};

	class Module
	{
	public:
		/**
		 * Identifies a Skyrim runtime.
		 */
		enum class Runtime : uint8_t
		{
			Unknown = 0,

			/**
			 * The Skyrim runtime is a post-Anniversary Edition Skyrim SE release (version 1.6.x and later).
			 */
			AE = 1 << 0,

			/**
			 * The Skyrim runtime is a pre-Anniversary Edition Skyrim SE release (version 1.5.97 and prior).
			 */
			SE = 1 << 1,

			/**
			 * The Skyrim runtime is Skyrim VR.
			 */
			VR = 1 << 2
		};

		[[nodiscard]] static Module& get()
		{
			if (_initialized.load(std::memory_order_acquire)) {
				return _instance;
			}
			std::unique_lock lock(_initLock);
			if (!_initialized.load(std::memory_order_relaxed)) {
				_instance.init();
				_initialized.store(true, std::memory_order_release);
			}
			return _instance;
		}

#ifdef ENABLE_COMMONLIBSSE_TESTING
		/**
		 * Forcibly set the singleton <code>Module</code> instance to a specific executable file.
		 *
		 * <p>
		 * This function should only be used in a unit testing environment, where there is no Skyrim process hosting
		 * the SKSE plugin. It is not thread-safe and assumes it will be run synchronously with serial test execution.
		 * </p>
		 *
		 * @param a_filePath The path to the executable to use a Skyrim executable.
		 * @return <code>true</code> if the module injection works; <code>false</code> otherwise.
		 */
		static bool inject(std::wstring_view a_filePath)
		{
			_instance.clear();
			_initialized = true;
			return _instance.init(a_filePath);
		}

		/**
		 * Forcibly set the singleton <code>Module</code> instance to an installed Skyrim executable.
		 *
		 * <p>
		 * This overload accepts only a <code>Runtime</code> value, and based on that value attempts to find the
		 * executable, using the Windows registry to find an installed copy of Skyrim of the given runtime. Using
		 * <code>Runtime::Unknown</code> causes an attempt to discover Skyrim Special Edition first, and if that fails,
		 * attempts to discover Skyrim VR.
		 * </p>
		 *
		 * <p>
		 * This function should only be used in a unit testing environment, where there is no Skyrim process hosting
		 * the SKSE plugin. It is not thread-safe and assumes it will be run synchronously with serial test execution.
		 * </p>
		 *
		 * @param a_runtime The type of Skyrim runtime to inject.
		 */
		static bool inject(Runtime a_runtime = Runtime::Unknown)
		{
			if (a_runtime == Runtime::Unknown) {
				return inject(Runtime::SE) || inject(Runtime::VR);
			}

			constexpr std::size_t bufferSize = 4096;  // Max NTFS path length.
			const wchar_t*        subKey =
                a_runtime == Runtime::VR ?
						   LR"(SOFTWARE\Bethesda Softworks\Skyrim VR)" :
						   LR"(SOFTWARE\Bethesda Softworks\Skyrim Special Edition)";
			std::uint32_t length = bufferSize * sizeof(wchar_t);
			std::uint8_t  value[bufferSize];
			if (REX::W32::RegGetValueW(REX::W32::HKEY_LOCAL_MACHINE, subKey, L"Installed Path", 0x20002u, nullptr, value, &length) != 0) {
				return false;
			}
			std::filesystem::path installPath(reinterpret_cast<wchar_t*>(value));
			installPath /= a_runtime == Runtime::VR ? L"SkyrimVR.exe" : L"SkyrimSE.exe";
			return inject(installPath.c_str());
		}

		static bool mock(
			REL::Version                               a_version,
			Runtime                                    a_runtime = Runtime::Unknown,
			std::wstring_view                          a_filename = L"SkyrimSE.exe"sv,
			std::uintptr_t                             a_base = 0,
			std::array<std::uintptr_t, Segment::total> a_segmentSizes = { 0x1603000, 0, 0x8ee000, 0x1887000, 0x15c000, 0x3000, 0x2000, 0x1000 })
		{
			_instance.clear();
			_initialized = true;

			if (a_filename.empty() || !a_segmentSizes[0]) {
				return false;
			}

			_instance._filename = _instance._filePath = a_filename.data();
			_instance._version = a_version;
			if (a_runtime == Runtime::Unknown) {
				// Minor version 4 = VR, 5 = SE, 6+ = AE (see load_version()).
				if (a_version[1] == 4) {
					_instance._runtime = Runtime::VR;
				} else if (a_version[1] >= 6) {
					_instance._runtime = Runtime::AE;
				} else {
					_instance._runtime = Runtime::SE;
				}
			} else {
				_instance._runtime = a_runtime;
			}
			_instance._base = a_base;

			auto currentAddress = a_base + 0x1000;
			for (std::size_t i = 0; i < a_segmentSizes.size(); ++i) {
				auto& segment = _instance._segments[i];
				segment._size = a_segmentSizes[i];
				if (segment._size) {
					segment._proxyBase = a_base;
					segment._address = (currentAddress += segment._size);
				}
			}

			return true;
		}
#endif

		static void reset()
		{
			_initialized = false;
			_instance.clear();
		}

		[[nodiscard]] std::uintptr_t base() const noexcept { return _base; }

		[[nodiscard]] stl::zwstring filename() const noexcept { return _filename; }

		[[nodiscard]] stl::zwstring filePath() const noexcept { return _filePath; }

		[[nodiscard]] Version version() const noexcept { return _version; }

		[[nodiscard]] Segment segment(Segment::Name a_segment) const noexcept { return _segments[a_segment]; }

		[[nodiscard]] REX::W32::HMODULE pointer() const noexcept { return reinterpret_cast<REX::W32::HMODULE>(base()); }

		template <class T>
		[[nodiscard]] T* pointer() const noexcept
		{
			return static_cast<T*>(pointer());
		}

		/**
		 * Get the type of runtime the currently-loaded Skyrim module is.
		 */
		[[nodiscard]] static SKYRIM_REL Runtime GetRuntime() noexcept
		{
#if (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
			return Runtime::SE;
#elif (!defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR))
			return Runtime::AE;
#elif (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
			return Runtime::VR;
#else
			return get()._runtime;
#endif
		}

		/**
		 * Returns whether the current Skyrim runtime is a post-Anniversary Edition Skyrim SE release.
		 */
		[[nodiscard]] static SKYRIM_REL bool IsAE() noexcept
		{
			return GetRuntime() == Runtime::AE;
		}

		/**
		 * Returns whether the current Skyrim runtime is an Anniversary Edition release at or above the given version.
		 */
		[[nodiscard]] static SKYRIM_REL bool IsAtLeast(Version a_version) noexcept
		{
			return IsAE() && get().version() >= a_version;
		}

		/**
		 * Returns whether the current Skyrim runtime is a pre-Anniversary Edition Skyrim SE release.
		 */
		[[nodiscard]] static SKYRIM_REL bool IsSE() noexcept
		{
			return GetRuntime() == Runtime::SE;
		}

		/**
		 * Returns whether the current Skyrim runtime is a Skyrim VR release.
		 */
		[[nodiscard]] static SKYRIM_REL_VR bool IsVR() noexcept
		{
#ifndef ENABLE_SKYRIM_VR
			return false;
#elif defined(EXCLUSIVE_SKYRIM_VR)
			return true;
#else
			return GetRuntime() == Runtime::VR;
#endif
		}

	private:
		Module() noexcept = default;
		Module(const Module&) = delete;
		Module(Module&&) = delete;

		~Module() noexcept = default;

		Module& operator=(const Module&) = delete;
		Module& operator=(Module&&) = delete;

		// Emitted from load(), the single point both init() overloads funnel through, rather
		// than the constructor, so Module::_instance can stay constant-initialized (no
		// user-provided ctor -> no static-initialization-order hazard for any consumer that
		// resolves a RELOCATION_ID during its own dynamic initialization).
		static void EmitLicenseNotice() noexcept;

		bool init()
		{
			const REX::W32::HMODULE moduleHandle = REX::W32::GetModuleHandleW(nullptr);
			if (!moduleHandle) {
				stl::report_and_fail("Failed to obtain the process's own module handle."sv);
			}

			constexpr std::size_t bufferSize = 32767;  // Windows extended-length path limit (\\?\ prefix)
			_filePath.resize(bufferSize);
			const auto length = REX::W32::GetModuleFileNameW(
				moduleHandle, _filePath.data(), static_cast<std::uint32_t>(_filePath.size()));
			if (length == 0 || length >= bufferSize) {
				stl::report_and_fail("Failed to obtain the process's own module file path."sv);
			}
			_filePath.resize(length);
			_filename = std::filesystem::path(_filePath).filename().wstring();

			return load(moduleHandle, true);
		}

		bool init(std::wstring_view a_filePath)
		{
			std::filesystem::path exePath(a_filePath);
			_filename = exePath.filename().wstring();
			_filePath = exePath.wstring();
			_injectedModule = REX::W32::LoadLibraryW(_filePath.c_str());
			if (_injectedModule) {
				return load(_injectedModule, false);
			}
			return false;
		}

		[[nodiscard]] bool load(void* a_handle, bool a_failOnError)
		{
			EmitLicenseNotice();
			_base = reinterpret_cast<std::uintptr_t>(a_handle);
			if (!load_version(a_failOnError)) {
				return false;
			}
			load_segments();
			return true;
		}

		void load_segments();

		bool load_version(bool a_failOnError)
		{
			const auto version = GetFileVersion(_filePath);
			if (version) {
				_version = *version;
				// Minor version 4 = VR, 5 = SE, 6+ = AE. AE 1.7.99 bumped the
				// minor version itself (not just patch/build), so this must
				// be a floor, not an exact match, or newer AE releases
				// silently misclassify as SE.
				if (_version[1] == 4) {
					_runtime = Runtime::VR;
				} else if (_version[1] >= 6) {
					_runtime = Runtime::AE;
				} else {
					_runtime = Runtime::SE;
				}
				return true;
			}
			return stl::report_and_error(
				std::format(
					"Failed to obtain file version info for: {}\n"
					"Please contact the author of this script extender plugin for further assistance."sv,
					stl::utf16_to_utf8(_filename).value_or("<unicode conversion error>"s)),
				a_failOnError);
		}

		void clear();

		static constexpr std::array SEGMENTS{
			std::make_pair(".text"sv, REX::W32::IMAGE_SCN_MEM_EXECUTE),
			std::make_pair(".idata"sv, 0u),
			std::make_pair(".rdata"sv, 0u),
			std::make_pair(".data"sv, 0u),
			std::make_pair(".pdata"sv, 0u),
			std::make_pair(".tls"sv, 0u),
			std::make_pair(".text"sv, REX::W32::IMAGE_SCN_MEM_WRITE),
			std::make_pair(".gfids"sv, 0u)
		};

		static Module                       _instance;
		static inline std::atomic_bool      _initialized{ false };
		static inline std::mutex            _initLock;
		REX::W32::HMODULE                   _injectedModule{ nullptr };
		std::wstring                        _filename;
		std::wstring                        _filePath;
		std::array<Segment, Segment::total> _segments;
		Version                             _version;
		std::uintptr_t                      _base{ 0 };
		Runtime                             _runtime{ Runtime::AE };
	};
}
