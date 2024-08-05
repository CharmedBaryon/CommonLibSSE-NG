#pragma once

#include "RE/B/bhkPCollisionObject.h"

namespace RE
{
	class bhkSPCollisionObject : public bhkPCollisionObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkSPCollisionObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkSPCollisionObject;
		inline static constexpr auto VTABLE = VTABLE_bhkSPCollisionObject;

		~bhkSPCollisionObject() override;  // 00

		// override (bhkSPCollisionObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		void          Unk_2B() override;                                  // 2B
		void          Unk_2C() override;                                  // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkSPCollisionObject) == 0x28);
}
