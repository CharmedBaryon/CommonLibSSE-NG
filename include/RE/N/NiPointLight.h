#pragma once

#include "RE/N/NiLight.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	class NiPointLight : public NiLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPointLight;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPointLight;
		inline static constexpr auto VTABLE = VTABLE_NiPointLight;

		struct POINT_LIGHT_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT             \
	float constAttenuation;     /* 00 */ \
	float linearAttenuation;    /* 04 */ \
	float quadraticAttenuation; /* 08 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(POINT_LIGHT_RUNTIME_DATA) == 0x0C);

		~NiPointLight() override;  // 00

		// override (NiLight)
		const NiRTTI*        GetRTTI() const override;                           // 02
		NiObject*            CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void                 LoadBinary(NiStream& a_stream) override;            // 18
		void                 SaveBinary(NiStream& a_stream) override;            // 1B
		bool                 IsEqual(NiObject* a_object) override;               // 1C
		static NiPointLight* Create()
		{
			auto light = malloc<NiPointLight>();
			std::memset(light, 0, sizeof(NiPointLight));
			if (light) {
				light->Ctor();
			}
			return light;
		}

		void SetLightAttenuation(float a_radius)
		{
			using func_t = decltype(&NiPointLight::SetLightAttenuation);
			static REL::Relocation<func_t> func{ RELOCATION_ID(17224, 17626) };
			return func(this, a_radius);
		}

		[[nodiscard]] inline POINT_LIGHT_RUNTIME_DATA& GetPointLightRuntimeData() noexcept
		{
			return REL::RelocateMember<POINT_LIGHT_RUNTIME_DATA>(this, 0x140, 0x168);
		}

		[[nodiscard]] inline const POINT_LIGHT_RUNTIME_DATA& GetPointLightRuntimeData() const noexcept
		{
			return REL::RelocateMember<POINT_LIGHT_RUNTIME_DATA>(this, 0x140, 0x168);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 140, 168
#endif
	private:
		NiPointLight* Ctor()
		{
			using func_t = decltype(&NiPointLight::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(69583, 70967) };
			return func(this);
		}
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiPointLight) == 0x150);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiPointLight) == 0x178);
#endif
}
#undef RUNTIME_DATA_CONTENT
