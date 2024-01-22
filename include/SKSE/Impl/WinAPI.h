#pragma once

#ifdef _INC_WINAPIFAMILY
#	error Windows API detected. Please move any Windows API includes after CommonLibSSE, or remove them.
#else

namespace SKSE::WinAPI
{
	// general constants
	inline const auto     INVALID_HANDLE_VALUE{ reinterpret_cast<void*>(static_cast<std::intptr_t>(-1)) };
	inline constexpr auto MAX_PATH{ 260u };

	// standard access
	inline constexpr auto STANDARD_RIGHTS_REQUIRED{ 0x000F0000 };
	inline constexpr auto STANDARD_RIGHTS_ALL{ 0x001F0000 };

	// code page identifiers
	inline constexpr auto CP_UTF8{ 65001u };

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

	// string normalization forms
	inline constexpr auto NORM_FORM_OTHER{ 0x0 };
	inline constexpr auto NORM_FORM_C{ 0x1 };
	inline constexpr auto NORM_FORM_D{ 0x2 };
	inline constexpr auto NORM_FORM_KC{ 0x5 };
	inline constexpr auto NORM_FORM_KD{ 0x6 };

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

	// symbol name undecoration flags
	inline constexpr auto UNDNAME_NO_MS_KEYWORDS{ 0x00000002u };
	inline constexpr auto UNDNAME_NO_FUNCTION_RETURNS{ 0x00000004u };
	inline constexpr auto UNDNAME_NO_ALLOCATION_MODEL{ 0x00000008u };
	inline constexpr auto UNDNAME_NO_ALLOCATION_LANGUAGE{ 0x00000010u };
	inline constexpr auto UNDNAME_NO_THISTYPE{ 0x00000060u };
	inline constexpr auto UNDNAME_NO_ACCESS_SPECIFIERS{ 0x00000080u };
	inline constexpr auto UNDNAME_NO_THROW_SIGNATURES{ 0x00000100u };
	inline constexpr auto UNDNAME_NO_RETURN_UDT_MODEL{ 0x00000400u };
	inline constexpr auto UNDNAME_NAME_ONLY{ 0x00001000u };
	inline constexpr auto UNDNAME_NO_ARGUMENTS{ 0x00002000u };

	using THREAD_START_ROUTINE = std::uint32_t(void* a_param);

	struct CRITICAL_SECTION
	{
	public:
		void*          debugInfo;       // 00
		std::int32_t   lockCount;       // 08
		std::int32_t   recursionCount;  // 0C
		void*          owningThread;    // 10
		void*          lockSemaphore;   // 18
		std::uint64_t* spinCount;       // 20
	};
	static_assert(sizeof(CRITICAL_SECTION) == 0x28);

	struct FILETIME
	{
		std::uint32_t lo;  // 00
		std::uint32_t hi;  // 04
	};
	static_assert(sizeof(FILETIME) == 0x8);

	struct GUID
	{
		std::uint32_t data1;
		std::uint16_t data2;
		std::uint16_t data3;
		std::uint8_t  data4[8];
	};
	static_assert(sizeof(GUID) == 0x10);

	// known folder ids
	inline constexpr GUID FOLDERID_DOCUMENTS{ 0xFDD39AD0u, 0x238Fu, 0x46AFu, 0xADu, 0xB4u, 0x6Cu, 0x85u, 0x48u, 0x03u, 0x69u, 0xC7u };
	inline constexpr GUID FOLDERID_PICTURES{ 0x33E28130u, 0x4E1Eu, 0x4676u, 0x83u, 0x5Au, 0x98u, 0x39u, 0x5Cu, 0x3Bu, 0xC3u, 0xBBu };
	inline constexpr GUID FOLDERID_PROGRAMDATA{ 0x62AB5D82u, 0xFDC1u, 0x4DC3u, 0xA9u, 0xDDu, 0x07u, 0x0Du, 0x1Du, 0x49u, 0x5Du, 0x97u };

	using HRESULT = std::uint32_t;

	struct HWND__;
	using HWND = HWND__*;

	using WNDPROC = std::int32_t(__stdcall*)(HWND, std::uint32_t, std::uint64_t, std::int64_t);

	struct HICON__;
	using HICON = HICON__*;

	struct HINSTANCE__;
	using HINSTANCE = HINSTANCE__*;
	using HMODULE = HINSTANCE;

	struct HKEY__;
	using HKEY = HKEY__*;

	inline auto HKEY_CLASSES_ROOT{ reinterpret_cast<HKEY>(0x80000000ull) };
	inline auto HKEY_CURRENT_USER{ reinterpret_cast<HKEY>(0x80000001ull) };
	inline auto HKEY_LOCAL_MACHINE{ reinterpret_cast<HKEY>(0x80000002ull) };

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
			std::uint64_t forwarderString;  // PBYTE
			std::uint64_t function;         // PDWORD
			std::uint64_t ordinal;
			std::uint64_t address;  // PIMAGE_IMPORT_BY_NAME
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

	struct NLSVERSIONINFO;

	struct POINT
	{
		std::int32_t x;
		std::int32_t y;
	};

	struct PROCESS_INFORMATION
	{
		void*         process;
		void*         thread;
		std::uint32_t processID;
		std::uint32_t threadID;
	};
	static_assert(sizeof(PROCESS_INFORMATION) == 0x18);

	struct RECT
	{
		std::int32_t left;
		std::int32_t top;
		std::int32_t right;
		std::int32_t bottom;
	};

	struct SECURITY_ATTRIBUTES
	{
		std::uint32_t length;
		void*         securityDescriptor;
		bool          inheritHandle;
	};
	static_assert(sizeof(SECURITY_ATTRIBUTES) == 0x18);

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

	union ULARGE_INTEGER
	{
		struct
		{
			std::uint32_t lo;
			std::uint32_t hi;
		};
		std::uint64_t value;
	};

	struct WIN32_FIND_DATAA
	{
		// members
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
		// members
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

	enum VKEnum : std::uint32_t
	{
		VK_LBUTTON = 0x1,
		VK_RBUTTON = 0x2,
		VK_CANCEL = 0x3,
		VK_MBUTTON = 0x4,
		VK_XBUTTON1 = 0x5,
		VK_XBUTTON2 = 0x6,
		VK_BACK = 0x8,
		VK_TAB = 0x9,
		VK_RESERVED_0A = 0xA,
		VK_RESERVED_0B = 0xB,
		VK_CLEAR = 0xC,
		VK_RETURN = 0xD,
		VK_SHIFT = 0x10,
		VK_CONTROL = 0x11,
		VK_MENU = 0x12,
		VK_PAUSE = 0x13,
		VK_CAPITAL = 0x14,
		VK_KANA = 0x15,
		VK_HANGUEL = 0x15,
		VK_HANGUL = 0x15,
		VK_IME_ON = 0x16,
		VK_JUNJA = 0x17,
		VK_FINAL = 0x18,
		VK_HANJA = 0x19,
		VK_KANJI = VK_HANJA,
		VK_IME_OFF = 0x1A,
		VK_ESCAPE = 0x1B,
		VK_CONVERT = 0x1C,
		VK_NONCONVERT = 0x1D,
		VK_ACCEPT = 0x1E,
		VK_MODECHANGE = 0x1F,
		VK_SPACE = 0x20,
		VK_PRIOR = 0x21,
		VK_NEXT = 0x22,
		VK_END = 0x23,
		VK_HOME = 0x24,
		VK_LEFT = 0x25,
		VK_UP = 0x26,
		VK_RIGHT = 0x27,
		VK_DOWN = 0x28,
		VK_SELECT = 0x29,
		VK_PRINT = 0x2A,
		VK_EXECUTE = 0x2B,
		VK_SNAPSHOT = 0x2C,
		VK_INSERT = 0x2D,
		VK_DELETE = 0x2E,
		VK_HELP = 0x2F,
		VK_0 = 0x30,
		VK_1 = 0x31,
		VK_2 = 0x32,
		VK_3 = 0x33,
		VK_4 = 0x34,
		VK_5 = 0x35,
		VK_6 = 0x36,
		VK_7 = 0x37,
		VK_8 = 0x38,
		VK_9 = 0x39,
		VK_A = 0x41,
		VK_B = 0x42,
		VK_C = 0x43,
		VK_D = 0x44,
		VK_E = 0x45,
		VK_F = 0x46,
		VK_G = 0x47,
		VK_H = 0x48,
		VK_I = 0x49,
		VK_J = 0x4A,
		VK_K = 0x4B,
		VK_L = 0x4C,
		VK_M = 0x4D,
		VK_N = 0x4E,
		VK_O = 0x4F,
		VK_P = 0x50,
		VK_Q = 0x51,
		VK_R = 0x52,
		VK_S = 0x53,
		VK_T = 0x54,
		VK_U = 0x55,
		VK_V = 0x56,
		VK_W = 0x57,
		VK_X = 0x58,
		VK_Y = 0x59,
		VK_Z = 0x5A,
		VK_LWIN = 0x5B,
		VK_RWIN = 0x5C,
		VK_APPS = 0x5D,
		VK_RESERVED_5E = 0x5E,
		VK_SLEEP = 0x5F,
		VK_NUMPAD0 = 0x60,
		VK_NUMPAD1 = 0x61,
		VK_NUMPAD2 = 0x62,
		VK_NUMPAD3 = 0x63,
		VK_NUMPAD4 = 0x64,
		VK_NUMPAD5 = 0x65,
		VK_NUMPAD6 = 0x66,
		VK_NUMPAD7 = 0x67,
		VK_NUMPAD8 = 0x68,
		VK_NUMPAD9 = 0x69,
		VK_MULTIPLY = 0x6A,
		VK_ADD = 0x6B,
		VK_SEPARATOR = 0x6C,
		VK_SUBTRACT = 0x6D,
		VK_DECIMAL = 0x6E,
		VK_DIVIDE = 0x6F,
		VK_F1 = 0x70,
		VK_F2 = 0x71,
		VK_F3 = 0x72,
		VK_F4 = 0x73,
		VK_F5 = 0x74,
		VK_F6 = 0x75,
		VK_F7 = 0x76,
		VK_F8 = 0x77,
		VK_F9 = 0x78,
		VK_F10 = 0x79,
		VK_F11 = 0x7A,
		VK_F12 = 0x7B,
		VK_F13 = 0x7C,
		VK_F14 = 0x7D,
		VK_F15 = 0x7E,
		VK_F16 = 0x7F,
		VK_F17 = 0x80,
		VK_F18 = 0x81,
		VK_F19 = 0x82,
		VK_F20 = 0x83,
		VK_F21 = 0x84,
		VK_F22 = 0x85,
		VK_F23 = 0x86,
		VK_F24 = 0x87,
		VK_NUMLOCK = 0x90,
		VK_SCROLL = 0x91,
		VK_OEMSPECIFIC_92 = 0x92,
		VK_OEMSPECIFIC_93 = 0x93,
		VK_OEMSPECIFIC_94 = 0x94,
		VK_OEMSPECIFIC_95 = 0x95,
		VK_OEMSPECIFIC_96 = 0x96,
		VK_LSHIFT = 0xA0,
		VK_RSHIFT = 0xA1,
		VK_LCONTROL = 0xA2,
		VK_RCONTROL = 0xA3,
		VK_LMENU = 0xA4,
		VK_RMENU = 0xA5,
		VK_BROWSER_BACK = 0xA6,
		VK_BROWSER_FORWARD = 0xA7,
		VK_BROWSER_REFRESH = 0xA8,
		VK_BROWSER_STOP = 0xA9,
		VK_BROWSER_SEARCH = 0xAA,
		VK_BROWSER_FAVORITES = 0xAB,
		VK_BROWSER_HOME = 0xAC,
		VK_VOLUME_MUTE = 0xAD,
		VK_VOLUME_DOWN = 0xAE,
		VK_VOLUME_UP = 0xAF,
		VK_MEDIA_NEXT_TRACK = 0xB0,
		VK_MEDIA_PREV_TRACK = 0xB1,
		VK_MEDIA_STOP = 0xB2,
		VK_MEDIA_PLAY_PAUSE = 0xB3,
		VK_LAUNCH_MAIL = 0xB4,
		VK_LAUNCH_MEDIA_SELECT = 0xB5,
		VK_LAUNCH_APP1 = 0xB6,
		VK_LAUNCH_APP2 = 0xB7,
		VK_RESERVED_B8 = 0xB8,
		VK_RESERVED_B9 = 0xB9,
		VK_OEM_1 = 0xBA,
		VK_OEM_PLUS = 0xBB,
		VK_OEM_COMMA = 0xBC,
		VK_OEM_MINUS = 0xBD,
		VK_OEM_PERIOD = 0xBE,
		VK_OEM_2 = 0xBF,
		VK_OEM_3 = 0xC0,
		VK_RESERVED_C1 = 0xC1,
		VK_RESERVED_C2 = 0xC2,
		VK_RESERVED_C3 = 0xC3,
		VK_RESERVED_C4 = 0xC4,
		VK_RESERVED_C5 = 0xC5,
		VK_RESERVED_C6 = 0xC6,
		VK_RESERVED_C7 = 0xC7,
		VK_RESERVED_C8 = 0xC8,
		VK_RESERVED_C9 = 0xC9,
		VK_RESERVED_CA = 0xCA,
		VK_RESERVED_CB = 0xCB,
		VK_RESERVED_CC = 0xCC,
		VK_RESERVED_CD = 0xCD,
		VK_RESERVED_CE = 0xCE,
		VK_RESERVED_CF = 0xCF,
		VK_RESERVED_D0 = 0xD0,
		VK_RESERVED_D1 = 0xD1,
		VK_RESERVED_D2 = 0xD2,
		VK_RESERVED_D3 = 0xD3,
		VK_RESERVED_D4 = 0xD4,
		VK_RESERVED_D5 = 0xD5,
		VK_RESERVED_D6 = 0xD6,
		VK_RESERVED_D7 = 0xD7,
		VK_OEM_4 = 0xDB,
		VK_OEM_5 = 0xDC,
		VK_OEM_6 = 0xDD,
		VK_OEM_7 = 0xDE,
		VK_OEM_8 = 0xDF,
		VK_RESERVED_E0 = 0xE0,
		VK_OEMSPECIFIC_E1 = 0xE1,
		VK_OEM_102 = 0xE2,
		VK_OEMSPECIFIC_E3 = 0xE3,
		VK_OEMSPECIFIC_E4 = 0xE4,
		VK_PROCESSKEY = 0xE5,
		VK_OEMSPECIFIC_E6 = 0xE6,
		VK_PACKET = 0xE7,
		VK_OEMSPECIFIC_E9 = 0xE9,
		VK_OEMSPECIFIC_EA = 0xEA,
		VK_OEMSPECIFIC_EB = 0xEB,
		VK_OEMSPECIFIC_EC = 0xEC,
		VK_OEMSPECIFIC_ED = 0xED,
		VK_OEMSPECIFIC_EE = 0xEE,
		VK_OEMSPECIFIC_EF = 0xEF,
		VK_OEMSPECIFIC_F0 = 0xF0,
		VK_OEMSPECIFIC_F1 = 0xF1,
		VK_OEMSPECIFIC_F2 = 0xF2,
		VK_OEMSPECIFIC_F3 = 0xF3,
		VK_OEMSPECIFIC_F4 = 0xF4,
		VK_OEMSPECIFIC_F5 = 0xF5,
		VK_ATTN = 0xF6,
		VK_CRSEL = 0xF7,
		VK_EXSEL = 0xF8,
		VK_EREOF = 0xF9,
		VK_PLAY = 0xFA,
		VK_ZOOM = 0xFB,
		VK_NONAME = 0xFC,
		VK_PA1 = 0xFD,
		VK_OEM_CLEAR = 0xFE,
		VK_RESERVED_FF = 0xFF
	};

	bool CloseHandle(
		void* a_handle) noexcept;

	void CoTaskMemFree(
		void* a_block) noexcept;

	void* CreateFileMapping(
		void*                a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t        a_protect,
		std::uint32_t        a_maxSizeHigh,
		std::uint32_t        a_maxSizeLow,
		const char*          a_name) noexcept;

	void* CreateFileMapping(
		void*                a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t        a_protect,
		std::uint32_t        a_maxSizeHigh,
		std::uint32_t        a_maxSizeLow,
		const wchar_t*       a_name) noexcept;

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
		PROCESS_INFORMATION* a_procInfo) noexcept;

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
		PROCESS_INFORMATION* a_procInfo) noexcept;

	void* CreateRemoteThread(
		void*                 a_process,
		SECURITY_ATTRIBUTES*  a_threadAttr,
		std::size_t           a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void*                 a_param,
		std::uint32_t         a_flags,
		std::uint32_t*        a_threadID) noexcept;

	void* CreateThread(
		SECURITY_ATTRIBUTES*  a_threadAttr,
		std::size_t           a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void*                 a_param,
		std::uint32_t         a_flags,
		std::uint32_t*        a_threadID) noexcept;

	std::uint32_t ExpandEnvironmentStrings(
		const char*   a_src,
		char*         a_dst,
		std::uint32_t a_dstLen) noexcept;

	std::uint32_t ExpandEnvironmentStrings(
		const wchar_t* a_src,
		wchar_t*       a_dst,
		std::uint32_t  a_dstLen) noexcept;

	[[nodiscard]] bool FindClose(
		void* a_file) noexcept;

	[[nodiscard]] void* FindFirstFile(
		const char*       a_name,
		WIN32_FIND_DATAA* a_data) noexcept;

	[[nodiscard]] void* FindFirstFile(
		const wchar_t*    a_name,
		WIN32_FIND_DATAW* a_data) noexcept;

	[[nodiscard]] bool FindNextFile(
		void*             a_file,
		WIN32_FIND_DATAA* a_data) noexcept;

	[[nodiscard]] bool FindNextFile(
		void*             a_file,
		WIN32_FIND_DATAW* a_data) noexcept;

	bool FlushInstructionCache(
		void*       a_process,
		const void* a_baseAddr,
		std::size_t a_size) noexcept;

	bool FreeLibrary(
		HMODULE a_module) noexcept;

	[[nodiscard]] void* GetCurrentModule() noexcept;

	[[nodiscard]] void* GetCurrentProcess() noexcept;

	[[nodiscard]] std::uint32_t GetCurrentThreadID() noexcept;

	[[nodiscard]] std::uint32_t GetEnvironmentVariable(
		const char*   a_name,
		char*         a_buffer,
		std::uint32_t a_size) noexcept;

	[[nodiscard]] std::uint32_t GetEnvironmentVariable(
		const wchar_t* a_name,
		wchar_t*       a_buffer,
		std::uint32_t  a_size) noexcept;

	[[nodiscard]] bool GetFileVersionInfo(
		const char*   a_name,
		std::uint32_t a_handle,
		std::uint32_t a_dataLen,
		void*         a_data) noexcept;

	[[nodiscard]] bool GetFileVersionInfo(
		const wchar_t* a_name,
		std::uint32_t  a_handle,
		std::uint32_t  a_dataLen,
		void*          a_data) noexcept;

	[[nodiscard]] std::uint32_t GetFileVersionInfoSize(
		const char*    a_name,
		std::uint32_t* a_handle) noexcept;

	[[nodiscard]] std::uint32_t GetFileVersionInfoSize(
		const wchar_t* a_name,
		std::uint32_t* a_handle) noexcept;

	[[nodiscard]] std::int32_t GetKeyNameText(
		std::int32_t a_param,
		char*        a_buffer,
		std::int32_t a_bufferLen) noexcept;

	[[nodiscard]] std::int32_t GetKeyNameText(
		std::int32_t a_param,
		wchar_t*     a_buffer,
		std::int32_t a_bufferLen) noexcept;

	[[nodiscard]] std::int16_t GetKeyState(
		std::int32_t a_key) noexcept;

	[[nodiscard]] std::uint32_t GetLastError() noexcept;

	[[nodiscard]] std::size_t GetMaxPath() noexcept;

	[[nodiscard]] std::uint32_t GetModuleFileName(
		void*         a_module,
		char*         a_name,
		std::uint32_t a_nameLen) noexcept;

	[[nodiscard]] std::uint32_t GetModuleFileName(
		void*         a_module,
		wchar_t*      a_name,
		std::uint32_t a_nameLen) noexcept;

	[[nodiscard]] HMODULE GetModuleHandle(
		const char* a_name) noexcept;

	[[nodiscard]] HMODULE GetModuleHandle(
		const wchar_t* a_name) noexcept;

	[[nodiscard]] std::uint32_t GetPrivateProfileString(
		const char*   a_app,
		const char*   a_key,
		const char*   a_default,
		char*         a_out,
		std::uint32_t a_outLen,
		const char*   a_name) noexcept;

	[[nodiscard]] std::uint32_t GetPrivateProfileString(
		const wchar_t* a_app,
		const wchar_t* a_key,
		const wchar_t* a_default,
		wchar_t*       a_out,
		std::uint32_t  a_outLen,
		const wchar_t* a_name) noexcept;

	[[nodiscard]] void* GetProcAddress(
		void*       a_module,
		const char* a_name) noexcept;

	[[nodiscard]] std::string_view GetProcPath(
		HMODULE a_handle) noexcept;

	void GetSystemInfo(
		SYSTEM_INFO* a_info) noexcept;

	[[nodiscard]] bool IMAGE_SNAP_BY_ORDINAL64(
		std::uint64_t a_ordinal) noexcept;

	[[nodiscard]] IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(
		const IMAGE_NT_HEADERS64* a_header) noexcept;

	[[nodiscard]] bool IsDebuggerPresent() noexcept;

	std::int32_t LCMapStringEx(
		const wchar_t*  a_locale,
		std::uint32_t   a_flags,
		const wchar_t*  a_src,
		std::int32_t    a_srcLen,
		wchar_t*        a_dest,
		std::int32_t    a_destLen,
		NLSVERSIONINFO* a_info,
		void*           a_reserved,
		std::intptr_t   a_sortHandle) noexcept;

	[[nodiscard]] HMODULE LoadLibrary(
		const char* a_name) noexcept;

	[[nodiscard]] HMODULE LoadLibrary(
		const wchar_t* a_name) noexcept;

	[[nodiscard]] void* MapViewOfFile(
		void*         a_object,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_fileOffsetHigh,
		std::uint32_t a_fileOffsetLow,
		std::size_t   a_numBytesToMap) noexcept;

	[[nodiscard]] void* MapViewOfFileEx(
		void*         a_object,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_fileOffsetHigh,
		std::uint32_t a_fileOffsetLow,
		std::size_t   a_numBytesToMap,
		void*         a_baseAddress) noexcept;

	std::int32_t MessageBox(
		void*         a_wnd,
		const char*   a_text,
		const char*   a_caption,
		std::uint32_t a_type) noexcept;

	std::int32_t MessageBox(
		void*          a_wnd,
		const wchar_t* a_text,
		const wchar_t* a_caption,
		std::uint32_t  a_type) noexcept;

	[[nodiscard]] std::int32_t MultiByteToWideChar(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const char*   a_str,
		std::int32_t  a_strLen,
		wchar_t*      a_wstr,
		std::int32_t  a_wstrLen);

	[[nodiscard]] std::int32_t NormalizeString(
		std::int32_t   a_normForm,
		const wchar_t* a_src,
		std::int32_t   a_srcLen,
		wchar_t*       a_dest,
		std::int32_t   a_destLen);

	[[nodiscard]] void* OpenFileMapping(
		std::uint32_t a_desiredAccess,
		bool          a_inheritHandle,
		const char*   a_name) noexcept;

	[[nodiscard]] void* OpenFileMapping(
		std::uint32_t  a_desiredAccess,
		bool           a_inheritHandle,
		const wchar_t* a_name) noexcept;

	void OutputDebugString(
		const char* a_outStr) noexcept;

	void OutputDebugString(
		const wchar_t* a_outStr) noexcept;

	std::int32_t RegGetValue(
		HKEY           a_key,
		const char*    a_subKey,
		const char*    a_value,
		std::uint32_t  a_flags,
		std::uint32_t* a_type,
		void*          a_data,
		std::uint32_t* a_dataLen);

	std::int32_t RegGetValue(
		HKEY           a_key,
		const wchar_t* a_subKey,
		const wchar_t* a_value,
		std::uint32_t  a_flags,
		std::uint32_t* a_type,
		void*          a_data,
		std::uint32_t* a_dataLen);

	std::uint32_t ResumeThread(
		void* a_handle) noexcept;

	bool SetEnvironmentVariable(
		const char* a_name,
		const char* a_value) noexcept;

	bool SetEnvironmentVariable(
		const wchar_t* a_name,
		const wchar_t* a_value) noexcept;

	[[nodiscard]] std::int32_t SHGetKnownFolderPath(
		const GUID&   a_id,
		std::uint32_t a_flags,
		void*         a_token,
		wchar_t**     a_path) noexcept;

	[[nodiscard]] std::int32_t ShowCursor(
		bool a_show) noexcept;

	void Sleep(
		std::uint32_t a_milliseconds) noexcept;

	bool TerminateProcess(
		void*         a_process,
		std::uint32_t a_exitCode) noexcept;

	[[nodiscard]] void* TlsGetValue(
		std::uint32_t a_index) noexcept;

	bool TlsSetValue(
		std::uint32_t a_index,
		void*         a_value) noexcept;

	[[nodiscard]] std::uint32_t UnDecorateSymbolName(
		const char*   a_name,
		char*         a_out,
		std::uint32_t a_outLenMax,
		std::uint32_t a_flags) noexcept;

	[[nodiscard]] std::uint32_t UnDecorateSymbolName(
		const wchar_t* a_name,
		wchar_t*       a_out,
		std::uint32_t  a_outLenMax,
		std::uint32_t  a_flags) noexcept;

	bool UnmapViewOfFile(
		const void* a_baseAddress) noexcept;

	bool VerQueryValue(
		const void*    a_block,
		const char*    a_subBlock,
		void**         a_buffer,
		std::uint32_t* a_bufferLen) noexcept;

	bool VerQueryValue(
		const void*    a_block,
		const wchar_t* a_subBlock,
		void**         a_buffer,
		std::uint32_t* a_bufferLen) noexcept;

	void* VirtualAlloc(
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept;

	void* VirtualAllocEx(
		void*         a_process,
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept;

	bool VirtualFree(
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type) noexcept;

	bool VirtualFreeEx(
		void*         a_process,
		void*         a_address,
		std::size_t   a_size,
		std::uint32_t a_type) noexcept;

	bool VirtualProtect(
		void*          a_address,
		std::size_t    a_size,
		std::uint32_t  a_newProtect,
		std::uint32_t* a_oldProtect) noexcept;

	bool VirtualProtectEx(
		void*          a_process,
		void*          a_address,
		std::size_t    a_size,
		std::uint32_t  a_newProtect,
		std::uint32_t* a_oldProtect) noexcept;

	[[nodiscard]] std::size_t VirtualQuery(
		const void*               a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t               a_bufferLen) noexcept;

	[[nodiscard]] std::size_t VirtualQueryEx(
		void*                     a_process,
		const void*               a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t               a_bufferLen) noexcept;

	[[nodiscard]] std::uint32_t WaitForSingleObject(
		void*         a_handle,
		std::uint32_t a_milliseconds) noexcept;

	[[nodiscard]] std::uint32_t WaitForSingleObjectEx(
		void*         a_handle,
		std::uint32_t a_milliseconds,
		bool          a_alertable) noexcept;

	[[nodiscard]] std::int32_t WideCharToMultiByte(
		std::uint32_t  a_codePage,
		std::uint32_t  a_flags,
		const wchar_t* a_wstr,
		std::int32_t   a_wstrLen,
		char*          a_str,
		std::int32_t   a_strLen,
		const char*    a_default,
		std::int32_t*  a_defaultLen);

	bool WriteProcessMemory(
		void*        a_process,
		void*        a_address,
		const void*  a_buffer,
		std::size_t  a_bufferLen,
		std::size_t* a_bufferWritten) noexcept;
}

#endif  // _INC_WINAPIFAMILY

namespace RE::DirectX
{
	struct XMFLOAT4X4
	{
		// members
		float m[4][4];
	};
	static_assert(sizeof(XMFLOAT4X4) == 0x40);

	struct DXGI_RATIONAL
	{
		// members
		std::uint32_t numerator;    // 00
		std::uint32_t denominator;  // 04
	};
	static_assert(sizeof(DXGI_RATIONAL) == 0x08);

	enum DXGI_MODE_SCALING : std::uint32_t
	{
		DXGI_MODE_SCALING_UNSPECIFIED = 0,
		DXGI_MODE_SCALING_CENTERED = 1,
		DXGI_MODE_SCALING_STRETCHED = 2
	};

	enum DXGI_MODE_SCANLINE_ORDER : std::uint32_t
	{
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
		DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
		DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
	};
}
