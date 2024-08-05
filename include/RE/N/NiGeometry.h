#pragma once

#include "RE/N/NiAVObject.h"
#include "RE/N/NiGeometryData.h"
#include "RE/N/NiProperty.h"
#include "RE/N/NiSkinInstance.h"

namespace RE
{
	class NiGeometry : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiGeometry;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiGeometry;
		inline static constexpr auto VTABLE = VTABLE_NiGeometry;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                             \
	NiPointer<NiProperty>     spPropertyState; /* 110 */ \
	NiPointer<NiProperty>     spEffectState;   /* 118 */ \
	NiPointer<NiSkinInstance> spSkinInstance;  /* 120 */ \
	NiPointer<NiGeometryData> spModelData;     /* 128 */ \
	std::uint64_t             unk130;          /* 130 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x28);

		~NiGeometry() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                                                                                    // 02
		void          LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void          LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                        // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                          // 1D

		// override (NiObject)
		NiGeometry* AsNiGeometry() { return nullptr; }                             // 0D
		void        PostLinkObject([[maybe_unused]] NiStream& a_stream) override;  // 1E

		// add
		SKYRIM_REL_VR_VIRTUAL void  Unk_35(void);                           // 35, 36 - call controller vtbl+0xA0?
		SKYRIM_REL_VR_VIRTUAL void  Unk_36(void);                           // 36, 37 - ret 0
		SKYRIM_REL_VR_VIRTUAL void  Unk_37(void);                           // 37, 38 - same as Unk_33
		SKYRIM_REL_VR_VIRTUAL void* Unk_38(void);                           // 38, 39 - ret call m_spModelData vtbl+0x9C
		SKYRIM_REL_VR_VIRTUAL void  SetGeometryData(NiGeometryData* unk1);  // 39, 3A - set and AddRef geometry data
		SKYRIM_REL_VR_VIRTUAL void* Unk_3A(void);                           // 3A, 3B - ret call m_spModelData vtbl+0x94
		SKYRIM_REL_VR_VIRTUAL std::uint16_t Unk_3B(bool unk1);              // 3B, 3C ??

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		RUNTIME_DATA_CONTENT;  // 110, 138
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiGeometry) == 0x160);
#else
	static_assert(sizeof(NiGeometry) == 0x138);
#endif
}
#undef RUNTIME_DATA_CONTENT
