#pragma once

namespace RE
{
	struct BSThreadEvent
	{
		static void InitSDM()
		{
			using func_t = decltype(&BSThreadEvent::InitSDM);
			static REL::Relocation<func_t> func{ RELOCATION_ID(67151, 68449) };
			return func();
		}

	private:
		KEEP_FOR_RE()
	};
}
