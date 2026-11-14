#pragma once

#include "RE/B/bhkUnaryAction.h"

namespace RE
{
	class bhkMouseSpringAction : public bhkUnaryAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkMouseSpringAction;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkMouseSpringAction;
		inline static constexpr auto VTABLE = VTABLE_bhkMouseSpringAction;

		~bhkMouseSpringAction() override;  // 00

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		void          Unk_2B(void) override;                              // 2B
		void          Unk_2C(void) override;                              // 2C
		virtual void  Unk_2E(void) override;                              // 2E
		virtual void  Unk_2F(void) override;                              // 2F
	};
	static_assert(sizeof(bhkMouseSpringAction) == 0x20);
}
