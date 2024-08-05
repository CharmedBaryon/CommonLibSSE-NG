#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class TESModelRDT : public TESModel
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESModelRDT;
		inline static constexpr auto VTABLE = VTABLE_TESModelRDT;

		~TESModelRDT() override;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESModelRDT) == 0x28);
}
