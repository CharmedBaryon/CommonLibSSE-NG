#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectREFR;
	class BGSImpactDataSet;
	struct BGSFootstepEvent;
	struct BGSCombatImpactEvent;
	struct BGSCollisionSoundEvent;
	struct BSSoundHandle;

	class BGSImpactManager :
		public BSTEventSink<BGSFootstepEvent>,        // 00
		public BSTEventSink<BGSCombatImpactEvent>,    // 08
		public BSTEventSink<BGSCollisionSoundEvent>,  // 10
		public BSTSingletonSDM<BGSImpactManager>      // 18
	{
	public:
		struct ImpactSoundData
		{
		public:
			// members
			BGSImpactData* impactData;      // 00
			NiPoint3*      position;        // 08
			NiAVObject*    objectToFollow;  // 10
			BSSoundHandle* sound1;          // 18
			BSSoundHandle* sound2;          // 20
			bool           playSound1;      // 28
			bool           playSound2;      // 29
			bool           unk2A;           // 2A
			void*          unk30;           // 30
		};
		static_assert(sizeof(ImpactSoundData) == 0x38);

		// override (BSTEventSink<BGSFootstepEvent>)
		BSEventNotifyControl ProcessEvent(const BGSFootstepEvent* a_event, BSTEventSource<BGSFootstepEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BGSCombatImpactEvent>)
		BSEventNotifyControl ProcessEvent(const BGSCombatImpactEvent* a_event, BSTEventSource<BGSCombatImpactEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BGSCollisionSoundEvent>)
		BSEventNotifyControl ProcessEvent(const BGSCollisionSoundEvent* a_event, BSTEventSource<BGSCollisionSoundEvent>* a_eventSource) override;  // 01

		static BGSImpactManager* GetSingleton()
		{
			REL::Relocation<BGSImpactManager**> singleton{ RELOCATION_ID(515123, 401262) };
			return *singleton;
		}

		bool PlayImpactEffect(TESObjectREFR* a_ref, BGSImpactDataSet* a_impactEffect, const BSFixedString& a_nodeName, NiPoint3& a_pickDirection, float a_pickLength, bool a_applyNodeRotation, bool a_useNodeLocalRotation)
		{
			using func_t = decltype(&BGSImpactManager::PlayImpactEffect);
			static REL::Relocation<func_t> func{ RELOCATION_ID(35320, 36215) };
			return func(this, a_ref, a_impactEffect, a_nodeName, a_pickDirection, a_pickLength, a_applyNodeRotation, a_useNodeLocalRotation);
		}
		bool PlayImpactDataSounds(ImpactSoundData& a_impactSoundData)
		{
			using func_t = decltype(&BGSImpactManager::PlayImpactDataSounds);
			static REL::Relocation<func_t> func{ RELOCATION_ID(35317, 36212) };
			return func(this, a_impactSoundData);
		}

	private:
		KEEP_FOR_RE()
	};
}
