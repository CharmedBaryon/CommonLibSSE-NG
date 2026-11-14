#pragma once

#include "RE/B/bhkSerializable.h"

namespace RE
{
	class bhkAction : public bhkSerializable
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkAction;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkAction;
		inline static constexpr auto VTABLE = VTABLE_bhkAction;

		~bhkAction() override;  // 00

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;                   // 02
		void          AdjustRefCount(bool a_increment) override;  // 26
		hkpWorld*     GetWorld1() override;                       // 27
		ahkpWorld*    GetWorld2() override;                       // 28
		void          MoveToWorld(bhkWorld* a_world) override;    // 29
		void          RemoveFromCurrentWorld() override;          // 2A

		// add
		virtual void Unk_32(void);  // 32
	};
	static_assert(sizeof(bhkAction) == 0x20);
}
