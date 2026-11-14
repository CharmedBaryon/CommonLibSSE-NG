#pragma once

#include "RE/N/NiFogProperty.h"

namespace RE
{
	class BSFogProperty : public NiFogProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFogProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFogProperty;
		inline static constexpr auto VTABLE = VTABLE_BSFogProperty;

		~BSFogProperty();

		// override (NiFogProperty)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// members
		float         nearDistance;  // 50
		float         farDistance;   // 54
		std::uint32_t unk58;         // 58
		std::uint32_t unk5C;         // 5C
		std::uint64_t unk60;         // 60
		std::uint64_t unk68;         // 68
		std::uint64_t unk70;         // 70
		std::uint64_t unk78;         // 78
		float         unk80;         // 80
		float         power;         // 84
		float         clamp;         // 88
		std::uint32_t pad8C;         // 8C
	};
	static_assert(sizeof(BSFogProperty) == 0x90);
}
