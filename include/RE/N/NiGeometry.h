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
		virtual void          Unk_33(void);                           // call controller vtbl+0xA0?
		virtual void          Unk_34(void);                           // ret 0
		virtual void          Unk_35(void);                           // same as Unk_33
		virtual void*         Unk_36(void);                           // ret call m_spModelData vtbl+0x9C
		virtual void          SetGeometryData(NiGeometryData* unk1);  // set and AddRef geometry data
		virtual void*         Unk_38(void);                           // ret call m_spModelData vtbl+0x94
		virtual std::uint16_t Unk_39(bool unk1);                      // ??

		NiPointer<NiProperty>     m_spPropertyState;  // 110
		NiPointer<NiProperty>     m_spEffectState;    // 118
		NiPointer<NiSkinInstance> m_spSkinInstance;   // 120
		NiPointer<NiGeometryData> m_spModelData;      // 128
		std::uint64_t             unk130;             // 130
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(NiGeometry) == 0x160);
#else
	static_assert(sizeof(NiGeometry) == 0x138);
#endif
}
