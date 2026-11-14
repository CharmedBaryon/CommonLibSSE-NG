#pragma once

#include "REL/Module.h"

namespace REL
{
	namespace detail
	{
		class memory_map
		{
		public:
			memory_map() noexcept = default;
			memory_map(const memory_map&) = delete;

			memory_map(memory_map&& a_rhs) noexcept :
				_mapping(a_rhs._mapping),
				_view(a_rhs._view)
			{
				a_rhs._mapping = nullptr;
				a_rhs._view = nullptr;
			}

			~memory_map() { close(); }

			memory_map& operator=(const memory_map&) = delete;

			memory_map& operator=(memory_map&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					close();

					_mapping = a_rhs._mapping;
					a_rhs._mapping = nullptr;

					_view = a_rhs._view;
					a_rhs._view = nullptr;
				}

				return *this;
			}

			[[nodiscard]] void* data() noexcept { return _view; }

			bool open(stl::zwstring a_name, std::size_t a_size);

			bool create(stl::zwstring a_name, std::size_t a_size);

			// Maps a file directly (read-only) instead of an anonymous named
			// section - used for the format-5 address library, whose on-disk
			// body is already the dense array CommonLib wants in memory.
			bool create_from_file(stl::zwstring a_path);

			void close();

		private:
			void* _mapping{ nullptr };
			void* _view{ nullptr };
		};
	}

	class IDDB
	{
	public:
		struct mapping_t
		{
			std::uint64_t id;
			std::uint64_t offset;
		};

		enum class Format
		{
			SSEv1,
			SSEv2,
			SSEv5,
			VR
		};

		[[nodiscard]] static IDDB& get()
		{
			if (_initialized.load(std::memory_order_acquire)) {
				return _instance;
			}
			std::unique_lock lock(_initLock);
			if (_initialized.load(std::memory_order_relaxed)) {
				return _instance;
			}
			_instance.load();
			_initialized.store(true, std::memory_order_release);
			return _instance;
		}

#ifdef ENABLE_COMMONLIBSSE_TESTING
		[[nodiscard]] static bool inject(std::wstring_view a_filePath, Format a_format)
		{
			return inject(a_filePath, a_format, Module::get().version());
		}

		[[nodiscard]] static bool inject(std::wstring_view a_filePath, Format a_format, Version a_version)
		{
			_initialized = true;
			_instance.clear();
			switch (a_format) {
			case Format::SSEv1:
				return _instance.load_file(a_filePath.data(), a_version, std::uint8_t{ 1 }, false);
			case Format::SSEv2:
				return _instance.load_file(a_filePath.data(), a_version, std::uint8_t{ 2 }, false);
			case Format::SSEv5:
				return _instance.load_file(a_filePath.data(), a_version, std::uint8_t{ 5 }, false);
#	ifdef ENABLE_SKYRIM_VR
			case Format::VR:
				return _instance.load_csv(a_filePath.data(), a_version, false);
#	endif
			default:
				return false;
			}
		}

		// Injects a fixture without asserting an expected format, exercising
		// the same auto-detecting dispatch real (non-test) loads use.
		[[nodiscard]] static bool inject(std::wstring_view a_filePath, Version a_version)
		{
			_initialized = true;
			_instance.clear();
			return _instance.load_file(a_filePath.data(), a_version, std::nullopt, false);
		}

		static void reset()
		{
			_instance.clear();
			_initialized = false;
		}
#endif

		[[nodiscard]] std::size_t id2offset(std::uint64_t a_id) const;

#ifdef ENABLE_SKYRIM_VR
		bool IsVRAddressLibraryAtLeastVersion(const char* a_minimalVRAddressLibVersion, bool a_reportAndFail = false) const;
#endif

	private:
		friend class Module;
		friend class Offset2ID;

		class istream_t
		{
		public:
			using stream_type = std::ifstream;
			using pointer = stream_type*;
			using const_pointer = const stream_type*;
			using reference = stream_type&;
			using const_reference = const stream_type&;

			inline istream_t(stl::zwstring a_filename, std::ios_base::openmode a_mode) :
				_stream(a_filename.data(), a_mode)
			{
				if (!_stream.is_open()) {
					stl::report_and_fail("failed to open address library file");
				}

				_stream.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
			}

			inline void ignore(std::streamsize a_count) { _stream.ignore(a_count); }

			template <class T>
			inline void readin(T& a_val)
			{
				_stream.read(reinterpret_cast<char*>(std::addressof(a_val)), sizeof(T));
			}

			template <
				class T,
				std::enable_if_t<
					std::is_arithmetic_v<T>,
					int> = 0>
			inline T readout()
			{
				T val{};
				readin(val);
				return val;
			}

		private:
			stream_type _stream;
		};

		// Header for format 1 (SE) / format 2 (old AE): a variable-length
		// name field followed by pointer size + a sparse address count.
		class header_v2_t
		{
		public:
			void read(istream_t& a_in)
			{
				std::int32_t version[4]{};
				std::int32_t nameLen{};
				a_in.readin(version);
				a_in.readin(nameLen);
				a_in.ignore(nameLen);

				a_in.readin(_pointerSize);
				a_in.readin(_addressCount);

				for (std::size_t i = 0; i < std::extent_v<decltype(version)>; ++i) {
					_version[i] = static_cast<std::uint16_t>(version[i]);
				}
			}

			[[nodiscard]] std::size_t address_count() const noexcept { return static_cast<std::size_t>(_addressCount); }

			[[nodiscard]] std::uint64_t pointer_size() const noexcept { return static_cast<std::uint64_t>(_pointerSize); }

			[[nodiscard]] Version version() const noexcept { return _version; }

		private:
			Version      _version;
			std::int32_t _pointerSize{ 0 };
			std::int32_t _addressCount{ 0 };
		};

		// Header for format 5 (1.7.99+ AE): a fixed 64-byte name field, a
		// reserved data-format field, and the dense array's element count.
		class header_v5_t
		{
		public:
			void read(istream_t& a_in)
			{
				std::uint32_t version[4]{};
				a_in.readin(version);

				char name[64]{};
				a_in.readin(name);

				a_in.readin(_pointerSize);
				a_in.readin(_dataFormat);
				a_in.readin(_offsetCount);

				for (std::size_t i = 0; i < std::extent_v<decltype(version)>; ++i) {
					_version[i] = static_cast<std::uint16_t>(version[i]);
				}
			}

			[[nodiscard]] std::size_t offset_count() const noexcept { return static_cast<std::size_t>(_offsetCount); }

			[[nodiscard]] Version version() const noexcept { return _version; }

		private:
			Version      _version;
			std::int32_t _pointerSize{ 0 };
			std::int32_t _dataFormat{ 0 };
			std::int32_t _offsetCount{ 0 };
		};

		IDDB() = default;
		IDDB(const IDDB&) = delete;
		IDDB(IDDB&&) = delete;

		~IDDB() = default;

		IDDB& operator=(const IDDB&) = delete;
		IDDB& operator=(IDDB&&) = delete;

		void load()
		{
			const auto version = Module::get().version();
#ifdef ENABLE_SKYRIM_VR
			if SKYRIM_REL_CONSTEXPR (Module::IsVR()) {
				const auto filename =
					stl::utf8_to_utf16(
						std::format("Data/SKSE/Plugins/version-{}.csv"sv, version.string()))
						.value_or(L"<unknown filename>"s);
				load_csv(filename, version, true);
			} else {
#endif
				const auto filename =
					stl::utf8_to_utf16(
						Module::IsAE() ?
							std::format("Data/SKSE/Plugins/versionlib-{}.bin"sv, version.string()) :
							std::format("Data/SKSE/Plugins/version-{}.bin"sv, version.string()))
						.value_or(L"<unknown filename>"s);
				load_file(filename, version, std::nullopt, true);
#ifdef ENABLE_SKYRIM_VR
			}
#endif
		}

		// a_expectedFormat is test-injection only; real loads pass nullopt
		// and dispatch on whatever format byte the file actually contains.
		bool load_file(stl::zwstring a_filename, Version a_version, std::optional<std::uint8_t> a_expectedFormat, bool a_failOnError);

		bool load_v2(istream_t& a_in, header_v2_t a_header, Version a_version, bool a_failOnError);

		bool load_v5(stl::zwstring a_filename, header_v5_t a_header, Version a_version, bool a_failOnError);

#ifdef ENABLE_SKYRIM_VR
		bool load_csv(stl::zwstring a_filename, Version a_version, bool a_failOnError);
#endif

		bool unpack_file(istream_t& a_in, header_v2_t a_header, bool a_failOnError);

		void clear()
		{
			_mmap.close();
			_id2offset = {};
			_id2offsetDense = {};
			_loadedFormat = Format::SSEv1;
		}

		static IDDB                    _instance;
		static inline std::atomic_bool _initialized{ false };
		static inline std::mutex       _initLock;
		detail::memory_map             _mmap;
		std::span<mapping_t>           _id2offset;       // format 1/2/VR: sparse, sorted by id
		std::span<const std::uint32_t> _id2offsetDense;  // format 5: dense, direct-indexed by id
		Format                         _loadedFormat{ Format::SSEv1 };

#ifdef ENABLE_SKYRIM_VR
		Version _vrAddressLibraryVersion;
#endif
	};
}
