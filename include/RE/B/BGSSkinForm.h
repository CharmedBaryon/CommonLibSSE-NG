#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESObjectARMO;

	class BGSSkinForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSkinForm;
		inline static constexpr auto VTABLE = VTABLE_BGSSkinForm;

		~BGSSkinForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// members
		TESObjectARMO* skin;  // 08 - WNAM
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSkinForm) == 0x10);
}
