#pragma once

#include "RE/B/BSIInputDevice.h"
#include "RE/B/BSInputDevice.h"

namespace RE
{
	class BSTrackedControllerDevice : public BSInputDevice
	{
	public:
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		inline static constexpr auto RTTI = RTTI_BSTrackedControllerDevice;
#endif

		~BSTrackedControllerDevice() override;

		// override BSIInputDevice
		bool               GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                        // 05
		void               Unk_06(void) override;                                                  // 06
		[[nodiscard]] bool IsEnabled() const override;                                             // 07
	};
	static_assert(sizeof(BSTrackedControllerDevice) == 0x70);
}
