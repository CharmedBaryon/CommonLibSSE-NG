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
		void Initialize() override;             // 01
		void Poll(float a_timeDelta) override;  // 02
		void Shutdown() override;               // 03
		void ClearInputState() override;        // 08 - { std::memset(&curState, 0, 0x200); }
		void Unk_09(void) override;             // 09 - { return; }
		void Unk_0A(void) override;             // 0A - { return; }

		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;
		[[nodiscard]] Key  RemapNumpadKey(REX::W32::DIK a_key);

		// VR note: own members start at 0x70 (SE) / 0x78 (VR) due to BSIInputDevice unk08.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                 \
	REX::W32::IDirectInput8A*    dInputDevice;     /* 070 */ \
	REX::W32::DIDEVICEOBJECTDATA diObjData[10];    /* 078 */ \
	std::uint8_t                 prevState[0x100]; /* 168 */ \
	std::uint8_t                 curState[0x100];  /* 268 */ \
	bool                         capsLockOn;       /* 368 */
            RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x70, 0x78);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif

	protected:
		BSWin32KeyboardDevice();
	};
#ifndef SKYRIM_CROSS_VR
	STATIC_ASSERT_OFFSET(BSWin32KeyboardDevice, prevState, 0x168, 0x170);
	STATIC_ASSERT_OFFSET(BSWin32KeyboardDevice, curState, 0x268, 0x270);
#endif
	STATIC_ASSERT_SIZE(BSWin32KeyboardDevice, 0x370, 0x370, 0x378, 0x8);
}
#undef RUNTIME_DATA_CONTENT
