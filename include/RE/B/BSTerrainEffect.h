#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTempEffect.h"
#include "RE/I/ID.h"
#include "RE/N/NiQuaternion.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class bhkWorld;
	class NiAVObject;
	struct PositionPlayerEvent;

	class BSTerrainEffect :
		public BSTempEffect,                      // 00
		public BSTEventSink<PositionPlayerEvent>  // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTerrainEffect;
		inline static constexpr auto VTABLE = VTABLE_BSTerrainEffect;
		inline static constexpr auto TYPE = TEMP_EFFECT_TYPE::kTerrain;

		struct BoneAdjustment
		{
		public:
			// members
			NiMatrix3   rotation;  // 00
			NiAVObject* bone;      // 28
			float       zOffset;   // 30
		};
		static_assert(sizeof(BoneAdjustment) == 0x38);

		~BSTerrainEffect() override;  // 00

		// override (BSTempEffect)
		bool                           Update(float a_arg1) override;                // 28
		[[nodiscard]] bool             GetManagerHandlesSaveLoad() const override;   // 2A
		[[nodiscard]] TEMP_EFFECT_TYPE GetType() const override;                     // 2C - { return 0; }
		void                           SaveGame(BGSSaveGameBuffer* a_buf) override;  // 2D
		void                           LoadGame(BGSLoadGameBuffer* a_buf) override;  // 2E

		// add
		virtual bool SetupTerrainEffect(const char* a_modelName, ObjectRefHandle& a_handle, std::uint32_t a_collisionFilter);

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent* a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override;  // 01 - { return BSEventNotifyControl::kContinue; }

		// members;
		NiQuaternion             orientation;         // 38
		NiPoint3                 location;            // 48
		std::uint32_t            pad54;               // 54
		BSTArray<BoneAdjustment> terrainAdjustments;  // 58
		BSTArray<BoneAdjustment> dynamicAdjustments;  // 70
		NiPointer<NiAVObject>    model;               // 88
		BSResource::ID           modelID;             // 90
		ObjectRefHandle          target;              // 9C
		NiPointer<bhkWorld>      physicsWorld;        // A0
		std::uint32_t            collisionFilter;     // A8
		std::uint32_t            padAC;               // AC
		NiPointer<NiAVObject>    followNode;          // B0
	};
	static_assert(sizeof(BSTerrainEffect) == 0xB8);
}
