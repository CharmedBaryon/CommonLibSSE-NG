#pragma once

#include "RE/B/BSFadeNodeCuller.h"
#include "RE/M/MobIterOperator.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundNode;
	class BSMultiBound;
	class BSMultiBoundSphere;

	class HighActorCuller : public MobIterOperator
	{
	public:
		inline static constexpr auto RTTI = RTTI_HighActorCuller;
		inline static constexpr auto VTABLE = VTABLE_HighActorCuller;

		~HighActorCuller() override;  // 00

		// override (MobIterOperator)
		void Operate(Actor* a_actor) override;  // 01

		static HighActorCuller* GetSingleton()
		{
			static REL::Relocation<HighActorCuller**> singleton{ RELOCATION_ID(517032, 403540) };
			return *singleton;
		}

		// members
		BSFadeNodeCuller              culler;            // 010
		NiPointer<BSMultiBoundNode>   multiBoundNode;    // 138
		NiPointer<BSMultiBound>       multiBound;        // 140
		NiPointer<BSMultiBoundSphere> multiBoundSphere;  // 148
	};
	static_assert(sizeof(HighActorCuller) == 0x150);
}
