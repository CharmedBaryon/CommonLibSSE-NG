#include "REX/W32/SHELL32.h"

REX_W32_IMPORT(std::int32_t, SHGetKnownFolderPath, const REX::W32::GUID&, std::uint32_t, void*, wchar_t**);

namespace REX::W32
{
	std::int32_t SHGetKnownFolderPath(const GUID& a_id, std::uint32_t a_flags, void* a_token, wchar_t** a_path) noexcept
	{
		return ::W32_IMPL_SHGetKnownFolderPath(a_id, a_flags, a_token, a_path);
	}
}
