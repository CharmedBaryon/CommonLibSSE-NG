#pragma once

#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;
	class CombatTargetLocationSearchResult;

	class CombatTargetLocationSearch : public CombatObject
	{
	public:
		CombatTargetLocationSearch(Actor* actor, Actor* target, float R);

		CombatTargetLocationSearchResult* result;
		BSTArray<uint32_t>                array1;
		BSTArray<void*>                   array2;  // TODO: rest
		ActorHandle                       actor;
		ActorHandle                       target;
		FormID                            target_formid;
		NiPoint3                          P;
		float                             r;
		float                             me_r;
		uint32_t                          field_68;
		uint32_t                          field_6C;
		void*                             lock;
	};
	static_assert(sizeof(CombatTargetLocationSearch) == 0x78);
}
