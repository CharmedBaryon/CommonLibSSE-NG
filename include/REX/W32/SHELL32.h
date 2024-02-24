#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	// known folder ids
	inline constexpr GUID FOLDERID_Documents{ 0xFDD39AD0u, 0x238Fu, 0x46AFu, { 0xADu, 0xB4u, 0x6Cu, 0x85u, 0x48u, 0x03u, 0x69u, 0xC7u } };
	inline constexpr GUID FOLDERID_Pictures{ 0x33E28130u, 0x4E1Eu, 0x4676u, { 0x83u, 0x5Au, 0x98u, 0x39u, 0x5Cu, 0x3Bu, 0xC3u, 0xBBu } };
	inline constexpr GUID FOLDERID_ProgramData{ 0x62AB5D82u, 0xFDC1u, 0x4DC3u, { 0xA9u, 0xDDu, 0x07u, 0x0Du, 0x1Du, 0x49u, 0x5Du, 0x97u } };

	// known folder flags
	inline constexpr auto KF_FLAG_DEFAULT{ 0x00000000u };
	inline constexpr auto KF_FLAG_FORCE_APP_DATA_REDIRECTION{ 0x00080000u };
	inline constexpr auto KF_FLAG_RETURN_FILTER_REDIRECTION_TARGET{ 0x00040000u };
	inline constexpr auto KF_FLAG_FORCE_PACKAGE_REDIRECTION{ 0x00020000u };
	inline constexpr auto KF_FLAG_NO_PACKAGE_REDIRECTION{ 0x00010000u };
	inline constexpr auto KF_FLAG_FORCE_APPCONTAINER_REDIRECTION{ 0x00020000u };
	inline constexpr auto KF_FLAG_NO_APPCONTAINER_REDIRECTION{ 0x00010000u };
	inline constexpr auto KF_FLAG_CREATE{ 0x00008000u };
	inline constexpr auto KF_FLAG_DONT_VERIFY{ 0x00004000u };
	inline constexpr auto KF_FLAG_DONT_UNEXPAND{ 0x00002000u };
	inline constexpr auto KF_FLAG_NO_ALIAS{ 0x00001000u };
	inline constexpr auto KF_FLAG_INIT{ 0x00000800u };
	inline constexpr auto KF_FLAG_DEFAULT_PATH{ 0x00000400u };
	inline constexpr auto KF_FLAG_NOT_PARENT_RELATIVE{ 0x00000200u };
	inline constexpr auto KF_FLAG_SIMPLE_IDLIST{ 0x00000100u };
	inline constexpr auto KF_FLAG_ALIAS_ONLY{ 0x80000000u };
}

namespace REX::W32
{
	std::int32_t SHGetKnownFolderPath(const GUID& a_id, std::uint32_t a_flags, void* a_token, wchar_t** a_path) noexcept;
}
