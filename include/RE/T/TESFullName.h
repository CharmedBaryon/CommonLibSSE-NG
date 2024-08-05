#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESFullName : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESFullName;
		inline static constexpr auto VTABLE = VTABLE_TESFullName;

		~TESFullName() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { name = ""; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual std::uint32_t GetFullNameLength() const;  // 04
		[[nodiscard]] virtual const char*   GetFullName() const;        // 05

		void SetFullName(const char* a_name)
		{
			using func_t = decltype(&TESFullName::SetFullName);
			static REL::Relocation<func_t> func{ RELOCATION_ID(22318, 22791) };
			func(this, a_name);
		}

		// members
		BSFixedString fullName;  // 08 - FULL
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESFullName) == 0x10);
}
