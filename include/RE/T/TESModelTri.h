#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class TESModelTri : public TESModel
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESModelTri;
		inline static constexpr auto VTABLE = VTABLE_TESModelTri;

		~TESModelTri() override;  // 00

		// override (TESModel)
		void SetModel(const char* a_model) override;  // 05
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESModelTri) == 0x28);
}
