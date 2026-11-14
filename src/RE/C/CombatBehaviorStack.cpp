#include "RE/C/CombatBehaviorStack.h"

namespace RE
{
	void CombatBehaviorStack::CheckBuffer(std::uint32_t a_size)
	{
		// AE inlines this into its callers; a relocation there calls an unrelated function.
		if (REL::Module::IsAE()) {
			if (bufferSize < a_size) {
				const auto oldBuffer = buffer;
				bufferSize = (std::max)(a_size * 2, std::uint32_t{ 0x10 });
				buffer = static_cast<char*>(malloc(bufferSize));
				if (oldBuffer) {
					std::memcpy(buffer, oldBuffer, size);
					free(oldBuffer);
				}
			}
			return;
		}

		using func_t = decltype(&CombatBehaviorStack::CheckBuffer);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32426, 0) };
		return func(this, a_size);
	}
}
