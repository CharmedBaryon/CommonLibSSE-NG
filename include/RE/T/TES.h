#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTTuple.h"
#include "RE/I/ICellAttachDetachEventSource.h"
#include "RE/M/MaterialIDs.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiSourceTexture.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

namespace RE
{
	namespace BSResource
	{
		struct ArchiveStreamOpenedEvent;
	}

	class BSSystemEvent;
	class BSTempNodeManager;
	class GridCellArray;
	class ImageSpaceModifierInstance;
	class LoadedAreaBound;
	class NavMeshInfoMap;
	class NiAVObject;
	class NiDirectionalLight;
	class NiFogProperty;
	class NiNode;
	class PlayerCharacter;
	class QueuedFile;
	class Sky;
	class TESActorBase;
	class TESLandTexture;
	class TESNPC;
	class TESObjectCELL;
	class TESObjectREFR;
	class TESWorldSpace;

	struct bhkPickData;
	struct PositionPlayerEvent;

	class TES :
		public ICellAttachDetachEventSource,                        // 000
		public BSTEventSink<BSResource::ArchiveStreamOpenedEvent>,  // 060
		public BSTEventSink<PositionPlayerEvent>                    // 068
	{
	public:
		inline static constexpr auto RTTI = RTTI_TES;
		inline static constexpr auto VTABLE = VTABLE_TES;

		class ParticleObjectCache
		{
		public:
			// members
			NiPointer<NiAVObject> model;   // 00
			NiPointer<NiAVObject> clones;  // 08
			ParticleObjectCache*  next;    // 10
		};
		static_assert(sizeof(ParticleObjectCache) == 0x18);

		class SystemEventAdapter : public BSTEventSink<BSSystemEvent>
		{
		public:
			inline static constexpr auto RTTI = RTTI_TES__SystemEventAdapter;
			inline static constexpr auto VTABLE = VTABLE_TES__SystemEventAdapter;

			~SystemEventAdapter() override;  // 00

			// override (BSTEventSink<BSSystemEvent>)
			BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

			// members
			std::uint64_t unk08;  // 08
		};
		STATIC_ASSERT_SIZE(SystemEventAdapter, 0x10);

		~TES() override;  // 00

		// override (BSTEventSink<BSResource::ArchiveStreamOpenedEvent>)
		BSEventNotifyControl ProcessEvent(const BSResource::ArchiveStreamOpenedEvent* a_event, BSTEventSource<BSResource::ArchiveStreamOpenedEvent>* a_eventSource) override;  // 01 - { return BSEventNotifyControl::kContinue; }

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent* a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override;  // 01

		static TES* GetSingleton();

		void ForEachCell(std::function<void(TESObjectCELL*)> a_callback);
		void ForEachCellInRange(TESObjectREFR* a_origin, float a_radius, std::function<void(TESObjectCELL*)> a_callback);
		void ForEachReference(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback);
		void ForEachReferenceInRange(TESObjectREFR* a_origin, float a_radius, std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback);

		void            CancelMasterFileLoads();
		TESObjectCELL*  GetCell(const NiPoint3& a_position) const;
		MATERIAL_ID     GetLandMaterialType(const NiPoint3& a_position) const;
		bool            GetLandHeight(const NiPoint3& a_positionIn, float& a_heightOut);
		TESLandTexture* GetLandTexture(const NiPoint3& a_position) const;
		float           GetWaterHeight(const NiPoint3& a_pos, TESObjectCELL* a_cell) const;
		NiAVObject*     Pick(bhkPickData& a_pickData);
		void            PurgeBufferedCells();
		void            ResumeMasterFileLoads();

		// Core interior/exterior cell-transition engine backing every cell
		// attach/detach (interior enter/exit, coc, worldspace load).
		void SetCurrentCell(TESObjectCELL* a_cell, const NiPoint3& a_position, float a_unk4);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                     \
	std::uint8_t  unk128;              /* 128 */ \
	bool          showLANDborders;     /* 129 */ \
	std::uint8_t  unk12A;              /* 12A */ \
	std::uint8_t  unk12B;              /* 12B */ \
	std::uint8_t  unk12C;              /* 12C */ \
	std::uint8_t  unk12D;              /* 12D */ \
	std::uint8_t  unk12E;              /* 12E */ \
	std::uint8_t  unk12F;              /* 12F */ \
	std::uint16_t unk130;              /* 130 */ \
	std::uint8_t  unk132;              /* 132 */ \
	std::uint8_t  unk133;              /* 133 */ \
	float         gridBufferDistanceX; /* 134 */ \
	float         gridBufferDistanceY; /* 138 */ \
	bool          allowUnusedPurge;    /* 13C */ \
	std::byte     pad13D[3];
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		// 1130 and later
		struct AE_RUNTIME_DATA
		{
#define AE_RUNTIME_DATA_CONTENT                  \
	std::uint32_t unk128;              /* 128 */ \
	std::uint32_t landBorderMode;      /* 12C */ \
	std::uint32_t borderColorAGBR;     /* 130 */ \
	float         gridBufferDistanceX; /* 134 */ \
	float         gridBufferDistanceY; /* 138 */ \
	bool          allowUnusedPurge;    /* 13C */ \
	std::byte     pad13D[3];           /* 13D */ \
	std::uint64_t unk140;              /* 140 - actual offset change is somewhere near showLandBorder */
			AE_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(AE_RUNTIME_DATA) == 0x20);

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                                                                                                                                 \
	TESWorldSpace*                                  worldSpace;                        /* 140 */                                                                              \
	BSSimpleList<BSTTuple<TESNPC*, std::uint16_t>*> deadCount;                         /* 148 */                                                                              \
	QueuedFile*                                     queuedFaceGenAddonHandle;          /* 158 - refcounted; queues facegen addon-node model/texture swaps */                  \
	NiPointer<NiSourceTexture>                      bloodDecalTexture;                 /* 160 - lazily loaded "Effects\\blooddecal.dds" */                                    \
	QueuedFile*                                     queuedFormDataHandle;              /* 168 - refcounted; purpose beyond the handle itself unresolved */                    \
	QueuedFile*                                     queuedBloodSprayWaterSplashHandle; /* 170 - refcounted; registers blood-spray/water-splash NIFs */                        \
	std::uint64_t                                   unk178;                            /* 178 */                                                                              \
	std::uint64_t                                   unk180;                            /* 180 */                                                                              \
	std::uint64_t                                   unk188;                            /* 188 */                                                                              \
	std::uint64_t                                   unk190;                            /* 190 */                                                                              \
	std::uint64_t                                   unk198;                            /* 198 */                                                                              \
	std::uint64_t                                   unk1A0;                            /* 1A0 */                                                                              \
	std::uint64_t                                   unk1A8;                            /* 1A8 */                                                                              \
	std::uint64_t                                   unk1B0;                            /* 1B0 */                                                                              \
	std::uint64_t                                   unk1B8;                            /* 1B8 */                                                                              \
	std::uint64_t                                   unk1C0;                            /* 1C0 */                                                                              \
	std::uint64_t                                   unk1C8;                            /* 1C8 */                                                                              \
	std::uint64_t                                   unk1D0;                            /* 1D0 */                                                                              \
	std::uint64_t                                   unk1D8;                            /* 1D8 */                                                                              \
	std::uint64_t                                   unk1E0;                            /* 1E0 */                                                                              \
	std::uint64_t                                   unk1E8;                            /* 1E8 */                                                                              \
	std::uint64_t                                   unk1F0;                            /* 1F0 */                                                                              \
	std::uint64_t                                   unk1F8;                            /* 1F8 */                                                                              \
	std::uint64_t                                   unk200;                            /* 200 */                                                                              \
	std::uint64_t                                   unk208;                            /* 208 */                                                                              \
	std::uint64_t                                   unk210;                            /* 210 */                                                                              \
	std::uint64_t                                   unk218;                            /* 218 */                                                                              \
	std::uint64_t                                   unk220;                            /* 220 */                                                                              \
	PlayerCharacter*                                playerCharacter;                   /* 228 */                                                                              \
	std::uint64_t                                   unk230;                            /* 230 */                                                                              \
	std::uint64_t                                   unk238;                            /* 238 */                                                                              \
	std::uint64_t                                   unk240;                            /* 240 */                                                                              \
	std::uint64_t                                   unk248;                            /* 248 */                                                                              \
	std::uint64_t                                   unk250;                            /* 250 */                                                                              \
	std::uint64_t                                   unk258;                            /* 258 */                                                                              \
	std::uint64_t                                   unk260;                            /* 260 */                                                                              \
	std::uint64_t                                   unk268;                            /* 268 */                                                                              \
	std::uint64_t                                   unk270;                            /* 270 */                                                                              \
	std::uint64_t                                   unk278;                            /* 278 - ctor zeroes only bytes 27C-283; real sub-object boundary unresolved */        \
	std::uint64_t                                   unk280;                            /* 280 - ctor sets only bytes 284-285 to 0x100; real sub-object boundary unresolved */ \
	ParticleObjectCache*                            particleCacheHead;                 /* 288 - head of a callback-keyed clone/cache linked list */                           \
	SystemEventAdapter                              unk290;                            /* 290 */                                                                              \
	std::uint64_t                                   placeableWaterCount;               /* 2A0 - ctor zeroes only the low 4 bytes; may be two 4-byte sub-fields */             \
	NavMeshInfoMap*                                 navMeshInfoMap;                    /* 2A8 - lazily constructed on first access */                                         \
	NiPointer<LoadedAreaBound>                      loadedAreaBound;                   /* 2B0 - refcounted */
            RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x178);

		[[nodiscard]] inline RUNTIME_DATA* GetRuntimeData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_1130) != std::strong_ordering::less) {
					return nullptr;
				}
			}
			return REL::RelocateMember<RUNTIME_DATA*>(this, 0x128, 0x128);
		}

		[[nodiscard]] inline const RUNTIME_DATA* GetRuntimeData() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_1130) != std::strong_ordering::less) {
					return nullptr;
				}
			}
			return REL::RelocateMember<RUNTIME_DATA*>(this, 0x128, 0x128);
		}

		AE_ONLY_POINTER_ACCESSOR_VERSIONED(AE_RUNTIME_DATA, GetAERuntimeData, SKSE::RUNTIME_SSE_1_6_1130, 0x120);

		RUNTIME_DATA_ACCESSOR_VERSIONED_EX(RUNTIME_DATA2, GetRuntimeData2, SKSE::RUNTIME_SSE_1_6_1130, 0x140, 0x148);
		// members
		std::uint64_t                                       unk070;                     // 070
		GridCellArray*                                      gridCells;                  // 078
		NiNode*                                             objRoot;                    // 080
		NiNode*                                             lodLandRoot;                // 088
		NiNode*                                             objLODWaterRoot;            // 090
		BSTempNodeManager*                                  tempNodeManager;            // 098
		NiDirectionalLight*                                 objLight;                   // 0A0
		NiFogProperty*                                      objFog;                     // 0A8
		std::int32_t                                        currentGridX;               // 0B0
		std::int32_t                                        currentGridY;               // 0B4
		std::int32_t                                        currentQueuedX;             // 0B8
		std::int32_t                                        currentQueuedY;             // 0BC
		TESObjectCELL*                                      interiorCell;               // 0C0
		TESObjectCELL**                                     interiorBuffer;             // 0C8
		TESObjectCELL**                                     exteriorBuffer;             // 0D0
		std::uint64_t                                       unk0D8;                     // 0D8
		std::int32_t                                        saveGridX;                  // 0E0
		std::int32_t                                        saveGridY;                  // 0E4
		std::uint64_t                                       unk0E8;                     // 0E8
		std::uint64_t                                       unk0F0;                     // 0F0
		std::uint64_t                                       unk0F8;                     // 0F8
		Sky*                                                sky;                        // 100
		BSSimpleList<NiPointer<ImageSpaceModifierInstance>> activeImageSpaceModifiers;  // 108
		std::uint64_t                                       unk118;                     // 118
		std::uint64_t                                       unk120;                     // 120
#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT;   // 128
		RUNTIME_DATA2_CONTENT;  // 140
#elif !defined(ENABLE_SKYRIM_VR) && !defined(ENABLE_SKYRIM_SE)
		AE_RUNTIME_DATA_CONTENT;  // 128
		RUNTIME_DATA2_CONTENT;    // 148
#endif
	};
	STATIC_ASSERT_SIZE(TES, 0x2B8, 0x2C0, 0x2B8, 0x128, 0x128);
}
#undef RUNTIME_DATA_CONTENT
#undef AE_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
