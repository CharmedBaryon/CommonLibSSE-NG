#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSGeometry.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTPointerList.h"
#include "RE/N/NiTPointerMap.h"

namespace RE
{
	class BSMultiBoundAABB;
	class BSMultiBoundNode;
	class NiAVObject;
	class NiNode;
	class TESObjectCELL;
	class TESWorldSpace;
	class TESWaterDisplacement;
	class TESWaterForm;
	class TESWaterNormals;
	class TESWaterObject;
	class TESWaterReflections;
	class WadingWaterData;

	class TESWaterSystem : public BSTSingletonSDM<TESWaterSystem>
	{
	public:
		static TESWaterSystem* GetSingleton();

		void AddRipple(const NiPoint3& a_pos, float a_scale);
		void AddLODWater(NiAVObject* a_LODWater, TESWorldSpace* a_worldSpace, NiNode* a_waterLODRoot, BSMultiBoundNode* a_bound, bool a_enableLODWaterHeight);
		void AddWater(NiAVObject* a_waterObj, TESWaterForm* a_waterType, float a_waterHeight, const BSTArray<NiPointer<BSMultiBoundAABB>>* a_multiBoundShape, bool a_noDisplacement, bool a_isProcedural);
		void Enable();
		void RemoveLODWater(NiAVObject* a_LODWater, NiNode* a_waterLODRoot);
		bool RemoveWater(NiAVObject* a_waterObj);

		// members
		std::uint32_t                                pad000;                          // 000
		BSFixedString*                               type;                            // 008
		std::uint32_t                                unk010;                          // 010
		std::uint32_t                                pad014;                          // 014
		float                                        unk018;                          // 018
		float                                        unk01C;                          // 01C
		BSTArray<NiPointer<TESWaterObject>>          waterObjects;                    // 020
		BSTArray<NiPointer<TESWaterReflections>>     waterReflections;                // 038
		BSTArray<NiPointer<TESWaterDisplacement>>    waterDisplacement;               // 050
		BSTArray<NiPointer<TESWaterNormals>>         waterNormals;                    // 068
		std::uint32_t                                unk080;                          // 080
		NiPoint2                                     lastDisplaceOffset;              // 084
		std::uint32_t                                pad08C;                          // 08C
		NiPointer<NiNode>                            waterRoot;                       // 090
		TESWaterForm*                                currentWaterType;                // 098
		std::uint32_t                                reflectionExteriorCount;         // 0A0
		std::uint32_t                                reflectionInteriorCount;         // 0A4
		TESWorldSpace*                               worldSpace;                      // 0A8
		bool                                         enabled;                         // 0B0
		std::uint8_t                                 pad0B1;                          // 0B1
		std::uint16_t                                pad0B2;                          // 0B2
		std::uint32_t                                unk0B4;                          // 0B4
		bool                                         playerUnderwater;                // 0B8
		bool                                         partiallyUnderwater;             // 0B9
		bool                                         unk0BA;                          // 0BA
		std::uint8_t                                 pad0BB;                          // 0BB
		std::uint32_t                                lastUpdateFrame;                 // 0BC
		float                                        underwaterHeight;                // 0C0
		bool                                         waterRadiusState;                // 0C4
		std::uint8_t                                 pad0C5;                          // 0C5
		std::uint8_t                                 unk0C6;                          // 0C6
		bool                                         showProcedualWater;              // 0C7
		std::uint8_t                                 unk0C8;                          // 0C8
		std::uint8_t                                 padC9;                           // 0C9
		std::uint16_t                                padCA;                           // 0CA
		std::int32_t                                 maxActorDisplacement;            // 0CC
		std::int32_t                                 activeWaterGroups;               // 0D0
		float                                        timeSinceLastRipplePlaced;       // 0D4
		NiTPointerMap<ActorHandle, WadingWaterData*> wadingWaterData;                 // 0D8
		NiTPointerList<ActorHandle>                  actorsInWater;                   // 0F8
		bool                                         skipNextUpdate;                  // 110
		std::uint8_t                                 pad111;                          // 111
		std::uint16_t                                pad112;                          // 112
		std::uint32_t                                pad114;                          // 114
		TESObjectCELL*                               lastWaterCell;                   // 118
		mutable BSSpinLock                           lock;                            // 120
		NiPointer<NiAVObject>                        defaultDisplacementWaterObject;  // 128
	};
	static_assert(sizeof(TESWaterSystem) == 0x130);
};
