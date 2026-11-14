#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/D/DelayFunctor.h"

namespace RE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	class TESBoundObject;

	namespace SkyrimScript
	{
		class AttachAshPileFunctor : public DelayFunctor
		{
		public:
			inline static constexpr auto RTTI = RTTI_SkyrimScript____AttachAshPileFunctor;
			inline static constexpr auto VTABLE = VTABLE_SkyrimScript____AttachAshPileFunctor;

			~AttachAshPileFunctor() override;  // 00

			// override (DelayFunctor)
			RE::BSScript::Variable operator()() override;                                                              // 01
			bool                   IsLatent() const override;                                                          // 02 - { return false; }
			bool                   SaveImpl(BSStorage& a_storage) const override;                                      // 04
			FunctorType            GetType() const override;                                                           // 05 - { return 14; }
			bool                   LoadImpl(const BSStorage& a_storage, std::uint32_t a_arg2, bool& a_arg3) override;  // 06

			// members
			ActorHandle                                targetActor;  // 10
			std::uint32_t                              pad14;        // 14
			TESBoundObject*                            ashObject;    // 18
			BSTSmartPointer<BSScript::IVirtualMachine> vm;           // 20
		};
		static_assert(sizeof(AttachAshPileFunctor) == 0x28);
	}
}
