#pragma once

namespace RE
{
	class ActorValueInfo;

	class UpdateConstellationAnims
	{
	public:
		inline static constexpr auto RTTI = RTTI___UpdateConstellationAnims;
		inline static constexpr auto VTABLE = VTABLE___UpdateConstellationAnims;

		virtual void Unk_00(void* a_unk);  // 00

		// members
		ActorValueInfo* unk08;  // 08
	};
	static_assert(sizeof(UpdateConstellationAnims) == 0x10);
}
