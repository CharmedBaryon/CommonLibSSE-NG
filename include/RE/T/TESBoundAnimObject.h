#pragma once

#include "RE/T/TESBoundObject.h"

namespace RE
{
	class TESBoundAnimObject : public TESBoundObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESBoundAnimObject;
		inline static constexpr auto VTABLE = VTABLE_TESBoundAnimObject;

		~TESBoundAnimObject() override;  // 00

		// override (TESBoundObject)
		bool IsBoundAnimObject() override;              // 3C - { return true; }
		bool ReplaceModel(const char* a_str) override;  // 4B
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESBoundAnimObject) == 0x30);
}
