#pragma once

#include "RE/I/IDEvent.h"

namespace RE
{
#ifdef ENABLE_SKYRIM_AE
#	pragma pack(push, 4)
	class AmiiboEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_AmiiboEvent;
		inline static constexpr auto VTABLE = VTABLE_AmiiboEvent;

		~AmiiboEvent() override;  // 00

		// members
		std::uint32_t unk28;  // 28 - not zero-initialized by the ctor
		std::uint64_t unk2C;  // 2C
		std::uint16_t unk34;  // 34
		std::uint16_t unk36;  // 36 - not zero-initialized by the ctor
		std::uint32_t unk38;  // 38
		std::uint32_t unk3C;  // 3C - not zero-initialized by the ctor
	};
#	pragma pack(pop)
	static_assert(sizeof(AmiiboEvent) == 0x40);
#endif
}
