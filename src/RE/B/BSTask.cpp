#include "RE/B/BSTask.h"

namespace RE
{
	bool BSTask::GetDescription(char* a_dest, std::uint32_t a_maxCount)
	{
		constexpr std::string_view name = "Unnamed";

		if (!a_dest || a_maxCount == 0) {
			return false;
		}

		const auto count = std::min<std::size_t>(name.size(), a_maxCount - 1);
		std::memcpy(a_dest, name.data(), count);
		a_dest[count] = '\0';
		return false;
	}
}
