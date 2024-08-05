#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class BGSBehaviorGraphModel : public TESModel
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSBehaviorGraphModel;
		inline static constexpr auto VTABLE = VTABLE_BGSBehaviorGraphModel;

		~BGSBehaviorGraphModel() override;  // 00

		// override (TESModel)
		void SetModel(const char* a_model) override;  // 05
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSBehaviorGraphModel) == 0x28);
}
