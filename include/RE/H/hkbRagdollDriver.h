#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbRagdollDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRagdollDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbRagdollDriver;

		~hkbRagdollDriver() override;  // 00

		// members
		std::uint64_t       unk10;                   // 10
		std::uint64_t       unk18;                   // 18
		std::uint64_t       unk20;                   // 20
		std::uint64_t       unk28;                   // 28
		std::uint64_t       unk30;                   // 30
		std::uint64_t       unk38;                   // 38
		std::uint64_t       unk40;                   // 40
		std::uint64_t       unk48;                   // 48
		std::uint64_t       unk50;                   // 50
		hkArray<int32_t>    reportingWhenKeyframed;  // 58
		std::uint64_t       unk68;                   // 68
		std::uint64_t       unk70;                   // 70
		std::uint64_t       unk78;                   // 78
		hkbCharacter*       character;               // 80
		hkaRagdollInstance* ragdoll;                 // 88
		std::uint64_t       unk90;                   // 90
		std::uint64_t       unk98;                   // 98
		std::uint64_t       unkA0;                   // A0
		std::uint64_t       unkA8;                   // A8
		std::uint64_t       unkB0;                   // B0
		std::uint32_t       unkB8;                   // B8
		float               unkBC;                   // BC
		float               unkC0;                   // C0
		std::uint32_t       unkC4;                   // C4
		std::uint64_t       unkC8;                   // C8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbRagdollDriver) == 0xD0);
}
