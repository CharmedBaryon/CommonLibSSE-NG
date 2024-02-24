#include "REX/W32/KERNEL32.h"

REX_W32_IMPORT(REX::W32::BOOL, CloseHandle, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileMappingA, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, std::uint32_t, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileMappingW, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, std::uint32_t, const wchar_t*);
REX_W32_IMPORT(REX::W32::BOOL, CreateProcessA, const char*, char*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::BOOL, std::uint32_t, void*, const char*, REX::W32::STARTUPINFOA*, REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT(REX::W32::BOOL, CreateProcessW, const wchar_t*, wchar_t*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::BOOL, std::uint32_t, void*, const wchar_t*, REX::W32::STARTUPINFOW*, REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateRemoteThread, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::size_t, REX::W32::THREAD_START_ROUTINE*, void*, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateSemaphoreA, REX::W32::SECURITY_ATTRIBUTES*, std::int32_t, std::int32_t, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateThread, REX::W32::SECURITY_ATTRIBUTES*, std::size_t, REX::W32::THREAD_START_ROUTINE*, void*, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(void, DeleteCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(void, EnterCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, FindClose, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileA, const char*, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileW, const wchar_t*, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileA, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileW, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FlushInstructionCache, REX::W32::HANDLE, const void*, std::size_t);
REX_W32_IMPORT(REX::W32::BOOL, FreeLibrary, REX::W32::HMODULE);
REX_W32_IMPORT(REX::W32::HANDLE, GetCurrentProcess);
REX_W32_IMPORT(std::uint32_t, GetCurrentThreadId);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetLastError);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameA, REX::W32::HMODULE, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameW, REX::W32::HMODULE, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleW, const wchar_t*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileStringA, const char*, const char*, const char*, char*, std::uint32_t, const char*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileStringW, const wchar_t*, const wchar_t*, const wchar_t*, wchar_t*, std::uint32_t, const wchar_t*);
REX_W32_IMPORT(void*, GetProcAddress, REX::W32::HMODULE, const char*);
REX_W32_IMPORT(void, GetSystemInfo, REX::W32::SYSTEM_INFO*);
REX_W32_IMPORT(REX::W32::BOOL, InitializeCriticalSectionAndSpinCount, REX::W32::CRITICAL_SECTION*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, IsDebuggerPresent);
REX_W32_IMPORT(std::int32_t, LCMapStringEx, const wchar_t*, std::uint32_t, const wchar_t*, std::int32_t, wchar_t*, std::int32_t, REX::W32::NLSVERSIONINFO*, void*, std::intptr_t);
REX_W32_IMPORT(void, LeaveCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryW, const wchar_t*);
REX_W32_IMPORT(void*, MapViewOfFile, REX::W32::HANDLE, std::uint32_t, std::uint32_t, std::uint32_t, std::size_t);
REX_W32_IMPORT(void*, MapViewOfFileEx, REX::W32::HANDLE, std::uint32_t, std::uint32_t, std::uint32_t, std::size_t, void*);
REX_W32_IMPORT(std::int32_t, MultiByteToWideChar, std::uint32_t, std::uint32_t, const char*, std::int32_t, wchar_t*, std::int32_t);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingA, std::uint32_t, REX::W32::BOOL, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingW, std::uint32_t, REX::W32::BOOL, const wchar_t*);
REX_W32_IMPORT(void, OutputDebugStringA, const char*);
REX_W32_IMPORT(void, OutputDebugStringW, const wchar_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceCounter, std::int64_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceFrequency, std::int64_t*);
REX_W32_IMPORT(std::uint32_t, ResumeThread, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableA, const char*, const char*);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableW, const wchar_t*, const wchar_t*);
REX_W32_IMPORT(void, Sleep, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TerminateProcess, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(void*, TlsGetValue, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TlsSetValue, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, UnmapViewOfFile, const void*);
REX_W32_IMPORT(void*, VirtualAlloc, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(void*, VirtualAllocEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFree, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFreeEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtect, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtectEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(std::size_t, VirtualQuery, const void*, MEMORY_BASIC_INFORMATION*, std::size_t);
REX_W32_IMPORT(std::size_t, VirtualQueryEx, REX::W32::HANDLE, const void*, MEMORY_BASIC_INFORMATION*, std::size_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObject, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObjectEx, REX::W32::HANDLE, std::uint32_t, REX::W32::BOOL);
REX_W32_IMPORT(std::int32_t, WideCharToMultiByte, std::uint32_t, std::uint32_t, const wchar_t*, std::int32_t, char*, std::int32_t, const char*, std::int32_t*);
REX_W32_IMPORT(REX::W32::BOOL, WriteProcessMemory, REX::W32::HANDLE, void*, const void*, std::size_t, std::size_t*);

extern "C" REX::W32::IMAGE_DOS_HEADER __ImageBase;

namespace REX::W32
{
	bool CloseHandle(HANDLE a_handle) noexcept
	{
		return ::W32_IMPL_CloseHandle(a_handle);
	}

	HANDLE CreateFileMappingA(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const char* a_name) noexcept
	{
		return ::W32_IMPL_CreateFileMappingA(a_file, a_attributes, a_protect, a_maxSizeHigh, a_maxSizeLow, a_name);
	}

	HANDLE CreateFileMappingW(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_CreateFileMappingW(a_file, a_attributes, a_protect, a_maxSizeHigh, a_maxSizeLow, a_name);
	}

	bool CreateProcessA(const char* a_name, char* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const char* a_curDir, STARTUPINFOA* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return ::W32_IMPL_CreateProcessA(a_name, a_cmd, a_procAttr, a_threadAttr, a_inheritHandles, a_flags, a_env, a_curDir, a_startInfo, a_procInfo);
	}

	bool CreateProcessW(const wchar_t* a_name, wchar_t* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const wchar_t* a_curDir, STARTUPINFOW* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return ::W32_IMPL_CreateProcessW(a_name, a_cmd, a_procAttr, a_threadAttr, a_inheritHandles, a_flags, a_env, a_curDir, a_startInfo, a_procInfo);
	}

	HANDLE CreateRemoteThread(HANDLE a_process, SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept
	{
		return ::W32_IMPL_CreateRemoteThread(a_process, a_threadAttr, a_stackSize, a_startAddr, a_param, a_flags, a_threadID);
	}

	HANDLE CreateSemaphoreA(SECURITY_ATTRIBUTES* a_semaphoreAttr, std::int32_t a_initCount, std::int32_t a_maxCount, const char* a_name)
	{
		return ::W32_IMPL_CreateSemaphoreA(a_semaphoreAttr, a_initCount, a_maxCount, a_name);
	}

	HANDLE CreateThread(SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept
	{
		return ::W32_IMPL_CreateThread(a_threadAttr, a_stackSize, a_startAddr, a_param, a_flags, a_threadID);
	}

	void DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_DeleteCriticalSection(a_criticalSection);
	}

	void EnterCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_EnterCriticalSection(a_criticalSection);
	}

	std::uint32_t ExpandEnvironmentStringsA(const char* a_src, char* a_dst, std::uint32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_ExpandEnvironmentStringsA(a_src, a_dst, a_dstLen);
	}

	std::uint32_t ExpandEnvironmentStringsW(const wchar_t* a_src, wchar_t* a_dst, std::uint32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_ExpandEnvironmentStringsW(a_src, a_dst, a_dstLen);
	}

	bool FindClose(HANDLE a_file) noexcept
	{
		return ::W32_IMPL_FindClose(a_file);
	}

	HANDLE FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept
	{
		return ::W32_IMPL_FindFirstFileA(a_name, a_data);
	}

	HANDLE FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept
	{
		return ::W32_IMPL_FindFirstFileW(a_name, a_data);
	}

	bool FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept
	{
		return ::W32_IMPL_FindNextFileA(a_file, a_data);
	}

	bool FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept
	{
		return ::W32_IMPL_FindNextFileW(a_file, a_data);
	}

	bool FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept
	{
		return ::W32_IMPL_FlushInstructionCache(a_process, a_baseAddr, a_size);
	}

	bool FreeLibrary(HMODULE a_module) noexcept
	{
		return ::W32_IMPL_FreeLibrary(a_module);
	}

	HMODULE GetCurrentModule() noexcept
	{
		return reinterpret_cast<HMODULE>(std::addressof(__ImageBase));
	}

	HANDLE GetCurrentProcess() noexcept
	{
		return ::W32_IMPL_GetCurrentProcess();
	}

	std::uint32_t GetCurrentThreadId() noexcept
	{
		return ::W32_IMPL_GetCurrentThreadId();
	}

	std::uint32_t GetEnvironmentVariableA(const char* a_name, char* a_buf, std::uint32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetEnvironmentVariableA(a_name, a_buf, a_bufLen);
	}

	std::uint32_t GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetEnvironmentVariableW(a_name, a_buf, a_bufLen);
	}

	std::uint32_t GetLastError() noexcept
	{
		return ::W32_IMPL_GetLastError();
	}

	std::uint32_t GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLen) noexcept
	{
		return ::W32_IMPL_GetModuleFileNameA(a_module, a_name, a_nameLen);
	}

	std::uint32_t GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLen) noexcept
	{
		return ::W32_IMPL_GetModuleFileNameW(a_module, a_name, a_nameLen);
	}

	HMODULE GetModuleHandleA(const char* a_name) noexcept
	{
		return ::W32_IMPL_GetModuleHandleA(a_name);
	}

	HMODULE GetModuleHandleW(const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_GetModuleHandleW(a_name);
	}

	std::uint32_t GetPrivateProfileStringA(const char* a_app, const char* a_key, const char* a_default, char* a_buf, std::uint32_t a_bufLen, const char* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileStringA(a_app, a_key, a_default, a_buf, a_bufLen, a_name);
	}

	std::uint32_t GetPrivateProfileStringW(const wchar_t* a_app, const wchar_t* a_key, const wchar_t* a_default, wchar_t* a_buf, std::uint32_t a_bufLen, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileStringW(a_app, a_key, a_default, a_buf, a_bufLen, a_name);
	}

	void* GetProcAddress(HMODULE a_module, const char* a_name) noexcept
	{
		return ::W32_IMPL_GetProcAddress(a_module, a_name);
	}

	void GetSystemInfo(SYSTEM_INFO* a_info) noexcept
	{
		return ::W32_IMPL_GetSystemInfo(a_info);
	}

	bool IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept
	{
		return (a_ordinal & IMAGE_ORDINAL_FLAG64) != 0;
	}

	IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept
	{
		constexpr auto opt = __builtin_offsetof(IMAGE_NT_HEADERS64, optionalHeader);
		const auto     optSize = a_header->fileHeader.optionalHeaderSize;
		const auto     section = reinterpret_cast<std::uintptr_t>(a_header) + opt + optSize;
		return reinterpret_cast<IMAGE_SECTION_HEADER*>(section);
	}

	bool InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount)
	{
		return ::W32_IMPL_InitializeCriticalSectionAndSpinCount(a_criticalSection, a_spinCount);
	}

	std::uint32_t InterlockedCompareExchange(volatile std::uint32_t* a_target, std::uint32_t a_value, std::uint32_t a_compare) noexcept
	{
		return _InterlockedCompareExchange((volatile long*)a_target, a_value, a_compare);
	}

	std::uint64_t InterlockedCompareExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value, std::uint64_t a_compare) noexcept
	{
		return _InterlockedCompareExchange64((volatile long long*)a_target, a_value, a_compare);
	}

	std::uint32_t InterlockedDecrement(volatile std::uint32_t* a_target) noexcept
	{
		return _InterlockedDecrement((volatile long*)a_target);
	}

	std::uint64_t InterlockedDecrement64(volatile std::uint64_t* a_target) noexcept
	{
		return _InterlockedDecrement64((volatile long long*)a_target);
	}

	std::uint32_t InterlockedExchange(volatile std::uint32_t* a_target, std::uint32_t a_value) noexcept
	{
		return _InterlockedExchange((volatile long*)a_target, a_value);
	}

	std::uint64_t InterlockedExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value) noexcept
	{
		return _InterlockedExchange64((volatile long long*)a_target, a_value);
	}

	std::uint32_t InterlockedIncrement(volatile std::uint32_t* a_target) noexcept
	{
		return _InterlockedIncrement((volatile long*)a_target);
	}

	std::uint64_t InterlockedIncrement64(volatile std::uint64_t* a_target) noexcept
	{
		return _InterlockedIncrement64((volatile long long*)a_target);
	}

	bool IsDebuggerPresent() noexcept
	{
		return ::W32_IMPL_IsDebuggerPresent();
	}

	std::int32_t LCMapStringEx(const wchar_t* a_locale, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen, NLSVERSIONINFO* a_info, void* a_reserved, std::intptr_t a_sortHandle) noexcept
	{
		return ::W32_IMPL_LCMapStringEx(a_locale, a_flags, a_src, a_srcLen, a_dst, a_dstLen, a_info, a_reserved, a_sortHandle);
	}

	void LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_LeaveCriticalSection(a_criticalSection);
	}

	HMODULE LoadLibraryA(const char* a_name) noexcept
	{
		return ::W32_IMPL_LoadLibraryA(a_name);
	}

	HMODULE LoadLibraryW(const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_LoadLibraryW(a_name);
	}

	void* MapViewOfFile(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes) noexcept
	{
		return ::W32_IMPL_MapViewOfFile(a_object, a_desiredAccess, a_fileOffsetHi, a_fileOffsetLo, a_numBytes);
	}

	void* MapViewOfFileEx(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes, void* a_baseAddr) noexcept
	{
		return ::W32_IMPL_MapViewOfFileEx(a_object, a_desiredAccess, a_fileOffsetHi, a_fileOffsetLo, a_numBytes, a_baseAddr);
	}

	std::int32_t MultiByteToWideChar(std::uint32_t a_codePage, std::uint32_t a_flags, const char* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_MultiByteToWideChar(a_codePage, a_flags, a_src, a_srcLen, a_dst, a_dstLen);
	}

	HANDLE OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept
	{
		return ::W32_IMPL_OpenFileMappingA(a_desiredAccess, a_inheritHandle, a_name);
	}

	HANDLE OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_OpenFileMappingW(a_desiredAccess, a_inheritHandle, a_name);
	}

	void OutputDebugStringA(const char* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringA(a_str);
	}

	void OutputDebugStringW(const wchar_t* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringW(a_str);
	}

	bool QueryPerformanceCounter(std::int64_t* a_counter) noexcept
	{
		return ::W32_IMPL_QueryPerformanceCounter(a_counter);
	}

	bool QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept
	{
		return ::W32_IMPL_QueryPerformanceFrequency(a_frequency);
	}

	std::uint32_t ResumeThread(HANDLE a_handle) noexcept
	{
		return ::W32_IMPL_ResumeThread(a_handle);
	}

	bool SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept
	{
		return ::W32_IMPL_SetEnvironmentVariableA(a_name, a_value);
	}

	bool SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept
	{
		return ::W32_IMPL_SetEnvironmentVariableW(a_name, a_value);
	}

	void Sleep(std::uint32_t a_milliseconds) noexcept
	{
		::W32_IMPL_Sleep(a_milliseconds);
	}

	bool TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept
	{
		return ::W32_IMPL_TerminateProcess(a_process, a_exitCode);
	}

	void* TlsGetValue(std::uint32_t a_index) noexcept
	{
		return ::W32_IMPL_TlsGetValue(a_index);
	}

	bool TlsSetValue(std::uint32_t a_index, void* a_value) noexcept
	{
		return ::W32_IMPL_TlsSetValue(a_index, a_value);
	}

	bool UnmapViewOfFile(const void* a_baseAddress) noexcept
	{
		return ::W32_IMPL_UnmapViewOfFile(a_baseAddress);
	}

	void* VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
	{
		return ::W32_IMPL_VirtualAlloc(a_address, a_size, a_type, a_protect);
	}

	void* VirtualAllocEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
	{
		return ::W32_IMPL_VirtualAllocEx(a_process, a_address, a_size, a_type, a_protect);
	}

	bool VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_VirtualFree(a_address, a_size, a_type);
	}

	bool VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_VirtualFreeEx(a_process, a_address, a_size, a_type);
	}

	bool VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept
	{
		return ::W32_IMPL_VirtualProtect(a_address, a_size, a_newProtect, a_oldProtect);
	}

	bool VirtualProtectEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept
	{
		return ::W32_IMPL_VirtualProtectEx(a_process, a_address, a_size, a_newProtect, a_oldProtect);
	}

	std::size_t VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept
	{
		return ::W32_IMPL_VirtualQuery(a_address, a_buf, a_bufLen);
	}

	std::size_t VirtualQueryEx(HANDLE a_process, const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept
	{
		return ::W32_IMPL_VirtualQueryEx(a_process, a_address, a_buf, a_bufLen);
	}

	std::uint32_t WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept
	{
		return ::W32_IMPL_WaitForSingleObject(a_handle, a_milliseconds);
	}

	std::uint32_t WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept
	{
		return ::W32_IMPL_WaitForSingleObjectEx(a_handle, a_milliseconds, a_alertable);
	}

	std::int32_t WideCharToMultiByte(std::uint32_t a_codePage, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, char* a_dst, std::int32_t a_dstLen, const char* a_default, std::int32_t* a_defaultLen)
	{
		return ::W32_IMPL_WideCharToMultiByte(a_codePage, a_flags, a_src, a_srcLen, a_dst, a_dstLen, a_default, a_defaultLen);
	}

	bool WriteProcessMemory(HANDLE a_process, void* a_address, const void* a_buf, std::size_t a_bufLen, std::size_t* a_bufWritten) noexcept
	{
		return ::W32_IMPL_WriteProcessMemory(a_process, a_address, a_buf, a_bufLen, a_bufWritten);
	}
}
