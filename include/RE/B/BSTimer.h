#pragma once

namespace RE
{
	class BSTimer
	{
	public:
		[[nodiscard]] static BSTimer* GetSingleton() noexcept
		{
			static REL::Relocation<BSTimer*> singleton{ RELOCATION_ID(523657, 410196) };
			return singleton.get();
		}

		static float QGlobalTimeMultiplier()
		{
			static REL::Relocation<float*> value{ RELOCATION_ID(511882, 388442) };
			return *value;
		}

		static float QGlobalTimeMultiplierTarget()
		{
			static REL::Relocation<float*> value{ RELOCATION_ID(511883, 388443) };
			return *value;
		}

		void SetGlobalTimeMultiplier(float a_multiplier, bool a_arg2)
		{
			using func_t = decltype(&BSTimer::SetGlobalTimeMultiplier);
			static REL::Relocation<func_t> func{ RELOCATION_ID(66988, 68245) };
			return func(this, a_multiplier, a_arg2);
		}

		// Per-frame tick: computes delta/realTimeDelta from a_currentTicks (a millisecond counter),
		// applying smoothing/fixed-timestep clamping. No-ops while pauseCount != 0.
		void Update(std::int32_t a_currentTicks)
		{
			using func_t = decltype(&BSTimer::Update);
			static REL::Relocation<func_t> func{ RELOCATION_ID(66987, 68244) };
			return func(this, a_currentTicks);
		}

		// members: layout is identical on SE/AE/VR
		float*        smoothingBuffer;                // 00: ring buffer of past deltas, sized by smoothingSampleCount
		std::int64_t  qpcBaseline;                    // 08: one 64-bit QueryPerformanceCounter value, not two uint32_t
		float         clamp;                          // 10: fixed-timestep step size in ticks; 0 = variable timestep
		float         clampRemainder;                 // 14: fractional tick carry for the fixed-timestep accumulator
		float         delta;                          // 18: game-time delta = realTimeDelta * global time multiplier
		float         realTimeDelta;                  // 1C: wall-clock delta, captured before the multiplier is applied
		std::uint32_t smoothedRunTimeMS;              // 20: ms-scale elapsed runtime, averaged when smoothing is active
		std::uint32_t runTimeMS;                      // 24: ms-scale elapsed runtime, set unconditionally every update
		std::uint32_t runTimeMSBaseline;              // 28: external elapsed-runtime input is diffed against this
		std::uint32_t pausedSmoothedRunTimeOffset;    // 2C: Pause() scratch restoring smoothedRunTimeMS on Unpause()
		std::uint32_t pausedRunTimeOffset;            // 30: Pause() scratch restoring runTimeMSBaseline on Unpause()
		std::uint32_t pauseCount;                     // 34: nested Pause()/Unpause() reference count, not a bool
		std::uint8_t  smoothingSampleCount;           // 38: sample window; 0-2 = passthrough, >=3 = moving average
		std::uint8_t  smoothingBufferIndex;           // 39: write index into smoothingBuffer, wraps mod smoothingSampleCount
		bool          useGlobalTimeMultiplierTarget;  // 3A: refreshed every frame from ini bChangeTimeMultSlowly:General
		std::uint8_t  pad3B;                          // 3B
		std::uint32_t pad3C;                          // 3C
	};
	static_assert(sizeof(BSTimer) == 0x40);
}
