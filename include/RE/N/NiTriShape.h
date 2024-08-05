#pragma once

#include "RE/N/NiTriBasedGeometry.h"

namespace RE
{
	class NiTriShape : public NiTriBasedGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriShape;
		inline static auto           Ni_RTTI = NiRTTI_NiTriShape;
		inline static constexpr auto VTABLE = VTABLE_NiTriShape;

		~NiTriShape() override;  // 00

		// override (NiTriBasedGeometry)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C

		// override (NiObject)
		NiTriShape* AsNiTriShape() override;                                             // 0F
		NiObject*   CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override;  // 17

		// add
		virtual std::uint16_t Unk_3B(bool unk1);  // 3B
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(NiTriShape) == 0x160);
#else
	static_assert(sizeof(NiTriShape) == 0x138);
#endif
}
