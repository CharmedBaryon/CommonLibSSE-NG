#pragma once

#include "RE/B/BSAnimationGraphManager.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/I/IAnimationGraphManagerHolder.h"

namespace RE
{
	class WeaponAnimationGraphManagerHolder :
		public IAnimationGraphManagerHolder,  // 00
		public BSIntrusiveRefCounted          // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_WeaponAnimationGraphManagerHolder;
		inline static constexpr auto VTABLE = VTABLE_WeaponAnimationGraphManagerHolder;

		// override (IAnimationGraphManagerHolder)
		bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_out) const override;  // 02 - { a_out = animationGraphManager; return a_out; }
		bool SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_in) override;         // 03 - { animationGraphManager = a_in; return true; }
		bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) override;                 // 05

		// add
		virtual void Unk_13(void);  // 13
		virtual void Unk_14(void);  // 14

		// members
		std::uint32_t                            pad0C;                  // 0C
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(WeaponAnimationGraphManagerHolder) == 0x18);
}
