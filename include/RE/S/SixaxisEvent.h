#pragma once

#include "RE/I/IDEvent.h"
#include "RE/N/NiQuaternion.h"

namespace RE
{
#ifdef ENABLE_SKYRIM_AE
#	pragma pack(push, 4)
	class SixaxisEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_SixaxisEvent;
		inline static constexpr auto VTABLE = VTABLE_SixaxisEvent;

		~SixaxisEvent() override;  // 00

		// members
		std::uint32_t unk28;        // 28
		std::uint32_t unk2C;        // 2C - not zero-initialized by the ctor
		std::uint64_t unk30;        // 30
		std::uint64_t unk38;        // 38
		std::uint32_t unk40;        // 40
		std::uint64_t unk44;        // 44
		std::uint32_t unk4C;        // 4C
		std::uint64_t unk50;        // 50
		std::uint32_t unk58;        // 58
		std::uint64_t unk5C;        // 5C
		std::uint32_t unk64;        // 64
		std::uint64_t unk68;        // 68
		std::uint32_t unk70;        // 70
		std::uint64_t unk74;        // 74
		std::uint32_t unk7C;        // 7C
		NiQuaternion  orientation;  // 80
	};
#	pragma pack(pop)
	static_assert(sizeof(SixaxisEvent) == 0x90);
#endif
}
