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
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event);  // 07
		virtual void SetHeldStateActive(bool a_flag);                    // 08
#else
		// Same base-class vtable, so PlayerInputHandler's delta applies here too.
		void UpdateHeldStateActive(const ButtonEvent* a_event)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, const ButtonEvent*)>(REL::VersionShift(0x05, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x07, this, a_event);
		}
		void SetHeldStateActive(bool a_flag)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, bool)>(REL::VersionShift(0x06, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x08, this, a_flag);
		}
#endif

		// members
		bool          heldStateActive{ false };      // 10
		bool          triggerReleaseEvent{ false };  // 11
		std::uint16_t pad12{ 0 };                    // 12
		std::uint32_t pad14{ 0 };                    // 14
#ifdef EXCLUSIVE_SKYRIM_VR
		std::uint8_t unkVr18[0x48];  // 18 - VR only, not touched by handler code
#endif
	};
	STATIC_ASSERT_SIZE(HeldStateHandler, 0x18, 0x18, 0x60, 0x18);
}
