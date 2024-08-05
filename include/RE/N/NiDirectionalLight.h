#pragma once

#include "RE/N/NiLight.h"

namespace RE
{
	class NiDirectionalLight : public NiLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiDirectionalLight;
		inline static auto           Ni_RTTI = NiRTTI_NiDirectionalLight;

		struct DIRECTIONAL_LIGHT_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	NiPoint3 worldDir; /* 00 */ \
	char     _pad[0xC];   /* 0c  NiColor m_kEffectColor? */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(DIRECTIONAL_LIGHT_RUNTIME_DATA) == 0x18);

		~NiDirectionalLight() override;  // 00

		// override (NiLight)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C

		[[nodiscard]] inline DIRECTIONAL_LIGHT_RUNTIME_DATA& GetDirectionalLightRuntimeData() noexcept
		{
			return REL::RelocateMember<DIRECTIONAL_LIGHT_RUNTIME_DATA>(this, 0x140, 0x168);
		}

		[[nodiscard]] inline const DIRECTIONAL_LIGHT_RUNTIME_DATA& GetDirectionalLightRuntimeData() const noexcept
		{
			return REL::RelocateMember<DIRECTIONAL_LIGHT_RUNTIME_DATA>(this, 0x140, 0x168);
		}

		// The model direction of the light is (1,0,0). The world direction is
		// the first column of the world rotation matrix.
		inline const NiPoint3& GetWorldDirection() const
		{
			return GetDirectionalLightRuntimeData().worldDir;
		}
		// members

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 140, 168
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiDirectionalLight) == 0x158);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiDirectionalLight) == 0x180);
#endif
}
#undef RUNTIME_DATA_CONTENT
