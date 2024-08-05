#pragma once

#include "RE/N/NiGeometry.h"

namespace RE
{
	class NiTriBasedGeometry : public NiGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriBasedGeom;
		inline static auto           Ni_RTTI = NiRTTI_NiTriBasedGeom;
		inline static constexpr auto VTABLE = VTABLE_NiTriBasedGeom;

		~NiTriBasedGeometry() override;  // 00

		// override (NiGeometry)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C
		void          Unk_36(void);                                      // 36
		void          Unk_37(void);                                      // 37

		// override (NiObject)
		NiTriBasedGeom* AsNiTriBasedGeom() override;  // 0E
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(NiTriBasedGeometry) == 0x160);
#else
	static_assert(sizeof(NiTriBasedGeometry) == 0x138);
#endif
}
