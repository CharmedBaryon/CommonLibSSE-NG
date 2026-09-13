#pragma once

#include "RE/B/bhkAction.h"

namespace RE
{
	class bhkUnaryAction : public bhkAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkUnaryAction;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkUnaryAction;
		inline static constexpr auto VTABLE = VTABLE_bhkUnaryAction;

		~bhkUnaryAction() override;  // 00

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C
		void          MoveToWorld(bhkWorld* a_world) override;           // 29
	};
	static_assert(sizeof(bhkUnaryAction) == 0x20);
}
