#pragma once

#include "REX/W32/COM.h"
#include "REX/W32/D3D.h"

namespace REX::W32
{
	struct IDirectInput8A;
	struct IDirectInputDevice8A;
	struct IDirectInputEffect;
}

namespace REX::W32
{
	enum DIK : std::uint32_t
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
}

namespace REX::W32
{
	struct DIENVELOPE;
	struct DIOBJECTDATAFORMAT;

	struct DIACTIONA
	{
		std::uintptr_t appData;
		std::uint32_t  semantic;
		std::uint32_t  flags;
		union
		{
			const char*   actionName;
			std::uint32_t resIdString;
		};
		GUID          guidInstance;
		std::uint32_t objID;
		std::uint32_t how;
	};

	struct DIACTIONFORMATA
	{
		std::uint32_t size;
		std::uint32_t actionSize;
		std::uint32_t dataSize;
		std::uint32_t numActions;
		DIACTIONA*    action;
		GUID          guidActionMap;
		std::uint32_t genre;
		std::uint32_t bufferSize;
		std::int32_t  axisMin;
		std::int32_t  axisMax;
		HINSTANCE     instString;
		FILETIME      timeStamp;
		std::uint32_t crc;
		char          actionMap[MAX_PATH];
	};

	struct DICOLORSET
	{
		std::uint32_t size;
		D3DCOLOR      textFore;
		D3DCOLOR      textHighlight;
		D3DCOLOR      calloutLine;
		D3DCOLOR      calloutHighlight;
		D3DCOLOR      border;
		D3DCOLOR      controlFill;
		D3DCOLOR      highlightFill;
		D3DCOLOR      areaFill;
	};

	struct DICONFIGUREDEVICESPARAMSA
	{
		std::uint32_t    size;
		std::uint32_t    users;
		char*            userNames;
		std::uint32_t    formatsSize;
		DIACTIONFORMATA* formats;
		HWND             hwnd;
		DICOLORSET       dics;
		IUnknown*        unkDDSTarget;
	};

	struct DIDATAFORMAT
	{
		std::uint32_t       size;
		std::uint32_t       objSize;
		std::uint32_t       flags;
		std::uint32_t       dataSize;
		std::uint32_t       numObjs;
		DIOBJECTDATAFORMAT* odf;
	};

	struct DIDEVCAPS
	{
		std::uint32_t size;
		std::uint32_t flags;
		std::uint32_t devType;
		std::uint32_t axes;
		std::uint32_t buttons;
		std::uint32_t povs;
		std::uint32_t ffSamplePeriod;
		std::uint32_t ffMinTimeResolution;
		std::uint32_t firmwareRevision;
		std::uint32_t hardwareRevision;
		std::uint32_t ffDriverVersion;
	};

	struct DIDEVICEIMAGEINFOA
	{
		char          imagePath[MAX_PATH];
		std::uint32_t flags;
		std::uint32_t viewID;
		RECT          overlay;
		std::uint32_t objID;
		std::uint32_t validPts;
		POINT         calloutLine[5];
		RECT          calloutRect;
		std::uint32_t textAlign;
	};

	struct DIDEVICEIMAGEINFOHEADERA
	{
		std::uint32_t       size;
		std::uint32_t       sizeImageInfo;
		std::uint32_t       views;
		std::uint32_t       buttons;
		std::uint32_t       axes;
		std::uint32_t       povs;
		std::uint32_t       bufferSize;
		std::uint32_t       bufferUsed;
		DIDEVICEIMAGEINFOA* imageInfoArray;
	};

	struct DIDEVICEINSTANCEA
	{
		std::uint32_t size;
		GUID          guidInstance;
		GUID          guidProduct;
		std::uint32_t devType;
		char          instanceName[MAX_PATH];
		char          productName[MAX_PATH];
		GUID          guidFFDriver;

		// DIRECTINPUT_VERSION >= 0x0500
		std::uint16_t usagePage;
		std::uint16_t usage;
	};

	struct DIDEVICEOBJECTDATA
	{
		std::uint32_t  ofs;
		std::uint32_t  data;
		std::uint32_t  timeStamp;
		std::uint32_t  sequence;
		std::uintptr_t appData;
	};

	struct DIDEVICEOBJECTINSTANCEA
	{
		std::uint32_t size;
		GUID          guidType;
		std::uint32_t ofs;
		std::uint32_t type;
		std::uint32_t flags;
		char          name[MAX_PATH];

		// DIRECTINPUT_VERSION >= 0x0500
		std::uint32_t ffMaxForce;
		std::uint32_t ffForceResolution;
		std::uint16_t collectionNumber;
		std::uint16_t designatorIndex;
		std::uint16_t usagePage;
		std::uint16_t usage;
		std::uint32_t dimension;
		std::uint16_t exponent;
		std::uint16_t reportId;
	};

	struct DIEFFECT
	{
		std::uint32_t  size;
		std::uint32_t  flags;
		std::uint32_t  duration;
		std::uint32_t  samplePeriod;
		std::uint32_t  gain;
		std::uint32_t  triggerButton;
		std::uint32_t  triggerRepeatInterval;
		std::uint32_t  axesSize;
		std::uint32_t* axes;
		std::int32_t*  direction;
		DIENVELOPE*    envelope;
		std::uint32_t  typeSpecificParamsSize;
		void*          typeSpecificParams;
		std::uint32_t  startDelay;
	};

	struct DIENVELOPE
	{
		std::uint32_t size;
		std::uint32_t attackLevel;
		std::uint32_t attackTime;
		std::uint32_t fadeLevel;
		std::uint32_t fadeTime;
	};

	struct DIEFFECTINFOA
	{
		std::uint32_t size;
		GUID          guid;
		std::uint32_t effectType;
		std::uint32_t staticParams;
		std::uint32_t dynamicParams;
		char          name[MAX_PATH];
	};

	struct DIEFFESCAPE
	{
		std::uint32_t size;
		std::uint32_t command;
		void*         inBuffer;
		std::uint32_t inBufferSize;
		void*         outBuffer;
		std::uint32_t outBufferSize;
	};

	struct DIFILEEFFECT
	{
		std::uint32_t   size;
		GUID            guidEffect;
		const DIEFFECT* effect;
		char            friendlyName[MAX_PATH];
	};

	struct DIMOUSESTATE2
	{
		std::int32_t x;
		std::int32_t y;
		std::int32_t z;
		std::uint8_t rgbButtons[8];
	};

	struct DIOBJECTDATAFORMAT
	{
		const GUID*   guid;
		std::uint32_t ofs;
		std::uint32_t type;
		std::uint32_t flags;
	};

	struct DIPROPHEADER
	{
		std::uint32_t size;
		std::uint32_t headerSize;
		std::uint32_t obj;
		std::uint32_t how;
	};
}

namespace REX::W32
{
	using LPDICONFIGUREDEVICESCALLBACK = BOOL(__stdcall*)(IUnknown*, void*);
	using LPDIENUMCREATEDEFFECTOBJECTSCALLBACK = BOOL(__stdcall*)(IDirectInputEffect*, void*);
	using LPDIENUMDEVICESBYSEMANTICSCBA = BOOL(__stdcall*)(const DIDEVICEINSTANCEA*, IDirectInputDevice8A*, std::uint32_t, std::uint32_t, void*);
	using LPDIENUMDEVICESCALLBACKA = BOOL(__stdcall*)(const DIDEVICEINSTANCEA*, void*);
	using LPDIENUMDEVICEOBJECTSCALLBACKA = BOOL(__stdcall*)(const DIDEVICEOBJECTINSTANCEA*, void*);
	using LPDIENUMEFFECTSCALLBACKA = BOOL(__stdcall*)(const DIEFFECTINFOA*, void*);
	using LPDIENUMEFFECTSINFILECALLBACK = BOOL(__stdcall*)(const DIFILEEFFECT*, void*);
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("BF798030-483A-4DA2-AA99-5D64ED369700"))
		IDirectInput8A : public IUnknown
	{
		virtual HRESULT CreateDevice(const GUID&, IDirectInputDevice8A**, IUnknown*) noexcept = 0;
		virtual HRESULT EnumDevices(std::uint32_t, LPDIENUMDEVICESCALLBACKA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetDeviceStatus(const GUID&) noexcept = 0;
		virtual HRESULT RunControlPanel(HWND, std::uint32_t) noexcept = 0;
		virtual HRESULT Initialize(HINSTANCE, std::uint32_t) noexcept = 0;
		virtual HRESULT FindDevice(const GUID&, const char*, GUID*) noexcept = 0;
		virtual HRESULT EnumDevicesBySemantics(const char*, DIACTIONFORMATA*, LPDIENUMDEVICESBYSEMANTICSCBA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK, DICONFIGUREDEVICESPARAMSA*, std::uint32_t, void*) noexcept = 0;
	};

	struct __declspec(novtable, uuid("54D41080-DC15-4833-A41B-748F73A38179"))
		IDirectInputDevice8A : public IUnknown
	{
		virtual HRESULT GetCapabilities(DIDEVCAPS*) noexcept = 0;
		virtual HRESULT EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA, void*, std::uint32_t) noexcept = 0;
		virtual HRESULT GetProperty(const GUID&, DIPROPHEADER*) noexcept = 0;
		virtual HRESULT SetProperty(const GUID&, const DIPROPHEADER*) noexcept = 0;
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

	struct __declspec(novtable, uuid("E7E1F7C0-88D2-11D0-9AD0-00A0C9A06E35"))
		IDirectInputEffect : public IUnknown
	{
		virtual HRESULT Initialize(HINSTANCE, std::uint32_t, const GUID&) noexcept = 0;
		virtual HRESULT GetEffectGuid(GUID*) noexcept = 0;
		virtual HRESULT GetParameters(DIEFFECT*, std::uint32_t) noexcept = 0;
		virtual HRESULT SetParameters(const DIEFFECT*, std::uint32_t) noexcept = 0;
		virtual HRESULT Start(std::uint32_t, std::uint32_t) noexcept = 0;
		virtual HRESULT Stop() noexcept = 0;
		virtual HRESULT GetEffectStatus(std::uint32_t*) noexcept = 0;
		virtual HRESULT Download() noexcept = 0;
		virtual HRESULT Unload() noexcept = 0;
		virtual HRESULT Escape(DIEFFESCAPE*) noexcept = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_IDirectInput8A{ 0xBF798030, 0x483A, 0x4DA2, { 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00 } };
	inline constexpr IID IID_IDirectInputDevice8A{ 0x54D41080, 0xDC15, 0x4833, { 0xA4, 0x1B, 0x74, 0x8F, 0x73, 0xA3, 0x81, 0x79 } };
	inline constexpr IID IID_IDirectInputEffect{ 0xE7E1F7C0, 0x88D2, 0x11D0, { 0x9A, 0xD0, 0x00, 0xA0, 0xC9, 0xA0, 0x6E, 0x35 } };
}
