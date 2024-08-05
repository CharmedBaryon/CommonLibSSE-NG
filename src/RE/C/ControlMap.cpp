#include "RE/C/ControlMap.h"

#include "RE/B/BSInputDeviceManager.h"
#include "RE/U/UserEventEnabled.h"

namespace RE
{
	ControlMap* ControlMap::GetSingleton()
	{
		REL::Relocation<ControlMap**> singleton{ RELOCATION_ID(514705, 400863) };
		return *singleton;
	}

	std::int8_t ControlMap::AllowTextInput(bool a_allow)
	{
		if (a_allow) {
			if (GetRuntimeData().textEntryCount != -1) {
				++GetRuntimeData().textEntryCount;
			}
		} else {
			if (GetRuntimeData().textEntryCount != 0) {
				--GetRuntimeData().textEntryCount;
			}
		}

		return GetRuntimeData().textEntryCount;
	}

	bool ControlMap::GetButtonNameFromUserEvent(const BSFixedString& a_eventID, INPUT_DEVICE a_device, BSFixedString& a_buttonName)
	{
		for (const auto& inputContext : controlMap) {
			if (!inputContext) {
				continue;
			}

			for (const auto& mapping : inputContext->deviceMappings[a_device]) {
				if (mapping.eventID == a_eventID) {
					if (mapping.inputKey == 0xFF) {
						break;
					}

					const auto inputDeviceManager = BSInputDeviceManager::GetSingleton();
					inputDeviceManager->GetButtonNameFromID(a_device, mapping.inputKey, a_buttonName);
					return true;
				}
			}
		}

		return false;
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

	void ControlMap::ToggleControls(UEFlag a_flags, bool a_enable)
	{
		auto oldState = GetRuntimeData().enabledControls;

		if (a_enable) {
			GetRuntimeData().enabledControls.set(a_flags);
			if (GetRuntimeData().unk11C != UEFlag::kInvalid) {
				GetRuntimeData().unk11C.set(a_flags);
			}
		} else {
			GetRuntimeData().enabledControls.reset(a_flags);
			if (GetRuntimeData().unk11C != UEFlag::kInvalid) {
				GetRuntimeData().unk11C.reset(a_flags);
			}
		}

		UserEventEnabled event{ GetRuntimeData().enabledControls, oldState };
		SendEvent(std::addressof(event));
	}
}
