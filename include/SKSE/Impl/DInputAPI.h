#pragma once

#include "WinAPI.h"

// TODO: This should probably be behind some sort of pragma that allows linking with dinput and dinput8
namespace RE::DirectInput8
{
	namespace WinAPI = SKSE::WinAPI;

	using DWORD = std::uint32_t;
	using LONG = std::int32_t;
	using WORD = std::uint16_t;
	using BYTE = std::uint8_t;
	using UINT = std::uint32_t;
	using CHAR = char;

	using LPSTR = char*;
	using LPCSTR = const char*;

	using UINT_PTR = std::uintptr_t;
	using HANDLE = void*;
	using LPDWORD = DWORD*;
	using LPVOID = void*;
	using LPLONG = LONG*;
	using LPWORD = WORD*;

	using GUID = SKSE::WinAPI::GUID;
	using LPGUID = GUID*;
	using REFGUID = const GUID&;
	using FILETIME = SKSE::WinAPI::FILETIME;
	using RECT = SKSE::WinAPI::RECT;
	using POINT = SKSE::WinAPI::POINT;

	using IID = GUID;
	using REFIID = const IID&;
	using LPIID = IID*;
	using D3DCOLOR = std::uint32_t;

	using HRESULT = SKSE::WinAPI::HRESULT;
	using HWND = SKSE::WinAPI::HWND;
	using HINSTANCE = SKSE::WinAPI::HINSTANCE;

	enum DIKey : uint32_t
	{
		DIK_ESCAPE = 0x1,
		DIK_1 = 0x2,
		DIK_2 = 0x3,
		DIK_3 = 0x4,
		DIK_4 = 0x5,
		DIK_5 = 0x6,
		DIK_6 = 0x7,
		DIK_7 = 0x8,
		DIK_8 = 0x9,
		DIK_9 = 0xA,
		DIK_0 = 0xB,
		DIK_MINUS = 0xC,
		DIK_EQUALS = 0xD,
		DIK_BACK = 0xE,
		DIK_TAB = 0xF,
		DIK_Q = 0x10,
		DIK_W = 0x11,
		DIK_E = 0x12,
		DIK_R = 0x13,
		DIK_T = 0x14,
		DIK_Y = 0x15,
		DIK_U = 0x16,
		DIK_I = 0x17,
		DIK_O = 0x18,
		DIK_P = 0x19,
		DIK_LBRACKET = 0x1A,
		DIK_RBRACKET = 0x1B,
		DIK_RETURN = 0x1C,
		DIK_LCONTROL = 0x1D,
		DIK_A = 0x1E,
		DIK_S = 0x1F,
		DIK_D = 0x20,
		DIK_F = 0x21,
		DIK_G = 0x22,
		DIK_H = 0x23,
		DIK_J = 0x24,
		DIK_K = 0x25,
		DIK_L = 0x26,
		DIK_SEMICOLON = 0x27,
		DIK_APOSTROPHE = 0x28,
		DIK_GRAVE = 0x29,
		DIK_LSHIFT = 0x2A,
		DIK_BACKSLASH = 0x2B,
		DIK_Z = 0x2C,
		DIK_X = 0x2D,
		DIK_C = 0x2E,
		DIK_V = 0x2F,
		DIK_B = 0x30,
		DIK_N = 0x31,
		DIK_M = 0x32,
		DIK_COMMA = 0x33,
		DIK_PERIOD = 0x34,
		DIK_SLASH = 0x35,
		DIK_RSHIFT = 0x36,
		DIK_MULTIPLY = 0x37,
		DIK_LMENU = 0x38,
		DIK_SPACE = 0x39,
		DIK_CAPITAL = 0x3A,
		DIK_F1 = 0x3B,
		DIK_F2 = 0x3C,
		DIK_F3 = 0x3D,
		DIK_F4 = 0x3E,
		DIK_F5 = 0x3F,
		DIK_F6 = 0x40,
		DIK_F7 = 0x41,
		DIK_F8 = 0x42,
		DIK_F9 = 0x43,
		DIK_F10 = 0x44,
		DIK_NUMLOCK = 0x45,
		DIK_SCROLL = 0x46,
		DIK_NUMPAD7 = 0x47,
		DIK_NUMPAD8 = 0x48,
		DIK_NUMPAD9 = 0x49,
		DIK_SUBTRACT = 0x4A,
		DIK_NUMPAD4 = 0x4B,
		DIK_NUMPAD5 = 0x4C,
		DIK_NUMPAD6 = 0x4D,
		DIK_ADD = 0x4E,
		DIK_NUMPAD1 = 0x4F,
		DIK_NUMPAD2 = 0x50,
		DIK_NUMPAD3 = 0x51,
		DIK_NUMPAD0 = 0x52,
		DIK_DECIMAL = 0x53,
		DIK_OEM_102 = 0x56,
		DIK_F11 = 0x57,
		DIK_F12 = 0x58,
		DIK_F13 = 0x64,
		DIK_F14 = 0x65,
		DIK_F15 = 0x66,
		DIK_KANA = 0x70,
		DIK_ABNT_C1 = 0x73,
		DIK_CONVERT = 0x79,
		DIK_NOCONVERT = 0x7B,
		DIK_YEN = 0x7D,
		DIK_ABNT_C2 = 0x7E,
		DIK_NUMPADEQUALS = 0x8D,
		DIK_PREVTRACK = 0x90,
		DIK_AT = 0x91,
		DIK_COLON = 0x92,
		DIK_UNDERLINE = 0x93,
		DIK_KANJI = 0x94,
		DIK_STOP = 0x95,
		DIK_AX = 0x96,
		DIK_UNLABELED = 0x97,
		DIK_NEXTTRACK = 0x99,
		DIK_NUMPADENTER = 0x9C,
		DIK_RCONTROL = 0x9D,
		DIK_MUTE = 0xA0,
		DIK_CALCULATOR = 0xA1,
		DIK_PLAYPAUSE = 0xA2,
		DIK_MEDIASTOP = 0xA4,
		DIK_VOLUMEDOWN = 0xAE,
		DIK_VOLUMEUP = 0xB0,
		DIK_WEBHOME = 0xB2,
		DIK_NUMPADCOMMA = 0xB3,
		DIK_DIVIDE = 0xB5,
		DIK_SYSRQ = 0xB7,
		DIK_RMENU = 0xB8,
		DIK_PAUSE = 0xC5,
		DIK_HOME = 0xC7,
		DIK_UP = 0xC8,
		DIK_PRIOR = 0xC9,
		DIK_LEFT = 0xCB,
		DIK_RIGHT = 0xCD,
		DIK_END = 0xCF,
		DIK_DOWN = 0xD0,
		DIK_NEXT = 0xD1,
		DIK_INSERT = 0xD2,
		DIK_DELETE = 0xD3,
		DIK_LWIN = 0xDB,
		DIK_RWIN = 0xDC,
		DIK_APPS = 0xDD,
		DIK_POWER = 0xDE,
		DIK_SLEEP = 0xDF,
		DIK_WAKE = 0xE3,
		DIK_WEBSEARCH = 0xE5,
		DIK_WEBFAVORITES = 0xE6,
		DIK_WEBREFRESH = 0xE7,
		DIK_WEBSTOP = 0xE8,
		DIK_WEBFORWARD = 0xE9,
		DIK_WEBBACK = 0xEA,
		DIK_MYCOMPUTER = 0xEB,
		DIK_MAIL = 0xEC,
		DIK_MEDIASELECT = 0xED,
		DIK_BACKSPACE = DIK_BACK,
		DIK_NUMPADSTAR = DIK_MULTIPLY,
		DIK_LALT = DIK_LMENU,
		DIK_CAPSLOCK = DIK_CAPITAL,
		DIK_NUMPADMINUS = DIK_SUBTRACT,
		DIK_NUMPADPLUS = DIK_ADD,
		DIK_NUMPADPERIOD = DIK_DECIMAL,
		DIK_NUMPADSLASH = DIK_DIVIDE,
		DIK_RALT = DIK_RMENU,
		DIK_UPARROW = DIK_UP,
		DIK_PGUP = DIK_PRIOR,
		DIK_LEFTARROW = DIK_LEFT,
		DIK_RIGHTARROW = DIK_RIGHT,
		DIK_DOWNARROW = DIK_DOWN,
		DIK_PGDN = DIK_NEXT
	};

	struct DIMOUSESTATE2__
	{
		LONG lX;
		LONG lY;
		LONG lZ;
		BYTE rgbButtons[8];
	};
	static_assert(sizeof(DIMOUSESTATE2__) == 0x14);
	using DIMOUSESTATE2 = DIMOUSESTATE2__;
	using LPDIMOUSESTATE2 = DIMOUSESTATE2*;

	struct DIDEVICEOBJECTDATA__
	{
		DWORD    dwOfs;        // 00
		DWORD    dwData;       // 04
		DWORD    dwTimeStamp;  // 08
		DWORD    dwSequence;   // 0C
		UINT_PTR uAppData;     // 10
	};
	static_assert(sizeof(DIDEVICEOBJECTDATA__) == 0x18);
	using DIDEVICEOBJECTDATA = DIDEVICEOBJECTDATA__;
	using LPDIDEVICEOBJECTDATA = DIDEVICEOBJECTDATA*;
	using LPCDIDEVICEOBJECTDATA = const DIDEVICEOBJECTDATA*;

	struct DIDEVICEINSTANCEA__
	{
		DWORD dwSize;
		GUID  guidInstance;
		GUID  guidProduct;
		DWORD dwDevType;
		CHAR  tszInstanceName[WinAPI::MAX_PATH];
		CHAR  tszProductName[WinAPI::MAX_PATH];
		GUID  guidFFDriver;  // DIRECTINPUT_VERSION >= 0x0500
		WORD  wUsagePage;
		WORD  wUsage;
	};
	using DIDEVICEINSTANCEA = DIDEVICEINSTANCEA__;
	using LPDIDEVICEINSTANCEA = DIDEVICEINSTANCEA*;
	using LPCDIDEVICEINSTANCEA = const DIDEVICEINSTANCEA*;

	struct DIDEVICEOBJECTINSTANCEA__
	{
		DWORD dwSize;
		GUID  guidType;
		DWORD dwOfs;
		DWORD dwType;
		DWORD dwFlags;
		CHAR  tszName[WinAPI::MAX_PATH];
		//#if(DIRECTINPUT_VERSION >= 0x0500)
		DWORD dwFFMaxForce;
		DWORD dwFFForceResolution;
		WORD  wCollectionNumber;
		WORD  wDesignatorIndex;
		WORD  wUsagePage;
		WORD  wUsage;
		DWORD dwDimension;
		WORD  wExponent;
		WORD  wReportId;
		//#endif /* DIRECTINPUT_VERSION >= 0x0500 */
	};
	using DIDEVICEOBJECTINSTANCEA = DIDEVICEOBJECTINSTANCEA__;
	using LPDIDEVICEOBJECTINSTANCEA = DIDEVICEOBJECTINSTANCEA*;
	using LPCDIDEVICEOBJECTINSTANCEA = const DIDEVICEOBJECTINSTANCEA*;

	using LPDIENUMDEVICEOBJECTSCALLBACKA = bool(__stdcall*)(LPCDIDEVICEOBJECTINSTANCEA, LPVOID);

	struct DIPROPHEADER__
	{
		DWORD dwSize;
		DWORD dwHeaderSize;
		DWORD dwObj;
		DWORD dwHow;
	};

	using DIPROPHEADER = DIPROPHEADER__;
	using LPDIPROPHEADER = DIPROPHEADER*;
	using LPCDIPROPHEADER = const DIPROPHEADER*;

	struct DIDEVCAPS__
	{
		DWORD dwSize;
		DWORD dwFlags;
		DWORD dwDevType;
		DWORD dwAxes;
		DWORD dwButtons;
		DWORD dwPOVs;
		DWORD dwFFSamplePeriod;  // -- fields here are Dinput >= 0x0500
		DWORD dwFFMinTimeResolution;
		DWORD dwFirmwareRevision;
		DWORD dwHardwareRevision;
		DWORD dwFFDriverVersion;
	};
	static_assert(sizeof(DIDEVCAPS__) == 0x2C);
	using DIDEVCAPS = DIDEVCAPS__;
	using LPDIDEVCAPS = DIDEVCAPS*;
	using LPCDIDEVCAPS = const DIDEVCAPS*;
	struct _DIDEVICEIMAGEINFOA
	{
		CHAR  tszImagePath[WinAPI::MAX_PATH];
		DWORD dwFlags;
		DWORD dwViewID;
		RECT  rcOverlay;
		DWORD dwObjID;
		DWORD dwcValidPts;
		POINT rgptCalloutLine[5];
		RECT  rcCalloutRect;
		DWORD dwTextAlign;
	};
	using DIDEVICEIMAGEINFOA = _DIDEVICEIMAGEINFOA;
	using LPDIDEVICEIMAGEINFOA = DIDEVICEIMAGEINFOA*;
	using LPCDIDEVICEIMAGEINFOA = const DIDEVICEIMAGEINFOA*;

	struct _DIOBJECTDATAFORMAT
	{
		const GUID* pguid;
		DWORD       dwOfs;
		DWORD       dwType;
		DWORD       dwFlags;
	};
	using DIOBJECTDATAFORMAT = _DIOBJECTDATAFORMAT;
	using LPDIOBJECTDATAFORMAT = DIOBJECTDATAFORMAT*;
	using LPCDIOBJECTDATAFORMAT = const DIOBJECTDATAFORMAT*;

	struct _DIDATAFORMAT
	{
		DWORD                dwSize;
		DWORD                dwObjSize;
		DWORD                dwFlags;
		DWORD                dwDataSize;
		DWORD                dwNumObjs;
		LPDIOBJECTDATAFORMAT rgodf;
	};
	using DIDATAFORMAT = _DIDATAFORMAT;
	using LPDIDATAFORMAT = DIDATAFORMAT*;
	using LPCDIDATAFORMAT = const DIDATAFORMAT*;

	struct DIENVELOPE__
	{
		DWORD dwSize; /* sizeof(DIENVELOPE)   */
		DWORD dwAttackLevel;
		DWORD dwAttackTime; /* Microseconds         */
		DWORD dwFadeLevel;
		DWORD dwFadeTime; /* Microseconds         */
	};
	using DIENVELOPE = DIENVELOPE__;
	using LPDIENVELOPE = DIENVELOPE*;
	using LPCDIENVELOPE = const DIENVELOPE*;

	struct DIEFFECTINFOA__
	{
		DWORD dwSize;
		GUID  guid;
		DWORD dwEffType;
		DWORD dwStaticParams;
		DWORD dwDynamicParams;
		CHAR  tszName[WinAPI::MAX_PATH];
	};
	using DIEFFECTINFOA = DIEFFECTINFOA__;
	using LPDIEFFECTINFOA = DIEFFECTINFOA*;
	using LPCDIEFFECTINFOA = const DIEFFECTINFOA*;

	using LPDIENUMEFFECTSCALLBACKA = bool(__stdcall*)(LPCDIEFFECTINFOA, LPVOID);

	struct DIEFFECT__
	{
		DWORD        dwSize;         /* sizeof(DIEFFECT)     */
		DWORD        dwFlags;        /* DIEFF_*              */
		DWORD        dwDuration;     /* Microseconds         */
		DWORD        dwSamplePeriod; /* Microseconds         */
		DWORD        dwGain;
		DWORD        dwTriggerButton;                          /* or DIEB_NOTRIGGER    */
		DWORD        dwTriggerRepeatInterval;                  /* Microseconds         */
		DWORD        cAxes;                                    /* Number of axes       */
		LPDWORD      rgdwAxes;                                 /* Array of axes        */
		LPLONG       rglDirection;                             /* Array of directions  */
		LPDIENVELOPE lpEnvelope;                               /* Optional             */
		DWORD        cbTypeSpecificParams;                     /* Size of params       */
		LPVOID       lpvTypeSpecificParams;                    /* Pointer to params    */
		DWORD        dwStartDelay; /* Microseconds         */  // -- fields here are Dinput >= 0x0600
	};
	using DIEFFECT = DIEFFECT__;
	using LPDIEFFECT = DIEFFECT*;
	using LPCDIEFFECT = const DIEFFECT*;

	struct DIEFFESCAPE__
	{
		DWORD  dwSize;
		DWORD  dwCommand;
		LPVOID lpvInBuffer;
		DWORD  cbInBuffer;
		LPVOID lpvOutBuffer;
		DWORD  cbOutBuffer;
	};
	using DIEFFESCAPE = DIEFFESCAPE__;
	using LPDIEFFESCAPE = DIEFFESCAPE*;
	using LPCDIEFFESCAPE = const DIEFFESCAPE*;
	struct DIFILEEFFECT__
	{
		DWORD       dwSize;
		GUID        GuidEffect;
		LPCDIEFFECT lpDiEffect;
		CHAR        szFriendlyName[WinAPI::MAX_PATH];
	};
	using DIFILEEFFECT = DIFILEEFFECT__;
	using LPDIFILEEFFECT = DIFILEEFFECT*;
	using LPCDIFILEEFFECT = const DIFILEEFFECT*;
	struct _DIACTIONA
	{
		UINT_PTR uAppData;
		DWORD    dwSemantic;
		DWORD    dwFlags;
		union
		{
			LPCSTR lptszActionName;
			UINT   uResIdString;
		};
		GUID  guidInstance;
		DWORD dwObjID;
		DWORD dwHow;
	};
	using DIACTIONA = _DIACTIONA;
	using LPDIACTIONA = DIACTIONA*;

	struct _DIACTIONFORMATA
	{
		DWORD       dwSize;
		DWORD       dwActionSize;
		DWORD       dwDataSize;
		DWORD       dwNumActions;
		LPDIACTIONA rgoAction;
		GUID        guidActionMap;
		DWORD       dwGenre;
		DWORD       dwBufferSize;
		LONG        lAxisMin;
		LONG        lAxisMax;
		HINSTANCE   hInstString;
		FILETIME    ftTimeStamp;
		DWORD       dwCRC;
		CHAR        tszActionMap[WinAPI::MAX_PATH];
	};
	using DIACTIONFORMATA = _DIACTIONFORMATA;
	using LPDIACTIONFORMATA = DIACTIONFORMATA*;
	using LPCDIACTIONFORMATA = const DIACTIONFORMATA*;
	struct _DIDEVICEIMAGEINFOHEADERA
	{
		DWORD                dwSize;
		DWORD                dwSizeImageInfo;
		DWORD                dwcViews;
		DWORD                dwcButtons;
		DWORD                dwcAxes;
		DWORD                dwcPOVs;
		DWORD                dwBufferSize;
		DWORD                dwBufferUsed;
		LPDIDEVICEIMAGEINFOA lprgImageInfoArray;
	};
	using DIDEVICEIMAGEINFOHEADERA = _DIDEVICEIMAGEINFOHEADERA;
	using LPDIDEVICEIMAGEINFOHEADERA = DIDEVICEIMAGEINFOHEADERA*;
	using LPCDIDEVICEIMAGEINFOHEADERA = const DIDEVICEIMAGEINFOHEADERA*;

	struct _DICOLORSET
	{
		DWORD    dwSize;
		D3DCOLOR cTextFore;
		D3DCOLOR cTextHighlight;
		D3DCOLOR cCalloutLine;
		D3DCOLOR cCalloutHighlight;
		D3DCOLOR cBorder;
		D3DCOLOR cControlFill;
		D3DCOLOR cHighlightFill;
		D3DCOLOR cAreaFill;
	};
	using DICOLORSET = _DICOLORSET;

	struct __declspec(uuid("00000000-0000-0000-C000-000000000046")) __declspec(novtable)
		IUnknown
	{
		virtual HRESULT       QueryInterface(const GUID&, void**) noexcept = 0;
		virtual std::uint32_t AddRef() noexcept = 0;
		virtual std::uint32_t Release() noexcept = 0;
	};
	using LPUNKNOWN = IUnknown*;

	struct _DICONFIGUREDEVICESPARAMSA
	{
		DWORD             dwSize;
		DWORD             dwcUsers;
		LPSTR             lptszUserNames;
		DWORD             dwcFormats;
		LPDIACTIONFORMATA lprgFormats;
		HWND              hwnd;
		DICOLORSET        dics;
		IUnknown*         lpUnkDDSTarget;
	};
	using DICONFIGUREDEVICESPARAMSA = _DICONFIGUREDEVICESPARAMSA;

	struct __declspec(novtable) IDirectInputEffect : public IUnknown
	{
		virtual HRESULT Initialize(HINSTANCE, DWORD, REFGUID) noexcept = 0;
		virtual HRESULT GetEffectGuid(LPGUID) noexcept = 0;
		virtual HRESULT GetParameters(LPDIEFFECT, DWORD) noexcept = 0;
		virtual HRESULT SetParameters(LPCDIEFFECT, DWORD) noexcept = 0;
		virtual HRESULT Start(std::uint32_t, std::uint32_t) noexcept = 0;
		virtual HRESULT Stop() noexcept = 0;
		virtual HRESULT GetEffectStatus(std::uint32_t*) noexcept = 0;
		virtual HRESULT Download() noexcept = 0;
		virtual HRESULT Unload() noexcept = 0;
		virtual HRESULT Escape(LPDIEFFESCAPE) noexcept = 0;
	};
	using LPDIRECTINPUTEFFECT = IDirectInputEffect*;
	using LPCDIRECTINPUTEFFECT = const IDirectInputEffect*;

	using LPDIENUMCREATEDEFFECTOBJECTSCALLBACK = bool(__stdcall*)(LPDIRECTINPUTEFFECT, void*);
	using LPDICONFIGUREDEVICESCALLBACK = bool(__stdcall*)(IUnknown*, void*);
	using LPDIENUMDEVICESCALLBACKA = bool(__stdcall*)(const DIDEVICEINSTANCEA*, void*);

	using LPDIENUMEFFECTSCALLBACKA = bool(__stdcall*)(const DIEFFECTINFOA*, void*);

	using LPDIENUMEFFECTSINFILECALLBACK = bool(__stdcall*)(const DIFILEEFFECT*, void*);

	struct __declspec(novtable) IDirectInputDevice8A : public IUnknown
	{
		virtual HRESULT GetCapabilities(DIDEVCAPS*) noexcept = 0;
		virtual HRESULT EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetProperty(std::uint32_t, DIPROPHEADER*) noexcept = 0;
		virtual HRESULT SetProperty(std::uint32_t, const DIPROPHEADER*) noexcept = 0;
		virtual HRESULT Acquire() noexcept = 0;
		virtual HRESULT Unacquire() noexcept = 0;
		virtual HRESULT GetDeviceState(std::uint32_t, void*) noexcept = 0;
		virtual HRESULT GetDeviceData(std::uint32_t, DIDEVICEOBJECTDATA*, std::uint32_t*, std::uint32_t) noexcept = 0;
		virtual HRESULT SetDataFormat(const DIDATAFORMAT*) noexcept = 0;
		virtual HRESULT SetEventNotification(HANDLE) noexcept = 0;
		virtual HRESULT SetCooperativeLevel(HWND, std::uint32_t) noexcept = 0;
		virtual HRESULT GetObjectInfo(DIDEVICEOBJECTINSTANCEA*, std::uint32_t, std::uint32_t) noexcept = 0;
		virtual HRESULT GetDeviceInfo(DIDEVICEINSTANCEA*) noexcept = 0;
		virtual HRESULT RunControlPanel(HWND, std::uint32_t) noexcept = 0;
		virtual HRESULT Initialize(HINSTANCE, std::uint32_t, const GUID&) noexcept = 0;
		virtual HRESULT CreateEffect(const GUID&, const DIEFFECT*, IDirectInputEffect*, IUnknown*) noexcept = 0;
		virtual HRESULT EnumEffects(LPDIENUMEFFECTSCALLBACKA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetEffectInfo(DIEFFECTINFOA*, const GUID&) noexcept = 0;
		virtual HRESULT GetForceFeedbackState(std::uint32_t*) noexcept = 0;
		virtual HRESULT SendForceFeedbackCommand(std::uint32_t) noexcept = 0;
		virtual HRESULT EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT Escape(DIEFFESCAPE*) noexcept = 0;
		virtual HRESULT Poll() noexcept = 0;
		virtual HRESULT SendDeviceData(std::uint32_t, const DIDEVICEOBJECTDATA*, std::uint32_t*, std::uint32_t) noexcept = 0;
		virtual HRESULT EnumEffectsInFile(const char*, LPDIENUMEFFECTSINFILECALLBACK, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT WriteEffectToFile(const char*, std::uint32_t, DIFILEEFFECT*, std::uint32_t) noexcept = 0;
		virtual HRESULT BuildActionMap(DIACTIONFORMATA*, const char*, std::uint32_t) noexcept = 0;
		virtual HRESULT SetActionMap(DIACTIONFORMATA*, const char*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetImageInfo(DIDEVICEIMAGEINFOHEADERA*) noexcept = 0;
	};

	using LPDIENUMDEVICESBYSEMANTICSCBA = bool(__stdcall*)(const DIDEVICEINSTANCEA*, IDirectInputDevice8A*, DWORD, DWORD, LPVOID);

	struct __declspec(novtable) IDirectInput8A : public IUnknown
	{
		virtual HRESULT CreateDevice(const GUID&, IDirectInputDevice8A**, IUnknown*) noexcept = 0;
		virtual HRESULT EnumDevices(std::uint32_t, LPDIENUMDEVICESCALLBACKA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetDeviceStatus(const GUID&) noexcept = 0;
		virtual HRESULT RunControlPanel(HWND, std::uint32_t) noexcept = 0;
		virtual HRESULT Initialize(HINSTANCE, std::uint32_t) noexcept = 0;
		virtual HRESULT FindDevice(const GUID&, const char*, GUID*) noexcept = 0;
		virtual HRESULT EnumDevicesBySemantics(const char*, LPDIACTIONFORMATA, LPDIENUMDEVICESBYSEMANTICSCBA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK, DICONFIGUREDEVICESPARAMSA*, std::uint32_t, void*) noexcept = 0;
	};

}
