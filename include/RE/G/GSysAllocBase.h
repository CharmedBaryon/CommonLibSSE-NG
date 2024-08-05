#pragma once

namespace RE
{
	class GSysAllocBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_GSysAllocBase;
		inline static constexpr auto VTABLE = VTABLE_GSysAllocBase;

		virtual ~GSysAllocBase() = default;  // 00

		// add
		virtual bool InitHeapEngine([[maybe_unused]] const void* a_heapDesc) { return false; }  // 01
		virtual void ShutdownHeapEngine() { return; }                                           // 02
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GSysAllocBase) == 0x8);
}
