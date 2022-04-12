#pragma once

#include "RE/B/BSTrackedControllerDevice.h"

namespace RE
{
	class BSOpenVRControllerDevice : public BSTrackedControllerDevice
	{
	public:
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		inline static constexpr auto RTTI = RTTI_BSOpenVRControllerDevice;
#endif

		~BSOpenVRControllerDevice() override;

		// override BSIInputDevice
		void               Initialize() override;                                                  // 01
		void               Process(float a_arg1) override;                                         // 02
		void               Unk_03(void) override;                                                  // 03 - { return; }
		bool               GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                        // 05
		void               Unk_06(void) override;                                                  // 06
		[[nodiscard]] bool IsEnabled() const override;                                             // 07 - { return true; }
		void               Reset() override;                                                       // 08

#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		// add
		virtual void Unk_09(void);  // 09
		virtual void Unk_0A(void);  // 0A
		virtual void Unk_0B(void);  // 0B
		virtual void Unk_0C(void);  // 0C
		virtual void Unk_0D(void);  // 0D
		virtual void Unk_0E(void);  // 0E
		virtual void Unk_0F(void);  // 0F
		virtual void Unk_10(void);  // 10
		virtual void Unk_11(void);  // 11
		virtual void Unk_12(void);  // 12
		virtual void Unk_13(void);  // 13
		virtual void Unk_14(void);  // 14
		virtual void Unk_15(void);  // 15
#endif

	private:
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		uint8_t  unk70[0xBC];  // 78
		uint64_t unk134;       // 134
		uint64_t unk138;       // 13C
		uint32_t unk140;       // 144
		uint32_t unk144;       // 148
		uint32_t unk148{ 4 };  // 14C
#endif
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSOpenVRControllerDevice) == 0x150);
#endif
}
