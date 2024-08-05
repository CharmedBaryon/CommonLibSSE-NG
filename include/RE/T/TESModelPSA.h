#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class TESModelPSA : public TESModel
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESModelPSA;
		inline static constexpr auto VTABLE = VTABLE_TESModelPSA;

		~TESModelPSA() override;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESModelPSA) == 0x28);
}
