#pragma once

#include "RE/B/BSTask.h"

namespace RE
{
	class IOTask : public BSTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_IOTask;
		inline static constexpr auto VTABLE = VTABLE_IOTask;

		~IOTask() override;  // 00

		// add
		virtual bool Process();                             // 05 - { return false; }
		virtual void PostProcess();                         // 06 - { return; }
		virtual void GenerateKey();                         // 07
		virtual void Requeue(std::uint32_t a_newPriority);  // 08
	};
	STATIC_ASSERT_SIZE(IOTask, 0x18, 0x20);
}
