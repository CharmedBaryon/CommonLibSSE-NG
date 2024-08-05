#pragma once

#include "RE/B/BSIInputDevice.h"

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
		void          Initialize() override;                                                      // 01
		void          Process(float a_unk1) override;                                             // 02
		void          Release() override;                                                         // 03
		bool          GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;      // 04
		std::uint32_t GetMappingKey(BSFixedString a_mapping) override;                            // 05
		bool          GetMappedKeycode(std::uint32_t a_key, std::uint32_t& outKeyCode) override;  // 06
		bool          IsEnabled() const override;                                                 // 07 - { return currentPCGamePadDelegate != 0; }
		void          Reset() override;                                                           // 08

		void InitializeDelegate();  // called by Initialize() and Process() to initialize the delegate

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x8, 0x10);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x8, 0x10);
		}
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT
#endif
	protected:
		friend class BSInputDeviceFactory;
		BSPCGamepadDeviceHandler();
	};
#ifndef SKYRIM_CROSS_VR
	static_assert(sizeof(BSPCGamepadDeviceHandler) == 0x10);
#else
	static_assert(sizeof(BSPCGamepadDeviceHandler) == 0x8);
#endif
}
#undef RUNTIME_DATA_CONTENT
