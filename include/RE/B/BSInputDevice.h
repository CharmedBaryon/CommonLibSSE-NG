#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIInputDevice.h"
#include "RE/B/BSTHashMap.h"
#include "RE/I/InputDevices.h"

namespace RE
{
	class BSInputDevice : public BSIInputDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSInputDevice;
		inline static constexpr auto VTABLE = VTABLE_BSInputDevice;

		struct InputButton
		{
			BSFixedString name;          // 00
			float         heldDownSecs;  // 08
			std::uint32_t keycode;       // 0C
		};
		static_assert(sizeof(InputButton) == 0x10);

		~BSInputDevice() override;  // 00

		// override (BSIInputDevice)
		bool               GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;      // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                            // 05
		bool               GetMappedKeycode(std::uint32_t a_key, std::uint32_t& outKeyCode) override;  // 06
		[[nodiscard]] bool IsEnabled() const override;                                                 // 07 - { return true; }

		[[nodiscard]] bool IsKeyboard() const;
		[[nodiscard]] bool IsMouse() const;
		[[nodiscard]] bool IsGamepad() const;
		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;

		bool LoadControlsDefinitionFile(const char* a_fileName);                                                                    // loads the controls definition file from <FILENAME>.txt (usually located in 'interface\controls' folder)
		void ResetButtonMaps();                                                                                                     // resets the button maps
		void SetButtonState(std::uint32_t a_buttonId, float a_timeSinceLastPoll, bool a_buttonWasPressed, bool a_buttonIsPressed);  // sets the button state for a given key code and emits a button event if necessary

		// members
		INPUT_DEVICE                             device;           // 08
		std::uint32_t                            pad0C;            // 0C
		BSTHashMap<std::uint32_t, InputButton*>  deviceButtons;    // 10
		BSTHashMap<BSFixedString, std::uint32_t> buttonNameIDMap;  // 40
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSInputDevice) == 0x70);
}
