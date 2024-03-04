#include "REL/Version.h"

#include "REX/W32/VERSION.h"

namespace REL
{
	std::optional<Version> GetFileVersion(stl::zwstring a_filename)
	{
		std::uint32_t     dummy;
		std::vector<char> buf(REX::W32::GetFileVersionInfoSizeW(a_filename.data(), std::addressof(dummy)));
		if (buf.empty()) {
			return std::nullopt;
		}

		if (!REX::W32::GetFileVersionInfoW(a_filename.data(), 0, static_cast<std::uint32_t>(buf.size()), buf.data())) {
			return std::nullopt;
		}

		void*         verBuf{ nullptr };
		std::uint32_t verLen{ 0 };
		if (!REX::W32::VerQueryValueW(buf.data(), L"\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(verBuf), std::addressof(verLen))) {
			return std::nullopt;
		}

		Version             version;
		std::wistringstream ss(std::wstring(static_cast<const wchar_t*>(verBuf), verLen));
		std::wstring        token;
		for (std::size_t i = 0; i < 4 && std::getline(ss, token, L'.'); ++i) {
			version[i] = static_cast<std::uint16_t>(std::stoi(token));
		}

		return version;
	}
}
