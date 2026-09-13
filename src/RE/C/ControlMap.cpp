#include "RE/C/ControlMap.h"

namespace RE
{
	ControlMap* ControlMap::GetSingleton()
	{
		static REL::Relocation<ControlMap**> singleton{ RELOCATION_ID(514705, 400863) };
		return *singleton;
	}

	void ControlMap::AllowTextInput(bool a_allow)
	{
		using func_t = decltype(&ControlMap::AllowTextInput);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67252, 68552) };
		return func(this, a_allow);
	}

	bool ControlMap::GetButtonNameFromUserEvent(const BSFixedString& a_eventID, INPUT_DEVICE a_device, BSFixedString& a_buttonName)
	{
		using func_t = decltype(&ControlMap::GetButtonNameFromUserEvent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67253, 68553) };
		return func(this, a_eventID, a_device, a_buttonName);
	}

	std::uint32_t ControlMap::GetMappedKey(std::string_view a_eventID, INPUT_DEVICE a_device, InputContextID a_context) const
	{
		assert(a_device < INPUT_DEVICE::kTotal);
		assert(a_context < InputContextID::kTotal);

		if (controlMap[a_context]) {
			const auto&   mappings = controlMap[a_context]->deviceMappings[a_device];
			BSFixedString eventID(a_eventID);
			for (auto& mapping : mappings) {
				if (mapping.eventID == eventID) {
					return mapping.inputKey;
				}
			}
		}

		return kInvalid;
	}

	bool ControlMap::GetMappingFromEventName(const BSFixedString& a_eventID, UserEvents::INPUT_CONTEXT_ID a_context, INPUT_DEVICE a_device, UserEventMapping& a_mapping)
	{
		const auto context = controlMap[a_context];
		if (context) {
			for (auto& mapping : context->deviceMappings[a_device]) {
				if (mapping.eventID == a_eventID) {
					a_mapping = mapping;
					return true;
				}
			}
		}

		return false;
	}

	std::string_view ControlMap::GetUserEventName(std::uint32_t a_buttonID, INPUT_DEVICE a_device, InputContextID a_context) const
	{
		assert(a_device < INPUT_DEVICE::kTotal);
		assert(a_context < InputContextID::kTotal);

		if (controlMap[a_context]) {
			const auto&      mappings = controlMap[a_context]->deviceMappings[a_device];
			UserEventMapping tmp{};
			tmp.inputKey = static_cast<std::uint16_t>(a_buttonID);
			auto range = std::equal_range(
				mappings.begin(),
				mappings.end(),
				tmp,
				[](auto&& a_lhs, auto&& a_rhs) {
					return a_lhs.inputKey < a_rhs.inputKey;
				});

			if (std::distance(range.first, range.second) == 1) {
				return range.first->eventID;
			}
		}

		return ""sv;
	}

	void ControlMap::PopInputContext(InputContextID a_context)
	{
		using func_t = decltype(&ControlMap::PopInputContext);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67244, 68544) };
		return func(this, a_context);
	}

	void ControlMap::PushInputContext(InputContextID a_context)
	{
		using func_t = decltype(&ControlMap::PushInputContext);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67243, 68543) };
		return func(this, a_context);
	}

	void ControlMap::StoreControls()
	{
		using func_t = decltype(&ControlMap::StoreControls);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67246, 68546) };
		return func(this);
	}

	void ControlMap::LoadStoredControls()
	{
		using func_t = decltype(&ControlMap::LoadStoredControls);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67247, 68547) };
		return func(this);
	}

	void ControlMap::ToggleControls(UEFlag a_flags, bool a_enable, bool a_storeState)
	{
		using func_t = decltype(&ControlMap::ToggleControls);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67245, 68545) };
		return func(this, a_flags, a_enable, a_storeState);
	}

	void ControlMap::GetControlsState(std::uint32_t& a_enabledControls, std::uint32_t& a_storedControls) const
	{
		using func_t = decltype(&ControlMap::GetControlsState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67248, 68548) };
		return func(this, a_enabledControls, a_storedControls);
	}

	void ControlMap::SetControlsState(std::uint32_t a_enabledControls, std::uint32_t a_storedControls)
	{
		using func_t = decltype(&ControlMap::SetControlsState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67249, 68549) };
		return func(this, a_enabledControls, a_storedControls);
	}

	void ControlMap::ResetControls()
	{
		using func_t = decltype(&ControlMap::ResetControls);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67250, 68550) };
		return func(this);
	}

	void ControlMap::SetGamePadType(PC_GAMEPAD_TYPE a_gamePadType)
	{
		using func_t = decltype(&ControlMap::SetGamePadType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67237, 68537) };
		return func(this, a_gamePadType);
	}
}
