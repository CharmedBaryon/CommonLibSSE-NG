#pragma once

#include "RE/A/ActionInput.h"
#include "RE/A/ActionOutput.h"

namespace RE
{
	class BGSActionData :
		public ActionInput,  // 00
		public ActionOutput  // 28
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSActionData;
		inline static constexpr auto VTABLE = VTABLE_BGSActionData;

		virtual ~BGSActionData() override;  // 00

		// add
		virtual BGSActionData* Clone() const;  // 04
		virtual bool           Process();      // 05 - { return false; }

		// members
		uint32_t flags;  // 58
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSActionData) == 0x60);
}
