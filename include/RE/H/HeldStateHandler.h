#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class HeldStateHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_HeldStateHandler;
		inline static constexpr auto VTABLE = VTABLE_HeldStateHandler;

		~HeldStateHandler() override = default;  // 00

#if defined(EXCLUSIVE_SKYRIM_VR)
		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event);  // 05
		virtual void SetHeldStateActive(bool a_flag);                    // 06
#else
		// Same base-class vtable, so PlayerInputHandler's delta applies here too.
		void UpdateHeldStateActive(const ButtonEvent* a_event)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, const ButtonEvent*)>(REL::VersionShift(0x05, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x05, this, a_event);
		}
		void SetHeldStateActive(bool a_flag)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, bool)>(REL::VersionShift(0x06, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x06, this, a_flag);
		}
#endif

		// members
		bool          heldStateActive{ false };      // 10
		bool          triggerReleaseEvent{ false };  // 11
		std::uint16_t pad12{ 0 };                    // 12
		std::uint32_t pad14{ 0 };                    // 14
	};
	STATIC_ASSERT_SIZE(HeldStateHandler, 0x18, 0x18, 0x30, 0x18);
}
