#pragma once

#include "RE/N/NiExtraData.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSInvMarker : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSInvMarker;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSInvMarker;
		inline static constexpr auto VTABLE = VTABLE_BSInvMarker;

		~BSInvMarker() override;  // 00

		// override (NiExtraData)
		const NiRTTI* GetRTTI() const override;                                                            // 02
		NiObject*     CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override { return this; }  // 17
		void          LoadBinary(NiStream& a_stream) override;                                             // 18
		void          LinkObject(NiStream& a_stream) override;                                             // 19 - { return; }
		bool          RegisterStreamables(NiStream& a_stream) override;                                    // 1A
		void          SaveBinary(NiStream& a_stream) override;                                             // 1B
		bool          IsEqual(NiObject* a_object) override;                                                // 1C

		RE::NiPoint3 GetRotationEulerAnglesXYZ() const;

		// members
		float         zoom;       // 18
		std::uint16_t rotationX;  // 1C
		std::uint16_t rotationY;  // 1E
		std::uint16_t rotationZ;  // 20
		std::uint8_t  pad22[6];   // 22
	};
	static_assert(sizeof(BSInvMarker) == 0x28);
}
