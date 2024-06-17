#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTempEffect.h"
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
		inline static constexpr auto TYPE = TEMP_EFFECT_TYPE::kTerrain;

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
		NiQuaternion          orientation;      // 38
		NiPoint3              location;         // 48
		std::uint32_t         unk54;            // 54
		BSTArray<void*>       unk58;            // 58
		BSTArray<void*>       unk70;            // 70
		NiPointer<NiAVObject> effectModel;      // 88
		NiPoint3              unk90;            // 90
		ObjectRefHandle       unk9C;            // 9C
		NiPointer<bhkWorld>   physicsWorld;     // A0
		std::uint32_t         collisionFilter;  // A8
		std::uint32_t         unkAC;            // AC
		NiPointer<NiAVObject> followNode;       // B0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSTerrainEffect) == 0xB8);
}
