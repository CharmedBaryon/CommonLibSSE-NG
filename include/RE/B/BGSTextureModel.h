#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class BGSTextureModel : public TESModel
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSTextureModel;
		inline static constexpr auto VTABLE = VTABLE_BGSTextureModel;

		~BGSTextureModel() override;  // 00

		// override (TESModel)
		void SetModel(const char* a_model) override;  // 05
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSTextureModel) == 0x28);
}
