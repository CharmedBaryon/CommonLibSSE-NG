#pragma once

#include "RE/N/NiLight.h"

#include "RE/M/MemoryManager.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiDirectionalLight : public NiLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiDirectionalLight;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiDirectionalLight;
		inline static constexpr auto VTABLE = VTABLE_NiDirectionalLight;

		struct DIRECTIONAL_LIGHT_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	NiPoint3 worldDir;    /* 00 */ \
	NiColor  effectColor; /* 0c  NiColor m_kEffectColor? */

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

		static NiDirectionalLight* Create()
		{
			// sizeof(NiDirectionalLight) is wrong under SKYRIM_CROSS_VR (runtime-data
			// members stripped); allocate the real per-runtime size. See malloc_runtime.
			auto light = malloc_runtime<NiDirectionalLight>(0x158, 0x180);
			if (light) {
				light->Ctor();
			}
			return light;
		}

		RUNTIME_DATA_ACCESSOR_EX(DIRECTIONAL_LIGHT_RUNTIME_DATA, GetDirectionalLightRuntimeData, 0x140, 0x168);
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

			private :
			NiDirectionalLight*
			Ctor()
		{
			using func_t = decltype(&NiDirectionalLight::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(69692, 71073) };
			return func(this);
		}
	};
	STATIC_ASSERT_SIZE(NiDirectionalLight, 0x158, 0x158, 0x180, 0x110);
}
#undef RUNTIME_DATA_CONTENT
