#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/B/BSIInputDevice.h"
#	include "RE/B/BSInputDevice.h"
#	include "openvr.h"
namespace RE
{
	enum class ControllerDeviceHand  // Not sure on this one, enum needs more RE
	{
		kLeft = 0,
		kRight = 1,

		kNeither = 3
	};
	class BSTrackedControllerDevice : public BSInputDevice
	{
	public:
#	if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_BSTrackedControllerDevice;
#	endif

		~BSTrackedControllerDevice() override;

		// override BSIInputDevice
		bool               GetButtonNameFromID(std::int32_t a_id, BSFixedString& a_buttonName) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                               // 05
		bool               GetKeyCodeFromID(std::int32_t a_id, std::uint32_t& a_keyCode) override;        // 06
		[[nodiscard]] bool IsEnabled() const override;                                                    // 07
	public:
		struct RUNTIME_DATA
		{
#	define RUNTIME_DATA_CONTENT                                   \
		std::uint64_t            unk70;              /* 70 / 78 */ \
		ControllerDeviceHand     hand;               /* 78 / 80 */ \
		vr::TrackedDeviceIndex_t trackedDeviceIndex; /* 7C / 84 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x70, 0x78);
#	ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#	endif
	};
	STATIC_ASSERT_SIZE(BSTrackedControllerDevice, 0x80, 0x80, 0x88, 0x8);
}
#	undef RUNTIME_DATA_CONTENT
#endif
