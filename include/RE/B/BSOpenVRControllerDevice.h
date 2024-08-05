#pragma once

#ifdef ENABLE_SKYRIM_VR

#include "RE/B/BSTrackedControllerDevice.h"

namespace RE
{
	class BSOpenVRControllerDevice : public BSTrackedControllerDevice
	{
	public:
#if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_BSOpenVRControllerDevice;
#endif

		~BSOpenVRControllerDevice() override;

		struct Keys
		{
			enum Key : std::uint32_t  // Only tested with Oculus, keys are same for both controllers
			{
				kBY = 1,    // Y/B button on left/right hand respectively
				kGrip = 2,  // Grip button
				kXA = 7,    // X/A button on left/right hand respectively
				// kJoystick = 11, // Joystick moving event
				kJoystickTrigger = 32,  // Joystick press
				kTrigger = 33           // Trigger button
			};
		};
		using Key = Keys::Key;

		// override BSIInputDevice
		void               Initialize() override;                                                      // 01
		void               Process(float a_arg1) override;                                             // 02
		void               Release() override;                                                         // 03 - { return; }
		bool               GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;      // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                            // 05
		bool               GetMappedKeycode(std::uint32_t a_key, std::uint32_t& outKeyCode) override;  // 06
		[[nodiscard]] bool IsEnabled() const override;                                                 // 07 - { return true; }
		void               Reset() override;                                                           // 08

	private:
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint64_t unk80[0x16];  // 080
		std::uint32_t unk130;       // 130
		std::uint32_t unk134;       // 134
		std::uint32_t unk138;       // 138
		std::uint32_t unk13C;       // 13C
		std::uint32_t unk140;       // 140
		std::uint32_t unk144;       // 144
		std::uint32_t unk148;       // 148
		std::uint32_t unk14C;       // 14C
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSOpenVRControllerDevice) == 0x150);
#endif
}
#endif
