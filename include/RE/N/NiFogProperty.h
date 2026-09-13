#pragma once

#include "RE/N/NiObjectNET.h"
#include "RE/N/NiProperty.h"

namespace RE
{
	class NiFogProperty : public NiProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFogProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiFogProperty;
		inline static constexpr auto VTABLE = VTABLE_NiFogProperty;

		~NiFogProperty();

		// override (NiProperty)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
		Type          GetType() const override;                           // 25

		// members
		std::uint32_t unk30;      // 30
		float         unk34;      // 34
		NiColor       nearColor;  // 38
		NiColor       farColor;   // 44
	};
	static_assert(sizeof(NiFogProperty) == 0x50);
}
