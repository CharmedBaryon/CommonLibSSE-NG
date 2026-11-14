#pragma once

#include "RE/A/AIProcess.h"

namespace RE
{
	enum class PROCESS_TYPE;
	class Actor;

	class MobIterOperator
	{
	public:
		inline static constexpr auto RTTI = RTTI_MobIterOperator;
		inline static constexpr auto VTABLE = VTABLE_MobIterOperator;

		virtual ~MobIterOperator();  // 00

		// add
		virtual void Operate(Actor* a_actor);  // 01

		// members
		REX::EnumSet<PROCESS_TYPE, std::uint8_t> processType;  // 00
	};
	static_assert(sizeof(MobIterOperator) == 0x10);
}
