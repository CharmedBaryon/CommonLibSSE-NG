#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESBoundObject;

	class BGSMenuDisplayObject : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSMenuDisplayObject;
		inline static constexpr auto VTABLE = VTABLE_BGSMenuDisplayObject;

		~BGSMenuDisplayObject() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual TESBoundObject* GetMenuDisplayObject() const;  // 04 - { return menuDispObject; }

		// members
		TESBoundObject* menuDispObject;  // 08 - MDOB
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSMenuDisplayObject) == 0x10);
}
