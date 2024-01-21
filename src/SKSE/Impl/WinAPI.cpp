#include "SKSE/Impl/WinAPI.h"

#define WIN32_LEAN_AND_MEAN

// clang-format off
#include <Windows.h>
#include <DbgHelp.h>
#include <objbase.h>
#include <ShlObj.h>
// clang-format on

#undef CreateFileMapping
#undef CreateProcess
#undef ExpandEnvironmentStrings
#undef FindFirstFile
#undef FindNextFile
#undef GetEnvironmentVariable
#undef GetFileVersionInfo
#undef GetFileVersionInfoSize
#undef GetKeyNameText
#undef GetModuleFileName
#undef GetModuleHandle
#undef GetPrivateProfileString
#undef IMAGE_FIRST_SECTION
#undef IMAGE_SNAP_BY_ORDINAL64
#undef LoadLibrary
#undef MessageBox
#undef OpenFileMapping
#undef OutputDebugString
#undef RegGetValue
#undef RegQueryValueEx
#undef SetEnvironmentVariable
#undef VerQueryValue

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace SKSE::WinAPI
{
	bool CloseHandle(
		void* a_handle) noexcept
	{
		return static_cast<bool>(
			::CloseHandle(
				a_handle));
	}

	void CoTaskMemFree(
		void* a_block) noexcept
	{
		::CoTaskMemFree(
			a_block);
	}

	void* CreateFileMapping(
		void*                a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t        a_protect,
		std::uint32_t        a_maxSizeHigh,
		std::uint32_t        a_maxSizeLow,
		const char*          a_name) noexcept
	{
		return CreateFileMappingA(
			a_file,
			reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_attributes),
			a_protect,
			a_maxSizeHigh,
			a_maxSizeLow,
			a_name);
	}

	void* CreateFileMapping(
		void*                a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t        a_protect,
		std::uint32_t        a_maxSizeHigh,
		std::uint32_t        a_maxSizeLow,
		const wchar_t*       a_name) noexcept
	{
		return CreateFileMappingW(
			a_file,
			reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_attributes),
			a_protect,
			a_maxSizeHigh,
			a_maxSizeLow,
			a_name);
	}

	bool CreateProcess(
		const char*          a_name,
		char*                a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool                 a_inherit,
		std::uint32_t        a_flags,
		void*                a_env,
		const char*          a_curDir,
		STARTUPINFOA*        a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return static_cast<bool>(
			CreateProcessA(
				a_name,
				a_cmd,
				reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_procAttr),
				reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_threadAttr),
				a_inherit,
				a_flags,
				a_env,
				a_curDir,
				reinterpret_cast<LPSTARTUPINFOA>(a_startInfo),
				reinterpret_cast<LPPROCESS_INFORMATION>(a_procInfo)));
	}

	bool CreateProcess(
		const wchar_t*       a_name,
		wchar_t*             a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool                 a_inherit,
		std::uint32_t        a_flags,
		void*                a_env,
		const wchar_t*       a_curDir,
		STARTUPINFOW*        a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return static_cast<bool>(
			CreateProcessW(
				a_name,
				a_cmd,
				reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_procAttr),
				reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_threadAttr),
				a_inherit,
				a_flags,
				a_env,
				a_curDir,
				reinterpret_cast<LPSTARTUPINFOW>(a_startInfo),
				reinterpret_cast<LPPROCESS_INFORMATION>(a_procInfo)));
	}

	void* CreateRemoteThread(
		void*                 a_process,
		SECURITY_ATTRIBUTES*  a_threadAttr,
		std::size_t           a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void*                 a_param,
		std::uint32_t         a_flags,
		std::uint32_t*        a_threadID) noexcept
	{
		return ::CreateRemoteThread(
			a_process,
			reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_threadAttr),
			a_stackSize,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(a_startAddr),
			a_param,
			a_flags,
			reinterpret_cast<LPDWORD>(a_threadID));
	}

	void* CreateThread(
		SECURITY_ATTRIBUTES*  a_threadAttr,
		std::size_t           a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void*                 a_param,
		std::uint32_t         a_flags,
		std::uint32_t*        a_threadID) noexcept
	{
		return ::CreateThread(
			reinterpret_cast<LPSECURITY_ATTRIBUTES>(a_threadAttr),
			a_stackSize,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(a_startAddr),
			a_param,
			a_flags,
			reinterpret_cast<LPDWORD>(a_threadID));
	}

	std::uint32_t ExpandEnvironmentStrings(
		const char*   a_src,
		char*         a_dst,
		std::uint32_t a_dstLen) noexcept
	{
		return static_cast<std::uint32_t>(
			ExpandEnvironmentStringsA(
				a_src,
				a_dst,
				a_dstLen));
	}

	std::uint32_t ExpandEnvironmentStrings(
		const wchar_t* a_src,
		wchar_t*       a_dst,
		std::uint32_t  a_dstLen) noexcept
	{
		return static_cast<std::uint32_t>(
			ExpandEnvironmentStringsW(
				a_src,
				a_dst,
				a_dstLen));
	}

	bool FindClose(
		void* a_file) noexcept
	{
		return static_cast<bool>(
			::FindClose(
				a_file));
	}

	void* FindFirstFile(
		const char*       a_name,
		WIN32_FIND_DATAA* a_data) noexcept
	{
		return FindFirstFileA(
			a_name,
			reinterpret_cast<LPWIN32_FIND_DATAA>(a_data));
	}

	void* FindFirstFile(
		const wchar_t*    a_name,
		WIN32_FIND_DATAW* a_data) noexcept
	{
		return FindFirstFileW(
			a_name,
			reinterpret_cast<LPWIN32_FIND_DATAW>(a_data));
	}

	bool FindNextFile(
		void*             a_file,
		WIN32_FIND_DATAA* a_data) noexcept
	{
		return static_cast<bool>(
			FindNextFileA(
				a_file,
				reinterpret_cast<LPWIN32_FIND_DATAA>(a_data)));
	}

	bool FindNextFile(
		void*             a_file,
		WIN32_FIND_DATAW* a_data) noexcept
	{
		return static_cast<bool>(
			FindNextFileW(
				a_file,
				reinterpret_cast<LPWIN32_FIND_DATAW>(a_data)));
	}

	bool FlushInstructionCache(
		void*       a_process,
		const void* a_baseAddr,
		std::size_t a_size) noexcept
	{
		return static_cast<bool>(
			::FlushInstructionCache(
				a_process,
				a_baseAddr,
				a_size));
	}

	bool FreeLibrary(
		HMODULE a_module) noexcept
	{
		return static_cast<bool>(
			::FreeLibrary(
				reinterpret_cast<::HMODULE>(a_module)));
	}

	void* GetCurrentModule() noexcept
	{
		return std::addressof(__ImageBase);
	}

	void* GetCurrentProcess() noexcept
	{
		return ::GetCurrentProcess();
	}

	std::uint32_t GetCurrentThreadID() noexcept
	{
		return static_cast<std::uint32_t>(
			GetCurrentThreadId());
	}

	std::uint32_t GetEnvironmentVariable(
		const char*   a_name,
		char*         a_buffer,
		std::uint32_t a_bufferLen) noexcept
	{
		return static_cast<std::uint32_t>(
			GetEnvironmentVariableA(
				a_name,
				a_buffer,
				a_bufferLen));
	}

	std::uint32_t GetEnvironmentVariable(
		const wchar_t* a_name,
		wchar_t*       a_buffer,
		std::uint32_t  a_bufferLen) noexcept
	{
		return static_cast<std::uint32_t>(
			GetEnvironmentVariableW(
				a_name,
				a_buffer,
				a_bufferLen));
	}

	bool GetFileVersionInfo(
		const char*   a_name,
		std::uint32_t a_handle,
		std::uint32_t a_dataLen,
		void*         a_data) noexcept
	{
		return static_cast<bool>(
			GetFileVersionInfoA(
				a_name,
				a_handle,
				a_dataLen,
				a_data));
	}

	bool GetFileVersionInfo(
		const wchar_t* a_name,
		std::uint32_t  a_handle,
		std::uint32_t  a_dataLen,
		void*          a_data) noexcept
	{
		return static_cast<bool>(
			GetFileVersionInfoW(
				a_name,
				a_handle,
				a_dataLen,
				a_data));
	}

	std::uint32_t GetFileVersionInfoSize(
		const char*    a_name,
		std::uint32_t* a_handle) noexcept
	{
		return static_cast<std::uint32_t>(
			GetFileVersionInfoSizeA(
				a_name,
				reinterpret_cast<LPDWORD>(a_handle)));
	}

	std::uint32_t GetFileVersionInfoSize(
		const wchar_t* a_name,
		std::uint32_t* a_handle) noexcept
	{
		return static_cast<std::uint32_t>(
			GetFileVersionInfoSizeW(
				a_name,
				reinterpret_cast<LPDWORD>(a_handle)));
	}

	std::int32_t GetKeyNameText(
		std::int32_t a_param,
		wchar_t*     a_buffer,
		std::int32_t a_bufferLen) noexcept
	{
		return GetKeyNameTextW(
			a_param,
			a_buffer,
			a_bufferLen);
	}

	std::int32_t GetKeyNameText(
		std::int32_t a_param,
		char*        a_buffer,
		std::int32_t a_bufferLen) noexcept
	{
		return GetKeyNameTextA(
			a_param,
			a_buffer,
			a_bufferLen);
	}

	std::int16_t GetKeyState(
		std::int32_t a_key) noexcept
	{
		return ::GetKeyState(a_key);
	}

	std::uint32_t GetLastError() noexcept
	{
		return static_cast<std::uint32_t>(
			::GetLastError());
	}

	std::size_t GetMaxPath() noexcept
	{
		return MAX_PATH;
	}

	std::uint32_t GetModuleFileName(
		void*         a_module,
		char*         a_name,
		std::uint32_t a_nameLen) noexcept
	{
		return static_cast<std::uint32_t>(
			GetModuleFileNameA(
				static_cast<::HMODULE>(a_module),
				a_name,
				a_nameLen));
	}

	std::uint32_t GetModuleFileName(
		void*         a_module,
		wchar_t*      a_name,
		std::uint32_t a_nameLen) noexcept
	{
		return static_cast<std::uint32_t>(
			GetModuleFileNameW(
				static_cast<::HMODULE>(a_module),
				a_name,
				a_nameLen));
	}

	HMODULE GetModuleHandle(
		const char* a_name) noexcept
	{
		return reinterpret_cast<HMODULE>(
			GetModuleHandleA(
				a_name));
	}

	HMODULE GetModuleHandle(
		const wchar_t* a_name) noexcept
	{
		return reinterpret_cast<HMODULE>(
			GetModuleHandleW(a_name));
	}

	std::uint32_t GetPrivateProfileString(
		const char*   a_app,
		const char*   a_key,
		const char*   a_default,
		char*         a_out,
		std::uint32_t a_outLen,
		const char*   a_name) noexcept
	{
		return static_cast<std::uint32_t>(
			GetPrivateProfileStringA(
				a_app,
				a_key,
				a_default,
				a_out,
				a_outLen,
				a_name));
	}

	std::uint32_t GetPrivateProfileString(
		const wchar_t* a_app,
		const wchar_t* a_key,
		const wchar_t* a_default,
		wchar_t*       a_out,
		std::uint32_t  a_outLen,
		const wchar_t* a_name) noexcept
	{
		return static_cast<std::uint32_t>(
			GetPrivateProfileStringW(
				a_app,
				a_key,
				a_default,
				a_out,
				a_outLen,
				a_name));
	}

	void* GetProcAddress(
		void*       a_module,
		const char* a_name) noexcept
	{
		return reinterpret_cast<void*>(
			::GetProcAddress(
				static_cast<::HMODULE>(a_module),
				a_name));
	}

	std::string_view GetProcPath(
		HMODULE a_handle) noexcept
	{
		static std::string fileName(MAX_PATH + 1, ' ');
		auto               res = GetModuleFileName(a_handle, fileName.data(), MAX_PATH + 1);
		if (res == 0) {
			fileName = "[ProcessHost]";
			res = 13;
		}

		return { fileName.c_str(), res };
	}

	void GetSystemInfo(
		SYSTEM_INFO* a_info) noexcept
	{
		::GetSystemInfo(
			reinterpret_cast<LPSYSTEM_INFO>(a_info));
	}

	bool IMAGE_SNAP_BY_ORDINAL64(
		std::uint64_t a_ordinal) noexcept
	{
		return (a_ordinal & IMAGE_ORDINAL_FLAG64) != 0;
	}

	IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(
		const IMAGE_NT_HEADERS64* a_header) noexcept
	{
		constexpr auto opt = __builtin_offsetof(IMAGE_NT_HEADERS64, optionalHeader);
		const auto     optSize = a_header->fileHeader.optionalHeaderSize;
		const auto     section = reinterpret_cast<std::uintptr_t>(a_header) + opt + optSize;
		return reinterpret_cast<IMAGE_SECTION_HEADER*>(section);
	}

	bool IsDebuggerPresent() noexcept
	{
		return static_cast<bool>(
			::IsDebuggerPresent());
	}

	std::int32_t LCMapStringEx(
		const wchar_t*  a_locale,
		std::uint32_t   a_flags,
		const wchar_t*  a_src,
		std::int32_t    a_srcLen,
		wchar_t*        a_dest,
		std::int32_t    a_destLen,
		NLSVERSIONINFO* a_info,
		void*           a_reserved,
		std::intptr_t   a_sortHandle) noexcept
	{
		return ::LCMapStringEx(
			a_locale,
			a_flags,
			a_src,
			a_srcLen,
			a_dest,
			a_destLen,
			reinterpret_cast<LPNLSVERSIONINFO>(a_info),
			a_reserved,
			a_sortHandle);
	}

	HMODULE LoadLibrary(
		const char* a_name) noexcept
	{
		return reinterpret_cast<HMODULE>(
			LoadLibraryA(
				a_name));
	}

	HMODULE LoadLibrary(
		const wchar_t* a_name) noexcept
	{
		return reinterpret_cast<HMODULE>(
			LoadLibraryW(a_name));
	}

	void* MapViewOfFile(
		void*         a_object,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_fileOffsetHigh,
		std::uint32_t a_fileOffsetLow,
		std::size_t   a_numBytesToMap) noexcept
	{
		return ::MapViewOfFile(
			a_object,
			a_desiredAccess,
			a_fileOffsetHigh,
			a_fileOffsetLow,
			a_numBytesToMap);
	}

	void* MapViewOfFileEx(
		void*         a_object,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_fileOffsetHigh,
		std::uint32_t a_fileOffsetLow,
		std::size_t   a_numBytesToMap,
		void*         a_baseAddress) noexcept
	{
		return ::MapViewOfFileEx(
			a_object,
			a_desiredAccess,
			a_fileOffsetHigh,
			a_fileOffsetLow,
			a_numBytesToMap,
			a_baseAddress);
	}

	std::int32_t MessageBox(
		void*         a_wnd,
		const char*   a_text,
		const char*   a_caption,
		std::uint32_t a_type) noexcept
	{
		return MessageBoxA(
			static_cast<::HWND>(a_wnd),
			a_text,
			a_caption,
			a_type);
	}

	std::int32_t MessageBox(
		void*          a_wnd,
		const wchar_t* a_text,
		const wchar_t* a_caption,
		std::uint32_t  a_type) noexcept
	{
		return MessageBoxW(
			static_cast<::HWND>(a_wnd),
			a_text,
			a_caption,
			a_type);
	}

	std::int32_t MultiByteToWideChar(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const char*   a_str,
		std::int32_t  a_strLen,
		wchar_t*      a_wstr,
		std::int32_t  a_wstrLen)
	{
		return ::MultiByteToWideChar(
			a_codePage,
			a_flags,
			a_str,
			a_strLen,
			a_wstr,
			a_wstrLen);
	}

	std::int32_t NormalizeString(
		std::int32_t   a_normForm,
		const wchar_t* a_src,
		std::int32_t   a_srcLen,
		wchar_t*       a_dest,
		std::int32_t   a_destLen)
	{
		return ::NormalizeString(
			static_cast<NORM_FORM>(a_normForm),
			a_src,
			a_srcLen,
			a_dest,
			a_destLen);
	}

	void* OpenFileMapping(
		std::uint32_t a_desiredAccess,
		bool          a_inheritHandle,
		const char*   a_name) noexcept
	{
		return OpenFileMappingA(
			a_desiredAccess,
			a_inheritHandle,
			a_name);
	}

	void* OpenFileMapping(
		std::uint32_t  a_desiredAccess,
		bool           a_inheritHandle,
		const wchar_t* a_name) noexcept
	{
		return OpenFileMappingW(
			a_desiredAccess,
			a_inheritHandle,
			a_name);
	}

	void OutputDebugString(
		const char* a_out) noexcept
	{
		OutputDebugStringA(
			a_out);
	}

	void OutputDebugString(
		const wchar_t* a_out) noexcept
	{
		OutputDebugStringW(
			a_out);
	}

	std::int32_t RegGetValue(
		HKEY           a_key,
		const char*    a_subKey,
		const char*    a_value,
		std::uint32_t  a_flags,
		std::uint32_t* a_type,
		void*          a_data,
		std::uint32_t* a_dataLen)
	{
		return RegGetValueA(
			reinterpret_cast<::HKEY>(a_key),
			a_subKey,
			a_value,
			a_flags,
			reinterpret_cast<LPDWORD>(a_type),
			a_data,
			reinterpret_cast<LPDWORD>(a_dataLen));
	}

	std::int32_t RegGetValue(
		HKEY           a_key,
		const wchar_t* a_subKey,
		const wchar_t* a_value,
		std::uint32_t  a_flags,
		std::uint32_t* a_type,
		void*          a_data,
		std::uint32_t* a_dataLen)
	{
		return RegGetValueW(
			reinterpret_cast<::HKEY>(a_key),
			a_subKey,
			a_value,
			a_flags,
			reinterpret_cast<LPDWORD>(a_type),
			a_data,
			reinterpret_cast<LPDWORD>(a_dataLen));
	}

	std::uint32_t ResumeThread(
		void* a_handle) noexcept
	{
		return static_cast<std::uint32_t>(
			::ResumeThread(
				a_handle));
	}

	bool SetEnvironmentVariable(
		const char* a_name,
		const char* a_value) noexcept
	{
		return static_cast<bool>(
			SetEnvironmentVariableA(
				a_name,
				a_value));
	}

	bool SetEnvironmentVariable(
		const wchar_t* a_name,
		const wchar_t* a_value) noexcept
	{
		return static_cast<bool>(
			SetEnvironmentVariableW(
				a_name,
				a_value));
	}

	std::int32_t SHGetKnownFolderPath(
		const GUID&   a_id,
		std::uint32_t a_flags,
		void*         a_token,
		wchar_t**     a_path) noexcept
	{
		return static_cast<std::int32_t>(
			::SHGetKnownFolderPath(
				reinterpret_cast<const KNOWNFOLDERID&>(a_id),
				a_flags,
				a_token,
				a_path));
	}

	std::int32_t ShowCursor(
		bool a_show) noexcept
	{
		return ::ShowCursor(
			a_show);
	}

	void Sleep(
		std::uint32_t a_milliseconds) noexcept
	{
		::Sleep(a_milliseconds);
	}

	bool TerminateProcess(
		void*         a_process,
		std::uint32_t a_exitCode) noexcept
	{
		return static_cast<bool>(
			::TerminateProcess(
				a_process,
				a_exitCode));
	}

	void* TlsGetValue(
		std::uint32_t a_index) noexcept
	{
		return ::TlsGetValue(
			a_index);
	}

	bool TlsSetValue(
		std::uint32_t a_index,
		void*         a_value) noexcept
	{
		return static_cast<bool>(
			::TlsSetValue(
				a_index,
				a_value));
	}

	std::uint32_t UnDecorateSymbolName(
		const char*   a_name,
		char*         a_out,
		std::uint32_t a_outLenMax,
		std::uint32_t a_flags) noexcept
	{
		return static_cast<std::uint32_t>(
			::UnDecorateSymbolName(
				a_name,
				a_out,
				a_outLenMax,
				a_flags));
	}

	std::uint32_t UnDecorateSymbolName(
		const wchar_t* a_name,
		wchar_t*       a_out,
		std::uint32_t  a_outLenMax,
		std::uint32_t  a_flags) noexcept
	{
		return static_cast<std::uint32_t>(
			UnDecorateSymbolNameW(
				a_name,
				a_out,
				a_outLenMax,
				a_flags));
	}

	bool UnmapViewOfFile(
		const void* a_baseAddress) noexcept
	{
		return static_cast<bool>(
			::UnmapViewOfFile(
				a_baseAddress));
	}

	bool VerQueryValue(
		const void*    a_block,
		const char*    a_subBlock,
		void**         a_buffer,
		std::uint32_t* a_bufferLen) noexcept
	{
		return static_cast<bool>(
			VerQueryValueA(a_block,
				a_subBlock,
				a_buffer,
				a_bufferLen));
	}

	bool VerQueryValue(
		const void*    a_block,
		const wchar_t* a_subBlock,
		void**         a_buffer,
		std::uint32_t* a_bufferLen) noexcept
	{
		return static_cast<bool>(
			VerQueryValueW(
				a_block,
				a_subBlock,
				a_buffer,
				a_bufferLen));
	}

	void* VirtualAlloc(
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept
	{
		return ::VirtualAlloc(
			a_address,
			a_size,
			a_type,
			a_protect);
	}

	void* VirtualAllocEx(
		void*         a_process,
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept
	{
		return ::VirtualAllocEx(
			a_process,
			a_address,
			a_size,
			a_type,
			a_protect);
	}

	bool VirtualFree(
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type) noexcept
	{
		return static_cast<bool>(
			::VirtualFree(
				a_address,
				a_size,
				a_type));
	}

	bool VirtualFreeEx(
		void*         a_process,
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type) noexcept
	{
		return static_cast<bool>(
			::VirtualFreeEx(
				a_process,
				a_address,
				a_size,
				a_type));
	}

	bool VirtualProtect(
		void*          a_address,
		std::size_t    a_size,
		std::uint32_t  a_newProtect,
		std::uint32_t* a_oldProtect) noexcept
	{
		return static_cast<bool>(
			::VirtualProtect(
				a_address,
				a_size,
				a_newProtect,
				reinterpret_cast<PDWORD>(a_oldProtect)));
	}

	bool VirtualProtectEx(
		void*          a_process,
		void*          a_address,
		std::size_t    a_size,
		std::uint32_t  a_newProtect,
		std::uint32_t* a_oldProtect) noexcept
	{
		return static_cast<bool>(
			::VirtualProtectEx(
				a_process,
				a_address,
				a_size,
				a_newProtect,
				reinterpret_cast<PDWORD>(a_oldProtect)));
	}

	std::size_t VirtualQuery(
		const void*               a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t               a_bufferLen) noexcept
	{
		return ::VirtualQuery(
			a_address,
			reinterpret_cast<PMEMORY_BASIC_INFORMATION>(a_buffer),
			a_bufferLen);
	}

	std::size_t VirtualQueryEx(
		void*                     a_process,
		const void*               a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t               a_bufferLen) noexcept
	{
		return ::VirtualQueryEx(
			a_process,
			a_address,
			reinterpret_cast<PMEMORY_BASIC_INFORMATION>(a_buffer),
			a_bufferLen);
	}

	std::uint32_t WaitForSingleObject(
		void*         a_handle,
		std::uint32_t a_milliseconds) noexcept
	{
		return static_cast<std::uint32_t>(
			::WaitForSingleObject(
				a_handle,
				a_milliseconds));
	}

	std::uint32_t WaitForSingleObjectEx(
		void*         a_handle,
		std::uint32_t a_milliseconds,
		bool          a_alertable) noexcept
	{
		return static_cast<std::uint32_t>(
			::WaitForSingleObjectEx(
				a_handle,
				a_milliseconds,
				a_alertable));
	}

	std::int32_t WideCharToMultiByte(
		std::uint32_t  a_codePage,
		std::uint32_t  a_flags,
		const wchar_t* a_wstr,
		std::int32_t   a_wstrLen,
		char*          a_str,
		std::int32_t   a_strLen,
		const char*    a_default,
		std::int32_t*  a_defaultLen)
	{
		return ::WideCharToMultiByte(
			a_codePage,
			a_flags,
			a_wstr,
			a_wstrLen,
			a_str,
			a_strLen,
			a_default,
			a_defaultLen);
	}

	bool WriteProcessMemory(
		void*        a_process,
		void*        a_address,
		const void*  a_buffer,
		std::size_t  a_bufferLen,
		std::size_t* a_bufferWritten) noexcept
	{
		return static_cast<bool>(
			::WriteProcessMemory(
				a_process,
				a_address,
				a_buffer,
				a_bufferLen,
				a_bufferWritten));
	}
}
