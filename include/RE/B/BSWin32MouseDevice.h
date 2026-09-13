#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSMouseDevice.h"

#include "REX/W32/DINPUT.h"

namespace RE
{
	class BSWin32MouseDevice : public BSMouseDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32MouseDevice;
		inline static constexpr auto VTABLE = VTABLE_BSWin32MouseDevice;

		struct Keys
		{
			enum Key : std::uint32_t
			{
				kLeftButton,
				kRightButton,
				kMiddleButton,
				kButton3,
				kButton4,
				kButton5,
				kButton6,
				kButton7,
				kWheelUp,
				kWheelDown
			};
		};
		using Key = Keys::Key;

		~BSWin32MouseDevice() override;  // 00

		// override (BSMouseDevice)
		void Initialize() override;             // 01
		void Poll(float a_timeDelta) override;  // 02
		void Shutdown() override;               // 03
		void ClearInputState() override;        // 08
		void Reinitialize(void) override;       // 09

		// VR note: own members start at 0x78 (SE) / 0x80 (VR) due to BSIInputDevice unk08.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                           \
	REX::W32::IDirectInputDevice8A* dInputDevice;      /* 78, 80 VR */ \
	REX::W32::DIMOUSESTATE2         dInputPrevState{}; /* 80, 88 VR */ \
	REX::W32::DIMOUSESTATE2         dInputNextState{}; /* 94, 9C VR */ \
	bool                            notInitialized;    /* A8, B0 VR */ \
	mutable BSSpinLock              reinitializeLock;  /* AC, B4 VR */
            RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x78, 0x80);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif

	protected:
		BSWin32MouseDevice();
	};
	STATIC_ASSERT_SIZE(BSWin32MouseDevice, 0xB8, 0xB8, 0xC0, 0x8);
}
#undef RUNTIME_DATA_CONTENT
