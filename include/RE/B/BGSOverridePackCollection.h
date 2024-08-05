#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class BGSListForm;

	class BGSOverridePackCollection : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSOverridePackCollection;
		inline static constexpr auto VTABLE = VTABLE_BGSOverridePackCollection;

		~BGSOverridePackCollection() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// members
		BGSListForm* spectatorOverRidePackList;      // 08 - SPOR
		BGSListForm* observeCorpseOverRidePackList;  // 10 - OCOR
		BGSListForm* guardWarnOverRidePackList;      // 18 - GWOR
		BGSListForm* enterCombatOverRidePackList;    // 20 - ECOR
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSOverridePackCollection) == 0x28);
}
