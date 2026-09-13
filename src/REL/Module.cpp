#include "REL/Module.h"

#include "REL/ID.h"

#include "REX/W32/KERNEL32.h"

// Only the CMake build defines this (tied to PROJECT_VERSION, kept in sync with releases
// by the semantic-release replace-plugin); xmake has no equivalent version tracking, so
// fall back rather than fail to compile there.
#ifndef COMMONLIB_VERSION
#	define COMMONLIB_VERSION "unknown"
#endif

namespace REL
{
	namespace
	{
		// Emitted once per linked module (each plugin DLL statically links its own copy of
		// REL::Module) via OutputDebugString rather than left as an inert string literal --
		// MSVC's /Gy + /OPT:REF would otherwise strip an unreferenced constant from a Release
		// build. Every consumer that binds any RELOCATION_ID pulls this translation unit in,
		// so this notice reaches any plugin statically linking CommonLibSSE-NG.
		constexpr const char* kLicenseNotice =
			"CommonLibSSE-NG " COMMONLIB_VERSION
			" (statically linked) is licensed under GPL-3.0-or-later with a Modding Exception. "
			"Source: https://github.com/alandtse/CommonLibSSE-NG";
	}

	void Module::EmitLicenseNotice() noexcept { REX::W32::OutputDebugStringA(kLicenseNotice); }

	// constinit enforces that _instance is constant-initialized, so a future non-literal
	// member cannot silently give it a dynamic initializer. The Debug STL's container debug
	// state makes Module non-literal, so the guard applies only where it's achievable.
#ifdef NDEBUG
	constinit Module Module::_instance;
#else
	Module Module::_instance;
#endif

	void Module::load_segments()
	{
		const auto dosHeader = reinterpret_cast<const REX::W32::IMAGE_DOS_HEADER*>(_base);
		const auto ntHeader = stl::adjust_pointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto sections = REX::W32::IMAGE_FIRST_SECTION(ntHeader);
		const auto size = std::min<std::size_t>(ntHeader->fileHeader.sectionCount, _segments.size());
		for (std::size_t i = 0; i < size; ++i) {
			const auto& section = sections[i];
			const auto  it = std::find_if(SEGMENTS.begin(), SEGMENTS.end(), [&](auto&& a_elem) {
                constexpr auto size = std::extent_v<decltype(section.name)>;
                const auto     len = std::min(a_elem.first.size(), size);
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
			REX::W32::FreeLibrary(_injectedModule);
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
		IDDB::_instance.clear();
		IDDB::_initialized = false;
	}
}
