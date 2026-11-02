#pragma once

#include "RE/B/BGSTypedItem.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IProcedureTreeExecState.h"

namespace RE
{
	class BGSPackageDataLocation;
	class BSPathingRequest;
	class IAIWorldLocation;

	class BGSProcedureTravelExecState : public BGSTypedItem<BGSProcedureTravelExecState, IProcedureTreeExecState>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSProcedureTravelExecState;
		inline static constexpr auto VTABLE = VTABLE_BGSProcedureTravelExecState;

		~BGSProcedureTravelExecState() override;  // 00

		// members
		IAIWorldLocation*                 location;            // 08
		BGSPackageDataLocation*           locationData;        // 10
		BSTSmartPointer<BSPathingRequest> pathingRequest;      // 18
		bool                              unk20;               // 20
		bool                              weaponsReequipped;   // 21
		bool                              pathingSearchFlag8;  // 22
		bool                              atDestination;       // 23
		std::uint32_t                     pad24;               // 24
	};
	static_assert(sizeof(BGSProcedureTravelExecState) == 0x28);
}
