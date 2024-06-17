#pragma once

#include "RE/B/BSKeyboardDevice.h"

#include "REX/W32/DINPUT.h"

namespace RE
{
	class BSWin32KeyboardDevice : public BSKeyboardDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32KeyboardDevice;
		inline static constexpr auto VTABLE = VTABLE_BSWin32KeyboardDevice;

		~BSWin32KeyboardDevice() override;  // 00

		// override (BSKeyboardDevice)
		void Initialize() override;           // 01
		void Process(float a_unk1) override;  // 02
		void Release() override;              // 03
		void Reset() override;                // 08 - { std::memset(&curState, 0, 0x200); }
		void Unk_09(void) override;           // 09 - { return; }
		void Unk_0A(void) override;           // 0A - { return; }

		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;
		[[nodiscard]] Key  RemapNumpadKey(REX::W32::DIK a_key);

		// members
		REX::W32::IDirectInput8A*    dInputDevice;      // 070
		REX::W32::DIDEVICEOBJECTDATA diObjData[10];     // 078
		std::uint8_t                 prevState[0x100];  // 168
		std::uint8_t                 curState[0x100];   // 268
		bool                         capsLockOn;        // 368

	protected:
		BSWin32KeyboardDevice();

	private:
		KEEP_FOR_RE()
	};
	static_assert(offsetof(BSWin32KeyboardDevice, prevState) == 0x168);
	static_assert(offsetof(BSWin32KeyboardDevice, curState) == 0x268);
	static_assert(sizeof(BSWin32KeyboardDevice) == 0x370);
}
