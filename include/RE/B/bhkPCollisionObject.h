#pragma once

#include "RE/B/bhkNiCollisionObject.h"

namespace RE
{
	class bhkPCollisionObject : public bhkNiCollisionObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkPCollisionObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkPCollisionObject;
		inline static constexpr auto VTABLE = VTABLE_bhkPCollisionObject;

		~bhkPCollisionObject() override;  // 00

		// override (bhkNiCollisionObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		void          Unk_2B() override;                                  // 2B
		void          Unk_2C() override;                                  // 2C
		void          Unk_2F() override;                                  // 2F
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkPCollisionObject) == 0x28);
}
