#pragma once

#include "RE/B/BSIInputDevice.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSPCGamepadDeviceDelegate;

	class BSPCGamepadDeviceHandler : public BSIInputDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPCGamepadDeviceHandler;
		inline static constexpr auto VTABLE = VTABLE_BSPCGamepadDeviceHandler;
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	BSPCGamepadDeviceDelegate* currentPCGamePadDelegate; /* 08, 10 in VR */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~BSPCGamepadDeviceHandler() override;  // 00

		// override (BSIInputDevice)
		void          Initialize() override;                                                         // 01
		void          Poll(float a_timeDelta) override;                                              // 02
		void          Shutdown() override;                                                           // 03
		bool          GetButtonNameFromID(std::int32_t a_id, BSFixedString& a_buttonName) override;  // 04
		std::uint32_t GetMappingKey(BSFixedString a_mapping) override;                               // 05
		bool          GetKeyCodeFromID(std::int32_t a_id, std::uint32_t& a_keyCode) override;        // 06
		bool          IsEnabled() const override;                                                    // 07 - { return currentPCGamePadDelegate != 0; }
		void          ClearInputState() override;                                                    // 08

		void InitializeDelegate();  // called by Initialize() and Process() to initialize the delegate

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x8, 0x10);
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT
#endif
	protected:
		friend class BSInputDeviceFactory;
		BSPCGamepadDeviceHandler();
	};
	STATIC_ASSERT_SIZE(BSPCGamepadDeviceHandler, 0x10, 0x10, 0x18, 0x8);
}
#undef RUNTIME_DATA_CONTENT
