#pragma once

#include <RE/N/NiAVObject.h>
#include <RE/N/NiGeometryData.h>
#include <RE/N/NiProperty.h>
#include <RE/N/NiSkinInstance.h>
#include <cstdint>

namespace RE
{
	class NiGeometry : public NiAVObject
	{
	public:
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                               \
	NiPointer<NiProperty>     m_spPropertyState; /* 110 */ \
	NiPointer<NiProperty>     m_spEffectState;   /* 118 */ \
	NiPointer<NiSkinInstance> m_spSkinInstance;  /* 120 */ \
	NiPointer<NiGeometryData> m_spModelData;     /* 128 */ \
	std::uint64_t             unk130;            /* 130 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x28);

		void          Unk_35(void);                           // 35, 36 - call controller vtbl+0xA0?
		void          Unk_36(void);                           // 36, 37 - ret 0
		void          Unk_37(void);                           // 37, 38 - same as Unk_33
		void*         Unk_38(void);                           // 38, 39 - ret call m_spModelData vtbl+0x9C
		void          SetGeometryData(NiGeometryData* unk1);  // 39, 3A - set and AddRef geometry data
		void*         Unk_3A(void);                           // 3A, 3B - ret call m_spModelData vtbl+0x94
		std::uint16_t Unk_3B(bool unk1);                      // 3B, 3C ??

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		RUNTIME_DATA_CONTENT  // 110, 138
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(NiGeometry) == 0x160);
#else
	static_assert(sizeof(NiGeometry) == 0x138);
#endif
}
#undef RUNTIME_DATA_CONTENT
