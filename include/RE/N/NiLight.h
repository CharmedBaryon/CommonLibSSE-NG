#pragma once

#include "RE/N/NiAVObject.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiLight : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiLight;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiLight;
		inline static constexpr auto VTABLE = VTABLE_NiLight;

		struct LIGHT_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT         \
	NiColor       ambient; /* 00 */  \
	NiColor       diffuse; /* 0C */  \
	NiPoint3      radius;  /* 018 */ \
	float         fade;    /* 024 */ \
	std::uint32_t unk138;  /* 028 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(LIGHT_RUNTIME_DATA) == 0x2C);

		~NiLight() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                 // 02
		void          LoadBinary(NiStream& a_stream) override;  // 18
		void          SaveBinary(NiStream& a_stream) override;  // 1B
		bool          IsEqual(NiObject* a_object) override;     // 1C

		[[nodiscard]] inline LIGHT_RUNTIME_DATA& GetLightRuntimeData() noexcept
		{
			return REL::RelocateMember<LIGHT_RUNTIME_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const LIGHT_RUNTIME_DATA& GetLightRuntimeData() const noexcept
		{
			return REL::RelocateMember<LIGHT_RUNTIME_DATA>(this, 0x110, 0x138);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 110, 138
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiLight) == 0x140);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiLight) == 0x168);
#endif
}
#undef RUNTIME_DATA_CONTENT
