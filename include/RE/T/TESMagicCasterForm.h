#pragma once

namespace RE
{
	class TESMagicCasterForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESMagicCasterForm;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESMagicCasterForm) == 0x1);
}
