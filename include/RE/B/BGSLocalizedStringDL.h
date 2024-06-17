#pragma once

namespace RE
{
	class BGSLocalizedStringDL
	{
	public:
		// members
		std::uint32_t id;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSLocalizedStringDL) == 0x4);
}
