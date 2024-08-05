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
		void Initialize() override;           // 01
		void Process(float a_arg1) override;  // 02
		void Release() override;              // 03
		void Reset() override;                // 08
		void Reinitialize(void) override;     // 09

		// members
		REX::W32::IDirectInputDevice8A* dInputDevice;       // 78
		REX::W32::DIMOUSESTATE2         dInputPrevState{};  // 80
		REX::W32::DIMOUSESTATE2         dInputNextState{};  // 94
		bool                            notInitialized;     // A8
		mutable BSSpinLock              reinitializeLock;   // AC

	protected:
		BSWin32MouseDevice();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSWin32MouseDevice) == 0xB8);
}
