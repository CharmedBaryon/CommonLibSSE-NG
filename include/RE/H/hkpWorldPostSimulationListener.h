#pragma once

namespace RE
{
	class hkpWorld;

	class hkpWorldPostSimulationListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpWorldPostSimulationListener;
		inline static constexpr auto VTABLE = VTABLE_hkpWorldPostSimulationListener;

		// add
		virtual ~hkpWorldPostSimulationListener() = default;  // 00

		virtual void PostSimulationCallback(hkpWorld* a_world) = 0;  // 01
		virtual void InactiveEntityMovedCallback(hkpWorld*) {}       // 02
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpWorldPostSimulationListener) == 0x8);
}
