#pragma once

namespace RE
{
	class TESMagicTargetForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESMagicTargetForm;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESMagicTargetForm) == 0x1);
}
