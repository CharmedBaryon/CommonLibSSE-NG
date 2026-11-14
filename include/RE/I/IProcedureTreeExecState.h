#pragma once

namespace RE
{
	// Base interface for per-node AI procedure execution state.
	// Concrete subtypes: BGSProcedureTreeOneChildExecState (branch/sequence nodes),
	// BGSProcedureXxxExecState (leaf procedures via BGSTypedItem<T, IProcedureTreeExecState>).
	class IProcedureTreeExecState
	{
	public:
		inline static constexpr auto RTTI = RTTI_IProcedureTreeExecState;
		inline static constexpr auto VTABLE = VTABLE_IProcedureTreeExecState;

		virtual ~IProcedureTreeExecState() = default;  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
		virtual void Unk_03(void) = 0;  // 03
		virtual void Unk_04(void) = 0;  // 04
		virtual void Unk_05(void) = 0;  // 05 - used by ValidateExecState
		virtual void Unk_06(void) = 0;  // 06
		virtual void Unk_07(void);      // 07
		virtual void Unk_08(void);      // 08
	};
	static_assert(sizeof(IProcedureTreeExecState) == 0x8);
}
