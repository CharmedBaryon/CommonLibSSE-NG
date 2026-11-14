#include "REL/IDDB.h"

#include "REX/W32/KERNEL32.h"

#ifdef ENABLE_SKYRIM_VR
#	include <rapidcsv.h>
#endif

namespace REL
{
	namespace
	{
		bool report_unsupported_format(std::int32_t a_format, bool a_failOnError)
		{
			// stl::report_and_error() always returns true (it's a log-and-optionally-
			// terminate helper, not a success signal) -- don't propagate that as if it
			// meant the format loaded fine.
			stl::report_and_error(
				std::format(
					"Unsupported address library format: {}\n"
					"This means this script extender plugin is incompatible with the address "
					"library available for this version of the game, and thus does not "
					"support it."sv,
					a_format),
				a_failOnError);
			return false;
		}

		[[noreturn]] void report_id_lookup_failure(std::uint64_t a_id)
		{
			stl::report_and_fail(
				std::format(
					"Failed to find the id within the address library: {}\n"
					"This means this script extender plugin is incompatible with the address "
					"library for this version of the game, and thus does not support it."sv,
					a_id));
		}
	}

	namespace detail
	{
		bool memory_map::open(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				close();
				return false;
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				close();
				return false;
			}

			return true;
		}

		bool memory_map::create(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				_mapping = REX::W32::CreateFileMappingW(
					REX::W32::INVALID_HANDLE_VALUE,
					nullptr,
					REX::W32::PAGE_READWRITE,
					bytes.hi,
					bytes.lo,
					a_name.data());
				if (!_mapping) {
					return false;
				}
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				return false;
			}

			return true;
		}

		bool memory_map::create_from_file(stl::zwstring a_path)
		{
			close();

			const auto file = REX::W32::CreateFileW(
				a_path.data(),
				REX::W32::GENERIC_READ,
				REX::W32::FILE_SHARE_READ,
				nullptr,
				REX::W32::OPEN_EXISTING,
				REX::W32::FILE_ATTRIBUTE_READONLY,
				nullptr);
			if (file == REX::W32::INVALID_HANDLE_VALUE) {
				return false;
			}

			_mapping = REX::W32::CreateFileMappingW(file, nullptr, REX::W32::PAGE_READONLY, 0, 0, nullptr);
			REX::W32::CloseHandle(file);
			if (!_mapping) {
				return false;
			}

			_view = REX::W32::MapViewOfFile(_mapping, REX::W32::FILE_MAP_READ, 0, 0, 0);
			if (!_view) {
				close();
				return false;
			}

			return true;
		}

		void memory_map::close()
		{
			if (_view) {
				REX::W32::UnmapViewOfFile(static_cast<const void*>(_view));
				_view = nullptr;
			}

			if (_mapping) {
				REX::W32::CloseHandle(_mapping);
				_mapping = nullptr;
			}
		}
	}

	IDDB IDDB::_instance;

	std::size_t IDDB::id2offset(std::uint64_t a_id) const
	{
		if (_loadedFormat == Format::SSEv5) {
			if (a_id >= _id2offsetDense.size() || _id2offsetDense[a_id] == 0) {
				report_id_lookup_failure(a_id);
			}

			return static_cast<std::size_t>(_id2offsetDense[a_id]);
		}

		mapping_t  elem{ a_id, 0 };
		const auto it = std::lower_bound(
			_id2offset.begin(),
			_id2offset.end(),
			elem,
			[](auto&& a_lhs, auto&& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});

		if (it == _id2offset.end() || it->id != a_id) {
			report_id_lookup_failure(a_id);
		}

		return static_cast<std::size_t>(it->offset);
	}

	bool IDDB::load_file(stl::zwstring a_filename, Version a_version, std::optional<std::uint8_t> a_expectedFormat, bool a_failOnError)
	{
		try {
			istream_t    in(a_filename.data(), std::ios::in | std::ios::binary);
			std::int32_t format{};
			in.readin(format);

			if (a_expectedFormat && format != static_cast<std::int32_t>(*a_expectedFormat)) {
				return report_unsupported_format(format, a_failOnError);
			}

			switch (format) {
			case 1:
			case 2:
				{
					header_v2_t header;
					header.read(in);
					if (!load_v2(in, header, a_version, a_failOnError)) {
						return false;
					}
					_loadedFormat = format == 1 ? Format::SSEv1 : Format::SSEv2;
					return true;
				}
			case 5:
				{
					header_v5_t header;
					header.read(in);
					return load_v5(a_filename, header, a_version, a_failOnError);
				}
			default:
				return report_unsupported_format(format, a_failOnError);
			}
		} catch (const std::system_error&) {
			stl::report_and_error(
				std::format(
					"Failed to locate an appropriate address library with the path: {}\n"
					"This means you are missing the address library for this specific version of "
					"the game. Please continue to the mod page for address library to download "
					"an appropriate version. If one is not available, then it is likely that "
					"address library has not yet added support for this version of the game."sv,
					stl::utf16_to_utf8(a_filename).value_or("<unknown filename>"s)),
				a_failOnError);
			return false;
		}
	}

	bool IDDB::load_v2(istream_t& a_in, header_v2_t a_header, Version a_version, bool a_failOnError)
	{
		if (a_header.version() != a_version) {
			stl::report_and_error("version mismatch"sv, a_failOnError);
			return false;
		}

		auto mapname = L"CommonLibSSEOffsets-v2-"s;
		mapname += a_version.wstring();
		const auto byteSize = static_cast<std::size_t>(a_header.address_count()) * sizeof(mapping_t);
		if (_mmap.open(mapname, byteSize)) {
			_id2offset = { static_cast<mapping_t*>(_mmap.data()), a_header.address_count() };
		} else if (_mmap.create(mapname, byteSize)) {
			_id2offset = { static_cast<mapping_t*>(_mmap.data()), a_header.address_count() };
			if (!unpack_file(a_in, a_header, a_failOnError)) {
				_id2offset = {};
				_mmap.close();
				return false;
			}
			std::sort(_id2offset.begin(), _id2offset.end(), [](auto&& a_lhs, auto&& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});
		} else {
			stl::report_and_error("failed to create shared mapping"sv, a_failOnError);
			return false;
		}

		return true;
	}

	bool IDDB::load_v5(stl::zwstring a_filename, header_v5_t a_header, Version a_version, bool a_failOnError)
	{
		if (a_header.version() != a_version) {
			stl::report_and_error("version mismatch"sv, a_failOnError);
			return false;
		}

		if (!_mmap.create_from_file(a_filename)) {
			stl::report_and_error(
				std::format(
					"Failed to memory-map the address library file: {}"sv,
					stl::utf16_to_utf8(a_filename).value_or("<unknown filename>"s)),
				a_failOnError);
			return false;
		}

		constexpr std::size_t headerBytes =
			sizeof(std::int32_t) +       // format
			sizeof(std::uint32_t) * 4 +  // version[4]
			64 +                         // name[64]
			sizeof(std::int32_t) +       // pointerSize
			sizeof(std::int32_t) +       // dataFormat
			sizeof(std::int32_t);        // offsetCount

		// offset_count() comes straight from the file; a truncated/corrupt file
		// could otherwise make the dense span extend past the mapped view.
		std::error_code ec;
		const auto      fileBytes = std::filesystem::file_size(a_filename.data(), ec);
		const auto      neededBytes = headerBytes + static_cast<std::uint64_t>(a_header.offset_count()) * sizeof(std::uint32_t);
		if (ec || fileBytes < neededBytes) {
			_mmap.close();
			stl::report_and_error(
				std::format(
					"Address library file is truncated or its offset count is invalid: {}"sv,
					stl::utf16_to_utf8(a_filename).value_or("<unknown filename>"s)),
				a_failOnError);
			return false;
		}

		const auto* base = static_cast<const std::uint8_t*>(_mmap.data());
		_id2offsetDense = {
			reinterpret_cast<const std::uint32_t*>(base + headerBytes),
			a_header.offset_count()
		};
		_loadedFormat = Format::SSEv5;

		return true;
	}

#ifdef ENABLE_SKYRIM_VR
	bool IDDB::load_csv(stl::zwstring a_filename, Version a_version, bool a_failOnError)
	{
		auto nstring = SKSE::stl::utf16_to_utf8(a_filename).value_or(""s);
		if (!std::filesystem::exists(nstring)) {
			stl::report_and_error(
				std::format("Required VR Address Library file {} does not exist"sv, nstring),
				a_failOnError);
			return false;
		}

		rapidcsv::Document in(nstring);
		std::size_t        id, address_count;
		std::string        version, offset;
		auto               mapname = L"CommonLibSSEOffsets-v2-"s;
		mapname += a_version.wstring();
		address_count = in.GetCell<std::size_t>(0, 0);
		version = in.GetCell<std::string>(1, 0);
		_vrAddressLibraryVersion = Version(version);
		const auto byteSize = static_cast<std::size_t>(address_count * sizeof(mapping_t));
		if (_mmap.open(mapname, byteSize)) {
			_id2offset = { static_cast<mapping_t*>(_mmap.data()), static_cast<std::size_t>(address_count) };
		} else if (_mmap.create(mapname, byteSize)) {
			_id2offset = { static_cast<mapping_t*>(_mmap.data()), static_cast<std::size_t>(address_count) };
			if (in.GetRowCount() > address_count + 1) {
				stl::report_and_error(
					std::format("VR Address Library {} tried to exceed {} allocated entries."sv,
						version, address_count),
					a_failOnError);
				return false;
			} else if (in.GetRowCount() < address_count + 1) {
				stl::report_and_error(
					std::format("VR Address Library {} loaded only {} entries but expected {}. Please redownload."sv,
						version, in.GetRowCount() - 1, address_count),
					a_failOnError);
				return false;
			}

			std::size_t index = 1;
			for (; index < in.GetRowCount(); ++index) {
				id = in.GetCell<std::size_t>(0, index);
				offset = in.GetCell<std::string>(1, index);
				_id2offset[index - 1] = { static_cast<std::uint64_t>(id),
					static_cast<std::uint64_t>(std::stoul(offset, nullptr, 16)) };
			}

			std::sort(_id2offset.begin(), _id2offset.end(), [](auto&& a_lhs, auto&& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});
		} else {
			stl::report_and_error("failed to create shared mapping"sv, a_failOnError);
			return false;
		}

		_loadedFormat = Format::VR;
		return true;
	}

	bool IDDB::IsVRAddressLibraryAtLeastVersion(const char* a_minimalVRAddressLibVersion, bool a_reportAndFail) const
	{
		const auto minimalVersion = REL::Version(a_minimalVRAddressLibVersion);

		if (minimalVersion <= _vrAddressLibraryVersion) {
			return true;
		}

		if (!a_reportAndFail) {
			return false;
		}

		stl::report_and_fail(
			std::format("You need version: {} of VR Address Library for SKSEVR, you have version: {}"sv,
				minimalVersion, _vrAddressLibraryVersion));
	}
#endif

	bool IDDB::unpack_file(istream_t& a_in, header_v2_t a_header, bool a_failOnError)
	{
		std::uint8_t  type = 0;
		std::uint64_t id = 0;
		std::uint64_t offset = 0;
		std::uint64_t prevID = 0;
		std::uint64_t prevOffset = 0;
		for (auto& mapping : _id2offset) {
			a_in.readin(type);
			const auto lo = static_cast<std::uint8_t>(type & 0xF);
			const auto hi = static_cast<std::uint8_t>(type >> 4);

			switch (lo) {
			case 0:
				a_in.readin(id);
				break;
			case 1:
				id = prevID + 1;
				break;
			case 2:
				id = prevID + a_in.readout<std::uint8_t>();
				break;
			case 3:
				id = prevID - a_in.readout<std::uint8_t>();
				break;
			case 4:
				id = prevID + a_in.readout<std::uint16_t>();
				break;
			case 5:
				id = prevID - a_in.readout<std::uint16_t>();
				break;
			case 6:
				id = a_in.readout<std::uint16_t>();
				break;
			case 7:
				id = a_in.readout<std::uint32_t>();
				break;
			default:
				stl::report_and_error("unhandled type"sv, a_failOnError);
				return false;
			}

			const std::uint64_t tmp = (hi & 8) != 0 ? (prevOffset / a_header.pointer_size()) : prevOffset;

			switch (hi & 7) {
			case 0:
				a_in.readin(offset);
				break;
			case 1:
				offset = tmp + 1;
				break;
			case 2:
				offset = tmp + a_in.readout<std::uint8_t>();
				break;
			case 3:
				offset = tmp - a_in.readout<std::uint8_t>();
				break;
			case 4:
				offset = tmp + a_in.readout<std::uint16_t>();
				break;
			case 5:
				offset = tmp - a_in.readout<std::uint16_t>();
				break;
			case 6:
				offset = a_in.readout<std::uint16_t>();
				break;
			case 7:
				offset = a_in.readout<std::uint32_t>();
				break;
			default:
				stl::report_and_error("unhandled type"sv, a_failOnError);
				return false;
			}

			if ((hi & 8) != 0) {
				offset *= a_header.pointer_size();
			}

			mapping = { id, offset };

			prevOffset = offset;
			prevID = id;
		}

		return true;
	}
}
