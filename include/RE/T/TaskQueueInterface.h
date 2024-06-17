#pragma once

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class NiAVObject;
	class NiNode;
	class NiPoint3;
	class SpellItem;
	class TESObjectREFR;
	class TESWeather;

	class TaskQueueInterface
	{
	public:
		static TaskQueueInterface* GetSingleton();

		static bool ShouldUseTaskQueue();

		void QueueNodeAttach(NiAVObject* a_obj, NiNode* a_root, bool a_arg3 = true, bool a_arg4 = false);                // 04
		void QueueNodeDetach(NiAVObject* a_obj);                                                                         // 05
		void QueueUpdateDestructibleObject(TESObjectREFR* a_refr, float a_damage, bool a_arg3, TESObjectREFR* a_cause);  // 09
		void QueueAddRipple(float a_scale, const NiPoint3& a_pos);                                                       // 45
		void QueueForceWeather(TESWeather* a_weather, bool a_forceOverride);                                             // 64
		void QueueActorDisarm(ActorHandle& a_target, ActorHandle& a_caster);                                             // 91
		void QueueRemoveSpell(ActorHandle& a_actor, SpellItem* a_spellItem);                                             // 93
	private:
		KEEP_FOR_RE()
	};
	//static_assert(sizeof(TaskQueueInterface) == 0x);
}
