#include "RE/B/BSInputDevice.h"

namespace RE
{
	bool BSInputDevice::IsKeyboard() const
	{
		return GetRuntimeData().device == INPUT_DEVICE::kKeyboard;
	}

	bool BSInputDevice::IsMouse() const
	{
		return GetRuntimeData().device == INPUT_DEVICE::kMouse;
	}

	bool BSInputDevice::IsGamepad() const
	{
		return GetRuntimeData().device == INPUT_DEVICE::kGamepad;
	}

	bool BSInputDevice::IsPressed(std::uint32_t a_keyCode) const
	{
		auto& rt = GetRuntimeData();
		auto  it = rt.deviceButtons.find(a_keyCode);
		return (it != rt.deviceButtons.end()) && (it->second->heldDownSecs > 0.0f);
	}

	bool BSInputDevice::LoadControlsDefinitionFile(const char* a_fileName)
	{
		using func_t = decltype(&BSInputDevice::LoadControlsDefinitionFile);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67438, 68745) };
		return func(this, a_fileName);
	}

	void BSInputDevice::ResetButtonMaps()
	{
		auto& rt = GetRuntimeData();
		rt.buttonNameIDMap.clear();
		rt.deviceButtons.clear();
	}

	void BSInputDevice::SetButtonState(std::uint32_t a_buttonId, float a_timeSinceLastPoll, bool a_buttonWasPressed, bool a_buttonIsPressed)
	{
		using func_t = decltype(&BSInputDevice::SetButtonState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67441, 68748) };
		return func(this, a_buttonId, a_timeSinceLastPoll, a_buttonWasPressed, a_buttonIsPressed);
	}
}
