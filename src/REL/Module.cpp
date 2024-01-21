#include "REL/Module.h"

#include "REL/ID.h"

namespace REL
{
    Module Module::_instance;

	void Module::load_segments()
	{
		auto       dosHeader = reinterpret_cast<const WinAPI::IMAGE_DOS_HEADER*>(_base);
		auto       ntHeader = stl::adjust_pointer<WinAPI::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto sections = WinAPI::IMAGE_FIRST_SECTION(ntHeader);
		const auto size = std::min<std::size_t>(ntHeader->fileHeader.sectionCount, _segments.size());
		for (std::size_t i = 0; i < size; ++i) {
			const auto& section = sections[i];
			const auto  it = std::find_if(SEGMENTS.begin(), SEGMENTS.end(), [&](auto&& a_elem) {
                constexpr auto size = std::extent_v<decltype(section.name)>;
                const auto     len = (std::min)(a_elem.first.size(), size);
                return std::memcmp(a_elem.first.data(), section.name, len) == 0 &&
                        (section.characteristics & a_elem.second) == a_elem.second;
            });
			if (it != SEGMENTS.end()) {
				const auto idx = static_cast<std::size_t>(std::distance(SEGMENTS.begin(), it));
				_segments[idx] = Segment{ _base, _base + section.virtualAddress, section.virtualSize };
			}
		}
	}

	void Module::clear()
	{
		if (_injectedModule) {
			WinAPI::FreeLibrary(_injectedModule);
			_injectedModule = nullptr;
		}
		_base = 0;
		_filename.clear();
		_filePath.clear();
		_runtime = Runtime::AE;
		_version = { 0, 0, 0, 0 };
		for (auto& segment : _segments) {
			segment = {};
		}
        IDDatabase::_instance.clear();
        IDDatabase::_initialized = false;
	}
}
