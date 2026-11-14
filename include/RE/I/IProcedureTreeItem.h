#pragma once

#include "RE/I/IProcedureTreeExecState.h"

namespace RE
{
	class Actor;
	class ActorPackage;
	class TESFile;
	class TESQuest;

	class IProcedureTreeItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_IProcedureTreeItem;
		inline static constexpr auto VTABLE = VTABLE_IProcedureTreeItem;

		// Per-invocation execution context, built on the caller's stack (e.g. SE Character::sub_1405E20D0
		// -> FUN_1406429D0) and passed down through Execute(). No RTTI (plain struct).
		struct ProcedureExecContext
		{
			Actor*    actor;                  // 00
			TESQuest* ownerQuest;             // 08 - TESPackage::ownerQuest of the running package
			void*     packageDataTail;        // 10 - ActorPackage::data cast past ActorPackageData's 8-byte vtable
											  //      ptr; points to the concrete subclass's own fields (e.g.
											  //      EscortActorPackageData, GuardActorPackageData) -- type depends
											  //      on the running package's PACKAGE_PROCEDURE_TYPE
			ActorPackage* package;            // 18 - the currently executing package
			bool          unk20;              // 20 - usually 0; propagated from an outer bool param in one caller
			bool          recheckConditions;  // 21 - constant true in normal AI-tick callers; computed from
											  //      TESCustomPackageData::alwaysRecheckConditions in one caller;
											  //      false in the query-only GameFunc::IsWarningAbout
			bool          continueFlag;       // 22 - cleared before each Execute call; caller checks it after
			std::uint8_t  pad23[5];           // 23
			void*         manager;            // 28 - stack-local closure; vtable[1] = SetActiveProcedure(BGSProcedureBase*)
			float         deltaTime;          // 30 - gSecondsSinceLastFrame_WorldTime at every observed call site
			std::uint32_t processType;        // 34 - RE::PROCESS_TYPE in the low byte (see Character::GetActorProcessType)
		};
		static_assert(sizeof(ProcedureExecContext) == 0x38);

		// Opaque pair passed to Execute().
		struct ExecStateContext
		{
			ProcedureExecContext*    context;    // 00
			IProcedureTreeExecState* nodeState;  // 08 - node-specific state (e.g. BGSProcedureTreeOneChildExecState)
		};
		static_assert(sizeof(ExecStateContext) == 0x10);

		virtual ~IProcedureTreeItem();  // 00

		// add
		virtual void Unk_01(void) = 0;                            // 01
		virtual void Unk_02(void) = 0;                            // 02
		virtual void Load(TESFile* a_mod) = 0;                    // 03
		virtual void Execute(ExecStateContext* a_execState) = 0;  // 04
		virtual void Unk_05(void) = 0;                            // 05
		virtual void Unk_06(void) = 0;                            // 06
		virtual void Unk_07(void) = 0;                            // 07
		virtual void Unk_08(void);                                // 08
		virtual void Unk_09(void);                                // 09
		virtual void Unk_0A(void) = 0;                            // 0A
		virtual void Unk_0B(void) = 0;                            // 0B
		virtual void Unk_0C(void) = 0;                            // 0C
		virtual void Unk_0D(void) = 0;                            // 0D
		virtual void Unk_0E(void) = 0;                            // 0E
		virtual void Unk_0F(void) = 0;                            // 0F
		virtual void Unk_10(void) = 0;                            // 10
	};
	static_assert(sizeof(IProcedureTreeItem) == 0x8);
}
