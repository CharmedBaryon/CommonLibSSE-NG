#pragma once

namespace RE
{
	class GFxSetBackgroundColor : public GASExecuteTag
	{
	public:
		virtual ~GFxSetBackgroundColor();  // 00

		// override (GASExecuteTag)
		void Execute1(GFxSprite* a_sprite) override;  // 01

		// members
		std::uint64_t unk08;  // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxSetBackgroundColor) == 0x10);
}
