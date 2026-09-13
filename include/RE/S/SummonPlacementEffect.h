#pragma once

#include "RE/B/BGSLoadGameSubBuffer.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/R/ReferenceEffect.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	class BGSArtObject;
	class BGSArtObjectCloneTask;
	class NiAVObject;
	struct BSAnimationGraphEvent;

	class SummonPlacementEffect :
		public ReferenceEffect,                     // 00
		public SimpleAnimationGraphManagerHolder,   // 48
		public BSTEventSink<BSAnimationGraphEvent>  // 60
	{
	public:
		inline static constexpr auto RTTI = RTTI_SummonPlacementEffect;
		inline static constexpr auto Ni_RTTI = NiRTTI_SummonPlacementEffect;
		inline static constexpr auto VTABLE = VTABLE_SummonPlacementEffect;
		inline static constexpr auto TYPE = TEMP_EFFECT_TYPE::kMagicSummon;

		~SummonPlacementEffect() override;  // 00

		// override (ReferenceEffect)
		const NiRTTI*    GetRTTI() const override;                           // 02
		bool             Update(float a_arg1) override;                      // 28
		TEMP_EFFECT_TYPE GetType() const override;                           // 2C - { return kMagicSummon; }
		void             SaveGame(BGSSaveGameBuffer* a_buf) override;        // 2D
		void             LoadGame(BGSLoadGameBuffer* a_buf) override;        // 2E
		void             FinishLoadGame(BGSLoadGameBuffer* a_buf) override;  // 2F
		void             Init() override;                                    // 36

		// override (SimpleAnimationGraphManagerHolder)
		bool SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) override;  // 08

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01

		// members
		BGSArtObject*                          artObject;            // 68
		NiPoint3                               location;             // 70
		std::uint32_t                          pad7C;                // 7C
		NiPointer<NiAVObject>                  artObject3D;          // 80
		BGSLoadGameSubBuffer                   loadedDataSubBuffer;  // 88
		BSTSmartPointer<BGSArtObjectCloneTask> cloneTask;            // 90
		bool                                   animationComplete;    // 98
	};
	static_assert(sizeof(SummonPlacementEffect) == 0xA0);
}
