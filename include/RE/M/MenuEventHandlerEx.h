#pragma once

#include "RE/B/ButtonEvent.h"
#include "RE/I/InputEvent.h"
#include "RE/K/KinectEvent.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/M/MouseMoveEvent.h"
#include "RE/T/ThumbstickEvent.h"
#include "RE/V/VrWandTouchpadPositionEvent.h"
#include "RE/V/VrWandTouchpadSwipeEvent.h"
#include "REL/Relocation.h"

#ifdef ENABLE_SKYRIM_AE
#	include "RE/M/MotionGestureEvent.h"
#	include "RE/S/SixaxisEvent.h"
#endif

namespace RE::detail
{
	// Synthesizes a real interface's vtable at runtime rather than relying on a
	// compiler-generated one, since no single compile-time layout is valid across every
	// runtime a build targets here. The Complete Object Locator is copied verbatim from the
	// real interface: safe only because its offset-to-top is 0 on every runtime checked.
	//
	// ShimLayout must be a POD struct byte-identical to the real interface's own object
	// layout up to sizeof(ShimLayout), with the vtable pointer as its first member.
	template <class ShimLayout, std::size_t kMaxSlots>
	class VtableShimBase
	{
	public:
		VtableShimBase(const VtableShimBase&) = delete;
		VtableShimBase(VtableShimBase&&) = delete;
		VtableShimBase& operator=(const VtableShimBase&) = delete;
		VtableShimBase& operator=(VtableShimBase&&) = delete;

	protected:
		VtableShimBase() = default;
		~VtableShimBase() = default;

		// a_patch writes thunk pointers into an a_realSlotCount-sized table starting at
		// slot 0 (not counting the destructor/COL). Built once per concrete adapter type
		// and shared across its instances (function-local static, thread-safe).
		template <class RealInterface>
		static const void* const* SharedTable(std::size_t a_realSlotCount, void (*a_patch)(const void**))
		{
			static const void* s_storage[kMaxSlots + 1]{};
			static const bool  s_init = [&] {
                const auto real = REL::Relocation<const void* const*>(RealInterface::VTABLE[0]).get();
                s_storage[0] = real[-1];  // real Complete Object Locator (offset-to-top == 0)
                const auto n = (std::min<std::size_t>)(a_realSlotCount, kMaxSlots);
                for (std::size_t i = 0; i < n; ++i) {
                    s_storage[i + 1] = real[i];
                }
                if (a_patch) {
                    a_patch(&s_storage[1]);
                }
                return true;
			}();
			(void)s_init;
			return &s_storage[1];
		}

		ShimLayout _shim{};
	};

	// Byte-identical to the real MenuEventHandler object layout (RE/M/MenuEventHandler.h).
	struct MenuEventHandlerShim
	{
		const void* const* vtbl;        // 0x00
		std::uint32_t      refCount;    // 0x08
		bool               registered;  // 0x0C
		std::uint8_t       unk0D;
		std::uint16_t      pad0E;
	};
	static_assert(sizeof(MenuEventHandlerShim) == 0x10);
	static_assert(offsetof(MenuEventHandlerShim, vtbl) == 0);
}

namespace RE
{
	class MenuEventHandlerEx : public detail::VtableShimBase<detail::MenuEventHandlerShim, 9>
	{
	private:
		using Base = detail::VtableShimBase<detail::MenuEventHandlerShim, 9>;

	public:
		MenuEventHandlerEx()
		{
			_shim.refCount = 1;  // MenuControls::handlers holds raw, plugin-owned pointers;
								 // the engine never IncRef/DecRefs a registered handler.
			_shim.registered = false;
			_shim.vtbl = BuildTable();
		}

		virtual ~MenuEventHandlerEx() = default;

		// Plugin overrides these; defaults match the real engine's own default bodies.
		virtual bool CanProcess(InputEvent* a_event) = 0;
		virtual bool ProcessButton([[maybe_unused]] ButtonEvent* a_event) { return false; }
		virtual bool ProcessMouseMove([[maybe_unused]] MouseMoveEvent* a_event) { return false; }
		virtual bool ProcessThumbstick([[maybe_unused]] ThumbstickEvent* a_event) { return false; }
		virtual bool ProcessKinect([[maybe_unused]] KinectEvent* a_event) { return false; }
#ifdef ENABLE_SKYRIM_AE
		virtual bool ProcessMotionGesture([[maybe_unused]] MotionGestureEvent* a_event)
		{
			return false;
		}
		virtual bool ProcessSixaxis([[maybe_unused]] SixaxisEvent* a_event) { return false; }
#endif
		virtual bool ProcessVrWandTouchpadSwipe([[maybe_unused]] VrWandTouchpadSwipeEvent* a_event)
		{
			return false;
		}
		virtual bool ProcessVrWandTouchpadPosition([[maybe_unused]] VrWandTouchpadPositionEvent* a_event) { return false; }

		// Pass this, not `this`, to MenuControls::RegisterHandler/RemoveHandler.
		[[nodiscard]] MenuEventHandler* Handler() noexcept
		{
			return reinterpret_cast<MenuEventHandler*>(&_shim);
		}

	private:
		static MenuEventHandlerEx* Owner(void* a_self) noexcept
		{
			return reinterpret_cast<MenuEventHandlerEx*>(
				reinterpret_cast<std::byte*>(a_self) - offsetof(MenuEventHandlerEx, _shim));
		}

		static bool T_CanProcess(detail::MenuEventHandlerShim* a_self, InputEvent* a_event) { return Owner(a_self)->CanProcess(a_event); }
		static bool T_ProcessButton(detail::MenuEventHandlerShim* a_self, ButtonEvent* a_event) { return Owner(a_self)->ProcessButton(a_event); }
		static bool T_ProcessMouseMove(detail::MenuEventHandlerShim* a_self, MouseMoveEvent* a_event) { return Owner(a_self)->ProcessMouseMove(a_event); }
		static bool T_ProcessThumbstick(detail::MenuEventHandlerShim* a_self, ThumbstickEvent* a_event) { return Owner(a_self)->ProcessThumbstick(a_event); }
		static bool T_ProcessKinect(detail::MenuEventHandlerShim* a_self, KinectEvent* a_event) { return Owner(a_self)->ProcessKinect(a_event); }
#ifdef ENABLE_SKYRIM_AE
		static bool T_ProcessMotionGesture(detail::MenuEventHandlerShim* a_self, MotionGestureEvent* a_event)
		{
			return Owner(a_self)->ProcessMotionGesture(a_event);
		}
		static bool T_ProcessSixaxis(detail::MenuEventHandlerShim* a_self, SixaxisEvent* a_event) { return Owner(a_self)->ProcessSixaxis(a_event); }
#endif
		static bool T_ProcessVrWandTouchpadSwipe(detail::MenuEventHandlerShim* a_self, VrWandTouchpadSwipeEvent* a_event)
		{
			return Owner(a_self)->ProcessVrWandTouchpadSwipe(a_event);
		}
		static bool T_ProcessVrWandTouchpadPosition(detail::MenuEventHandlerShim* a_self, VrWandTouchpadPositionEvent* a_event) { return Owner(a_self)->ProcessVrWandTouchpadPosition(a_event); }

		// Real per-runtime slot layout, matching RE/M/MenuEventHandler.h's own numbering
		// exactly (a_table[k] is real vtable slot k -- slot 0 is the destructor, left as
		// the copied real default; slot 1 is always CanProcess, pure in the real class).
		static void Patch(const void** a_table)
		{
			a_table[1] = reinterpret_cast<const void*>(&T_CanProcess);
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				a_table[2] = reinterpret_cast<const void*>(&T_ProcessVrWandTouchpadSwipe);
				a_table[3] = reinterpret_cast<const void*>(&T_ProcessVrWandTouchpadPosition);
				// slot 4 (Unk_04) intentionally left as the real default -- not routed by
				// MenuControls, not exposed as an override point.
				a_table[5] = reinterpret_cast<const void*>(&T_ProcessKinect);
				a_table[6] = reinterpret_cast<const void*>(&T_ProcessThumbstick);
				a_table[7] = reinterpret_cast<const void*>(&T_ProcessMouseMove);
				a_table[8] = reinterpret_cast<const void*>(&T_ProcessButton);
			}
#ifdef ENABLE_SKYRIM_AE
			else if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				a_table[2] = reinterpret_cast<const void*>(&T_ProcessMotionGesture);
				a_table[3] = reinterpret_cast<const void*>(&T_ProcessSixaxis);
				a_table[4] = reinterpret_cast<const void*>(&T_ProcessKinect);
				a_table[5] = reinterpret_cast<const void*>(&T_ProcessThumbstick);
				a_table[6] = reinterpret_cast<const void*>(&T_ProcessMouseMove);
				a_table[7] = reinterpret_cast<const void*>(&T_ProcessButton);
			}
#endif
			else {
				a_table[2] = reinterpret_cast<const void*>(&T_ProcessKinect);
				a_table[3] = reinterpret_cast<const void*>(&T_ProcessThumbstick);
				a_table[4] = reinterpret_cast<const void*>(&T_ProcessMouseMove);
				a_table[5] = reinterpret_cast<const void*>(&T_ProcessButton);
			}
		}

		static const void* const* BuildTable()
		{
			std::size_t n;
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				n = 9;
			}
#ifdef ENABLE_SKYRIM_AE
			else if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				n = 8;
			}
#endif
			else {
				n = 6;
			}
			return Base::template SharedTable<MenuEventHandler>(n, &Patch);
		}
	};
}
