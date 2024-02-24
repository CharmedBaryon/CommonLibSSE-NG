#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	// standard access
	inline constexpr auto STANDARD_RIGHTS_REQUIRED{ 0x000F0000 };
	inline constexpr auto STANDARD_RIGHTS_ALL{ 0x001F0000 };

	// code page identifiers
	inline constexpr auto CP_UTF8{ 65001u };

	// memory allocation types
	inline constexpr auto MEM_COMMIT{ 0x00001000u };
	inline constexpr auto MEM_RESERVE{ 0x00002000u };
	inline constexpr auto MEM_DECOMMIT{ 0x00004000u };
	inline constexpr auto MEM_RELEASE{ 0x00008000u };
	inline constexpr auto MEM_FREE{ 0x00010000u };
	inline constexpr auto MEM_RESET{ 0x00080000u };
	inline constexpr auto MEM_RESET_UNDO{ 0x01000000u };

	// memory page protection attributes
	inline constexpr auto PAGE_NOACCESS{ 0x00000001u };
	inline constexpr auto PAGE_READONLY{ 0x00000002u };
	inline constexpr auto PAGE_READWRITE{ 0x00000004u };
	inline constexpr auto PAGE_WRITECOPY{ 0x00000008u };
	inline constexpr auto PAGE_EXECUTE{ 0x00000010u };
	inline constexpr auto PAGE_EXECUTE_READ{ 0x00000020u };
	inline constexpr auto PAGE_EXECUTE_READWRITE{ 0x00000040u };

	// memory section
	inline constexpr auto SECTION_QUERY{ 0x00000001 };
	inline constexpr auto SECTION_MAP_WRITE{ 0x00000002 };
	inline constexpr auto SECTION_MAP_READ{ 0x00000004 };
	inline constexpr auto SECTION_MAP_EXECUTE{ 0x00000008 };
	inline constexpr auto SECTION_EXTEND_SIZE{ 0x00000010 };
	inline constexpr auto SECTION_MAP_EXECUTE_EXPLICIT{ 0x00000020 };
	inline constexpr auto SECTION_ALL_ACCESS{
		STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_WRITE | SECTION_MAP_READ | SECTION_MAP_EXECUTE | SECTION_EXTEND_SIZE
	};

	// file attributes
	inline constexpr auto FILE_ATTRIBUTE_READONLY{ 0x00000001u };
	inline constexpr auto FILE_ATTRIBUTE_HIDDEN{ 0x00000002u };
	inline constexpr auto FILE_ATTRIBUTE_SYSTEM{ 0x00000004u };
	inline constexpr auto FILE_ATTRIBUTE_DIRECTORY{ 0x00000010u };
	inline constexpr auto FILE_ATTRIBUTE_ARCHIVE{ 0x00000020u };

	// file mapping flags
	inline constexpr auto FILE_MAP_ALL_ACCESS{ SECTION_ALL_ACCESS };
	inline constexpr auto FILE_MAP_COPY{ 0x00000001u };
	inline constexpr auto FILE_MAP_WRITE{ 0x00000002u };
	inline constexpr auto FILE_MAP_READ{ 0x00000004u };
	inline constexpr auto FILE_MAP_EXECUTE{ 0x00000020u };
	inline constexpr auto FILE_MAP_LARGE_PAGES{ 0x20000000u };
	inline constexpr auto FILE_MAP_TARGETS_INVALID{ 0x40000000u };
	inline constexpr auto FILE_MAP_RESERVE{ 0x80000000u };

	// file open mode flags
	inline constexpr auto GENERIC_READ{ 0x80000000L };
	inline constexpr auto GENERIC_WRITE{ 0x40000000L };
	inline constexpr auto GENERIC_EXECUTE{ 0x20000000L };
	inline constexpr auto GENERIC_ALL{ 0x10000000L };

	// pe image header
	inline constexpr auto IMAGE_DOS_SIGNATURE{ 0x5A4Du };
	inline constexpr auto IMAGE_NT_SIGNATURE{ 0x00004550u };
	inline constexpr auto IMAGE_NT_OPTIONAL_HDR32_MAGIC{ 0x10Bu };
	inline constexpr auto IMAGE_NT_OPTIONAL_HDR64_MAGIC{ 0x20Bu };

	// pe image directory entries
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_EXPORT{ 0u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_IMPORT{ 1u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_RESOURCE{ 2u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_EXCEPTION{ 3u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_SECURITY{ 4u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_BASERELOC{ 5u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_DEBUG{ 6u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_ARCHITECTURE{ 7u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_GLOBALPTR{ 8u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_TLS{ 9u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG{ 10u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT{ 11u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_IAT{ 12u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT{ 13u };
	inline constexpr auto IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR{ 14u };
	inline constexpr auto IMAGE_NUMBEROF_DIRECTORY_ENTRIES{ 16u };

	// pe image ordinal
	inline constexpr auto IMAGE_ORDINAL_FLAG32{ 0x80000000u };
	inline constexpr auto IMAGE_ORDINAL_FLAG64{ 0x8000000000000000ull };

	// pe image section header characteristics
	inline constexpr auto IMAGE_SCN_MEM_SHARED{ 0x10000000u };
	inline constexpr auto IMAGE_SCN_MEM_EXECUTE{ 0x20000000u };
	inline constexpr auto IMAGE_SCN_MEM_READ{ 0x40000000u };
	inline constexpr auto IMAGE_SCN_MEM_WRITE{ 0x80000000u };
	inline constexpr auto IMAGE_SIZEOF_SECTION_HEADER{ 40u };
	inline constexpr auto IMAGE_SIZEOF_SHORT_NAME{ 8u };

	// process creation flags
	inline constexpr auto DEBUG_PROCESS{ 0x00000001u };
	inline constexpr auto DEBUG_ONLY_THIS_PROCESS{ 0x00000002u };
	inline constexpr auto CREATE_SUSPENDED{ 0x00000004u };
	inline constexpr auto DETACHED_PROCESS{ 0x00000008u };
	inline constexpr auto CREATE_NEW_CONSOLE{ 0x00000010u };
	inline constexpr auto NORMAL_PRIORITY_CLASS{ 0x00000020u };
	inline constexpr auto IDLE_PRIORITY_CLASS{ 0x00000040u };
	inline constexpr auto HIGH_PRIORITY_CLASS{ 0x00000080u };
	inline constexpr auto REALTIME_PRIORITY_CLASS{ 0x00000100u };
	inline constexpr auto CREATE_NEW_PROCESS_GROUP{ 0x00000200u };
	inline constexpr auto CREATE_UNICODE_ENVIRONMENT{ 0x00000400u };
	inline constexpr auto CREATE_FORCEDOS{ 0x00002000u };
	inline constexpr auto BELOW_NORMAL_PRIORITY_CLASS{ 0x00004000u };
	inline constexpr auto ABOVE_NORMAL_PRIORITY_CLASS{ 0x00008000u };
	inline constexpr auto INHERIT_PARENT_AFFINITY{ 0x00010000u };
	inline constexpr auto CREATE_PROTECTED_PROCESS{ 0x00040000u };
	inline constexpr auto EXTENDED_STARTUPINFO_PRESENT{ 0x00080000u };
	inline constexpr auto PROCESS_MODE_BACKGROUND_BEGIN{ 0x00100000u };
	inline constexpr auto PROCESS_MODE_BACKGROUND_END{ 0x00200000u };
	inline constexpr auto CREATE_SECURE_PROCESS{ 0x00400000 };
	inline constexpr auto CREATE_BREAKAWAY_FROM_JOB{ 0x01000000u };
	inline constexpr auto CREATE_PRESERVE_CODE_AUTHZ_LEVEL{ 0x02000000u };
	inline constexpr auto CREATE_DEFAULT_ERROR_MODE{ 0x04000000u };
	inline constexpr auto CREATE_NO_WINDOW{ 0x08000000u };

	// locale map flags
	inline constexpr auto LCMAP_LOWERCASE{ 0x00000100u };
	inline constexpr auto LCMAP_UPPERCASE{ 0x00000200u };
	inline constexpr auto LCMAP_TITLECASE{ 0x00000300u };
	inline constexpr auto LCMAP_SORTKEY{ 0x00000400u };
	inline constexpr auto LCMAP_BYTEREV{ 0x00000800u };
	inline constexpr auto LCMAP_HIRAGANA{ 0x00100000u };
	inline constexpr auto LCMAP_KATAKANA{ 0x00200000u };
	inline constexpr auto LCMAP_HALFWIDTH{ 0x00400000u };
	inline constexpr auto LCMAP_FULLWIDTH{ 0x00800000u };
	inline constexpr auto LCMAP_LINGUISTIC_CASING{ 0x01000000u };
	inline constexpr auto LCMAP_SIMPLIFIED_CHINESE{ 0x02000000u };
	inline constexpr auto LCMAP_TRADITIONAL_CHINESE{ 0x04000000u };

	// locale names
	inline constexpr auto LOCALE_NAME_USER_DEFAULT{ nullptr };
	inline constexpr auto LOCALE_NAME_INVARIANT{ L"" };
	inline constexpr auto LOCALE_NAME_SYSTEM_DEFAULT{ L"!x-sys-default-locale" };
}

namespace REX::W32
{
	struct IMAGE_DATA_DIRECTORY
	{
		std::uint32_t virtualAddress;
		std::uint32_t size;
	};
	static_assert(sizeof(IMAGE_DATA_DIRECTORY) == 0x8);

	struct IMAGE_DOS_HEADER
	{
		std::uint16_t magic;
		std::uint16_t cblp;
		std::uint16_t cp;
		std::uint16_t crlc;
		std::uint16_t cparhdr;
		std::uint16_t minalloc;
		std::uint16_t maxalloc;
		std::uint16_t ss;
		std::uint16_t sp;
		std::uint16_t csum;
		std::uint16_t ip;
		std::uint16_t cs;
		std::uint16_t lfarlc;
		std::uint16_t ovno;
		std::uint16_t res[4];
		std::uint16_t oemid;
		std::uint16_t oeminfo;
		std::uint16_t res2[10];
		std::int32_t  lfanew;
	};
	static_assert(sizeof(IMAGE_DOS_HEADER) == 0x40);

	struct IMAGE_FILE_HEADER
	{
		std::uint16_t machine;
		std::uint16_t sectionCount;
		std::uint32_t timeDateStamp;
		std::uint32_t symbolTablePtr;
		std::uint32_t symbolCount;
		std::uint16_t optionalHeaderSize;
		std::uint16_t characteristics;
	};
	static_assert(sizeof(IMAGE_FILE_HEADER) == 0x14);

	struct IMAGE_IMPORT_BY_NAME
	{
		std::uint16_t hint;
		char          name[1];
	};
	static_assert(sizeof(IMAGE_IMPORT_BY_NAME) == 0x4);

	struct IMAGE_IMPORT_DESCRIPTOR
	{
		union
		{
			std::uint32_t characteristics;
			std::uint32_t firstThunkOriginal;
		};

		std::uint32_t timeDateStamp;
		std::uint32_t forwarderChain;
		std::uint32_t name;
		std::uint32_t firstThunk;
	};
	static_assert(sizeof(IMAGE_IMPORT_DESCRIPTOR) == 0x14);

	struct IMAGE_OPTIONAL_HEADER64
	{
		std::uint16_t        magic;
		std::uint8_t         linkerVersionMajor;
		std::uint8_t         linkerVersionMinor;
		std::uint32_t        codeSize;
		std::uint32_t        initializedDataSize;
		std::uint32_t        uninitializedDataSize;
		std::uint32_t        entryPointAddress;
		std::uint32_t        codeBase;
		std::uint64_t        imageBase;
		std::uint32_t        sectionAlignment;
		std::uint32_t        fileAlignment;
		std::uint16_t        osVersionMajor;
		std::uint16_t        osVersionMinor;
		std::uint16_t        imageVersionMajor;
		std::uint16_t        imageVersionMinor;
		std::uint16_t        subsystemVersionMajor;
		std::uint16_t        subsystemVersionMinor;
		std::uint32_t        win32Version;
		std::uint32_t        imageSize;
		std::uint32_t        headersSize;
		std::uint32_t        checksum;
		std::uint16_t        subsystem;
		std::uint16_t        dllCharacteristics;
		std::uint64_t        stackReserveSize;
		std::uint64_t        stackCommitSize;
		std::uint64_t        heapReserveSize;
		std::uint64_t        heapCommitSize;
		std::uint32_t        loaderFlags;
		std::uint32_t        rvaAndSizesCount;
		IMAGE_DATA_DIRECTORY dataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
	};
	static_assert(sizeof(IMAGE_OPTIONAL_HEADER64) == 0xF0);

	struct IMAGE_NT_HEADERS64
	{
		std::uint32_t           signature;
		IMAGE_FILE_HEADER       fileHeader;
		IMAGE_OPTIONAL_HEADER64 optionalHeader;
	};
	static_assert(sizeof(IMAGE_NT_HEADERS64) == 0x108);

	struct IMAGE_SECTION_HEADER
	{
		std::uint8_t name[IMAGE_SIZEOF_SHORT_NAME];
		union
		{
			std::uint32_t physicalAddress;
			std::uint32_t virtualSize;
		};
		std::uint32_t virtualAddress;
		std::uint32_t rawDataSize;
		std::uint32_t rawDataPtr;
		std::uint32_t relocationsPtr;
		std::uint32_t lineNumbersPtr;
		std::uint16_t relocationsCount;
		std::uint16_t lineNumbersCount;
		std::uint32_t characteristics;
	};
	static_assert(sizeof(IMAGE_SECTION_HEADER) == 0x28);

	struct IMAGE_THUNK_DATA64
	{
		union
		{
			std::uint64_t forwarderString;
			std::uint64_t function;
			std::uint64_t ordinal;
			std::uint64_t address;
		};
	};
	static_assert(sizeof(IMAGE_THUNK_DATA64) == 0x8);

	struct MEMORY_BASIC_INFORMATION
	{
		void*         baseAddress;
		void*         allocationBase;
		std::uint32_t allocationProtect;
		std::uint16_t partitionID;
		std::size_t   regionSize;
		std::uint32_t state;
		std::uint32_t protect;
		std::uint32_t type;
	};
	static_assert(sizeof(MEMORY_BASIC_INFORMATION) == 0x30);

	struct NLSVERSIONINFO
	{
		std::uint32_t nlsVersionInfoSize;
		std::uint32_t nlsVersion;
		std::uint32_t definedVersion;
		std::uint32_t effectiveID;
		GUID          guidCustomVersion;
	};
	static_assert(sizeof(NLSVERSIONINFO) == 0x20);

	struct PROCESS_INFORMATION
	{
		void*         process;
		void*         thread;
		std::uint32_t processID;
		std::uint32_t threadID;
	};
	static_assert(sizeof(PROCESS_INFORMATION) == 0x18);

	struct STARTUPINFOA
	{
		std::uint32_t size;
		char*         reserved0;
		char*         desktop;
		char*         title;
		std::uint32_t x;
		std::uint32_t y;
		std::uint32_t xSize;
		std::uint32_t ySize;
		std::uint32_t xCountChars;
		std::uint32_t yCountChars;
		std::uint32_t fillAttribute;
		std::uint32_t flags;
		std::uint16_t showWindow;
		std::uint16_t reserved1;
		std::uint8_t* reserved2;
		void*         stdIn;
		void*         stdOut;
		void*         stdErr;
	};
	static_assert(sizeof(STARTUPINFOA) == 0x68);

	struct STARTUPINFOW
	{
		std::uint32_t size;
		wchar_t*      reserved0;
		wchar_t*      desktop;
		wchar_t*      title;
		std::uint32_t x;
		std::uint32_t y;
		std::uint32_t xSize;
		std::uint32_t ySize;
		std::uint32_t xCountChars;
		std::uint32_t yCountChars;
		std::uint32_t fillAttribute;
		std::uint32_t flags;
		std::uint16_t showWindow;
		std::uint16_t reserved1;
		std::uint8_t* reserved2;
		void*         stdIn;
		void*         stdOut;
		void*         stdErr;
	};
	static_assert(sizeof(STARTUPINFOW) == 0x68);

	struct SYSTEM_INFO
	{
		union
		{
			std::uint32_t oemID;
			struct
			{
				std::uint16_t processorArch;
				std::uint16_t reserved;
			};
		};
		std::uint32_t  pageSize;
		void*          appAddressMin;
		void*          appAddressMax;
		std::uintptr_t processorActiveMask;
		std::uint32_t  processorCount;
		std::uint32_t  processorType;
		std::uint32_t  allocationGranularity;
		std::uint16_t  processorLevel;
		std::uint16_t  processorRevision;
	};
	static_assert(sizeof(SYSTEM_INFO) == 0x30);

	struct WIN32_FIND_DATAA
	{
		std::uint32_t fileAttributes;
		FILETIME      creationTime;
		FILETIME      lastAccessTime;
		FILETIME      lastWriteTime;
		std::uint32_t fileSizeHi;
		std::uint32_t fileSizeLo;
		std::uint32_t reserved0;
		std::uint32_t reserved1;
		char          fileName[MAX_PATH];
		char          fileNameAlt[14];
	};
	static_assert(sizeof(WIN32_FIND_DATAA) == 0x140);

	struct WIN32_FIND_DATAW
	{
		std::uint32_t fileAttributes;
		FILETIME      creationTime;
		FILETIME      lastAccessTime;
		FILETIME      lastWriteTime;
		std::uint32_t fileSizeHi;
		std::uint32_t fileSizeLo;
		std::uint32_t reserved0;
		std::uint32_t reserved1;
		wchar_t       fileName[MAX_PATH];
		wchar_t       fileNameAlt[14];
	};
	static_assert(sizeof(WIN32_FIND_DATAW) == 0x250);
}

namespace REX::W32
{
	using THREAD_START_ROUTINE = std::uint32_t(void* a_param);
}

namespace REX::W32
{
	bool                  CloseHandle(HANDLE a_handle) noexcept;
	HANDLE                CreateFileMappingA(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const char* a_name) noexcept;
	HANDLE                CreateFileMappingW(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const wchar_t* a_name) noexcept;
	bool                  CreateProcessA(const char* a_name, char* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const char* a_curDir, STARTUPINFOA* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept;
	bool                  CreateProcessW(const wchar_t* a_name, wchar_t* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const wchar_t* a_curDir, STARTUPINFOW* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept;
	HANDLE                CreateRemoteThread(HANDLE a_process, SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept;
	HANDLE                CreateSemaphoreA(SECURITY_ATTRIBUTES* a_semaphoreAttr, std::int32_t a_initCount, std::int32_t a_maxCount, const char* a_name);
	HANDLE                CreateThread(SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept;
	void                  DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection);
	void                  EnterCriticalSection(CRITICAL_SECTION* a_criticalSection);
	std::uint32_t         ExpandEnvironmentStrings(const char* a_src, char* a_dst, std::uint32_t a_dstLen) noexcept;
	std::uint32_t         ExpandEnvironmentStrings(const wchar_t* a_src, wchar_t* a_dst, std::uint32_t a_dstLen) noexcept;
	bool                  FindClose(HANDLE a_file) noexcept;
	HANDLE                FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept;
	HANDLE                FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept;
	bool                  FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept;
	bool                  FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept;
	bool                  FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept;
	bool                  FreeLibrary(HMODULE a_module) noexcept;
	HMODULE               GetCurrentModule() noexcept;
	HANDLE                GetCurrentProcess() noexcept;
	std::uint32_t         GetCurrentThreadId() noexcept;
	std::uint32_t         GetEnvironmentVariableA(const char* a_name, char* a_buf, std::uint32_t a_bufLen) noexcept;
	std::uint32_t         GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen) noexcept;
	std::uint32_t         GetLastError() noexcept;
	std::uint32_t         GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLen) noexcept;
	std::uint32_t         GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLen) noexcept;
	HMODULE               GetModuleHandleA(const char* a_name) noexcept;
	HMODULE               GetModuleHandleW(const wchar_t* a_name) noexcept;
	std::uint32_t         GetPrivateProfileStringA(const char* a_app, const char* a_key, const char* a_default, char* a_buf, std::uint32_t a_bufLen, const char* a_name) noexcept;
	std::uint32_t         GetPrivateProfileStringW(const wchar_t* a_app, const wchar_t* a_key, const wchar_t* a_default, wchar_t* a_buf, std::uint32_t a_bufLen, const wchar_t* a_name) noexcept;
	void*                 GetProcAddress(HMODULE a_module, const char* a_name) noexcept;
	void                  GetSystemInfo(SYSTEM_INFO* a_info) noexcept;
	bool                  IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept;
	IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept;
	bool                  InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount);
	std::uint32_t         InterlockedCompareExchange(volatile std::uint32_t* a_target, std::uint32_t a_value, std::uint32_t a_compare) noexcept;
	std::uint64_t         InterlockedCompareExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value, std::uint64_t a_compare) noexcept;
	std::uint32_t         InterlockedDecrement(volatile std::uint32_t* a_target) noexcept;
	std::uint64_t         InterlockedDecrement64(volatile std::uint64_t* a_target) noexcept;
	std::uint32_t         InterlockedExchange(volatile std::uint32_t* a_target, std::uint32_t a_value) noexcept;
	std::uint64_t         InterlockedExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value) noexcept;
	std::uint32_t         InterlockedIncrement(volatile std::uint32_t* a_target) noexcept;
	std::uint64_t         InterlockedIncrement64(volatile std::uint64_t* a_target) noexcept;
	bool                  IsDebuggerPresent() noexcept;
	std::int32_t          LCMapStringEx(const wchar_t* a_locale, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen, NLSVERSIONINFO* a_info, void* a_reserved, std::intptr_t a_sortHandle) noexcept;
	void                  LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection);
	HMODULE               LoadLibraryA(const char* a_name) noexcept;
	HMODULE               LoadLibraryW(const wchar_t* a_name) noexcept;
	void*                 MapViewOfFile(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes) noexcept;
	void*                 MapViewOfFileEx(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes, void* a_baseAddr) noexcept;
	std::int32_t          MultiByteToWideChar(std::uint32_t a_codePage, std::uint32_t a_flags, const char* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen) noexcept;
	HANDLE                OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept;
	HANDLE                OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept;
	void                  OutputDebugStringA(const char* a_str) noexcept;
	void                  OutputDebugStringW(const wchar_t* a_str) noexcept;
	bool                  QueryPerformanceCounter(std::int64_t* a_counter) noexcept;
	bool                  QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept;
	std::uint32_t         ResumeThread(HANDLE a_handle) noexcept;
	bool                  SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept;
	bool                  SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept;
	void                  Sleep(std::uint32_t a_milliseconds) noexcept;
	bool                  TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept;
	void*                 TlsGetValue(std::uint32_t a_index) noexcept;
	bool                  TlsSetValue(std::uint32_t a_index, void* a_value) noexcept;
	bool                  UnmapViewOfFile(const void* a_baseAddress) noexcept;
	void*                 VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept;
	void*                 VirtualAllocEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept;
	bool                  VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept;
	bool                  VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept;
	bool                  VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept;
	bool                  VirtualProtectEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept;
	std::size_t           VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept;
	std::size_t           VirtualQueryEx(HANDLE a_process, const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept;
	std::uint32_t         WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept;
	std::uint32_t         WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept;
	std::int32_t          WideCharToMultiByte(std::uint32_t a_codePage, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, char* a_dst, std::int32_t a_dstLen, const char* a_default, std::int32_t* a_defaultLen);
	bool                  WriteProcessMemory(HANDLE a_process, void* a_address, const void* a_buf, std::size_t a_bufLen, std::size_t* a_bufWritten) noexcept;
}
