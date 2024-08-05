#pragma once

#include "RE/B/BGSLocalizedStringDL.h"
#include "RE/B/BSString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESForm;

	class TESDescription : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESDescription;
		inline static constexpr auto VTABLE = VTABLE_TESDescription;

		~TESDescription() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		void GetDescription(BSString& a_out, TESForm* a_parent, std::uint32_t a_fieldType = 'CSED');

		// members
		std::uint32_t        fileOffset;       // 08
		BGSLocalizedStringDL descriptionText;  // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESDescription) == 0x10);
}
