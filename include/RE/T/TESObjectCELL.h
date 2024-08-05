#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSBitField.h"
#include "RE/B/BSContainer.h"
#include "RE/B/BSMultiBoundNode.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/C/Color.h"
#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTypes.h"
#include "RE/I/InteriorData.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTMap.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESObjectREFR.h"
#include "SKSE/Version.h"

namespace RE
{
	class TESRegionList;

	namespace BGSWaterCollisionManager
	{
		class BGSWaterUpdateI;
	}

	class BSTempEffectParticle;
	class bhkWorld;
	class BSPortalGraph;
	class NavMesh;
	class NiNode;

	class BGSTerrainVisibilityData
	{
	public:
		// members
		BSBitField<>* visData;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSTerrainVisibilityData) == 0x8);

	struct EXTERIOR_DATA  // XCLC
	{
	public:
		enum class LandHideFlag
		{
			kNone = 0,
			kQuad1 = 1 << 0,
			kQuad2 = 1 << 1,
			kQuad3 = 1 << 2,
			kQuad4 = 1 << 3
		};

		// members
		std::int32_t                                 cellX;          // 00
		std::int32_t                                 cellY;          // 04
		char*                                        maxHeightData;  // 08
		BGSTerrainVisibilityData*                    lodVisData;     // 10
		float                                        worldX;         // 18
		float                                        worldY;         // 1C
		stl::enumeration<LandHideFlag, std::uint8_t> landHideFlags;  // 20
		std::uint8_t                                 pad21;          // 21
		std::uint16_t                                pad22;          // 22
		std::uint32_t                                pad24;          // 24
	};
	static_assert(sizeof(EXTERIOR_DATA) == 0x28);

	class NavMeshArray
	{
	public:
		// members
		BSTArray<BSTSmartPointer<NavMesh>> navMeshes;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NavMeshArray) == 0x18);

	struct LOADED_CELL_DATA
	{
	public:
		// members
		NiPointer<BSPortalGraph>                             portalGraph;             // 000 - smart ptr
		NiPointer<NiNode>                                    cell3D;                  // 008
		void*                                                unk010;                  // 010 - smart ptr
		void*                                                unk018;                  // 018 - smart ptr
		void*                                                unk020;                  // 020 - smart ptr
		std::uint64_t                                        unk028;                  // 028
		std::uint64_t                                        unk030;                  // 030
		std::uint64_t                                        unk038;                  // 038
		BSTArray<ObjectRefHandle>                            unk040;                  // 040
		BSTArray<ObjectRefHandle>                            flickeringLights;        // 058
		NiTMap<TESForm*, ObjectRefHandle>                    emittanceSourceRefMap;   // 070
		NiTMap<ObjectRefHandle, NiNode*>                     emittanceLightRefMap;    // 090
		NiTMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap;        // 0B0
		NiTMap<BSMultiBoundNode*, ObjectRefHandle>           refMultiboundMap;        // 0D0
		BSSimpleList<ObjectRefHandle>                        activatingRefs;          // 0F0
		BSSimpleList<ObjectRefHandle>                        unk100;                  // 100
		std::uint64_t                                        unk110;                  // 110
		BSTArray<void*>                                      unk118;                  // 118
		BSTArray<ObjectRefHandle>                            decalRefs;               // 130
		BSTArray<ObjectRefHandle>                            skyActors;               // 148
		BGSEncounterZone*                                    encounterZone;           // 160
		bool                                                 decalsQueued;            // 168
		volatile mutable std::int32_t                        criticalQueuedRefCount;  // 16C
		volatile mutable std::int32_t                        queuedRefCount;          // 170
		volatile mutable std::int32_t                        queuedDistantRefCount;   // 174
		std::int32_t                                         unk178;                  // 178
		bool                                                 refsFullyLoaded;         // 17C
	};
	static_assert(sizeof(LOADED_CELL_DATA) == 0x180);

	class TESObjectCELL :
		public TESForm,     // 000
		public TESFullName  // 020
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectCELL;
		inline static constexpr auto VTABLE = VTABLE_TESObjectCELL;
		inline static constexpr auto FORMTYPE = FormType::Cell;

		enum class Flag  // DATA
		{
			kNone = 0,
			kIsInteriorCell = 1 << 0,
			kHasWater = 1 << 1,
			kCanTravelFromHere = 1 << 2,
			kNoLODWater = 1 << 3,
			kHasTempData = 1 << 4,
			kPublicArea = 1 << 5,
			kHandChanged = 1 << 6,
			kShowSky = 1 << 7,
			kUseSkyLighting = 1 << 8,
			kWarnToLeave = 1 << 9
		};

		enum class CellState
		{
			kAttached = 7
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kFlags = 1 << 1,
				kFullName = 1 << 2,
				kOwnership = 1 << 3,
				kExteriorShort = 1 << 28,
				kExteriorChar = 1 << 29,
				kDetachTime = 1 << 30,
				kSeendData = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kPersistent = 1 << 10,
				kIgnored = 1 << 12,
				kOffLimits = 1 << 17,
				kCompressed = 1 << 18,
				kCantWait = 1 << 19
			};
		};

		union CellData
		{
			EXTERIOR_DATA* exterior;  // XCLC
			INTERIOR_DATA* interior;  // XCLL
		};
		static_assert(sizeof(CellData) == 0x8);

		~TESObjectCELL() override;  // 00

		// override (TESForm)
		void               ClearData() override;                                                                 // 05
		bool               Load(TESFile* a_mod) override;                                                        // 06
		TESForm*           CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;                    // 09 - { return 0; }
		bool               FindInFileFast(TESFile* a_mod) override;                                              // 0C
		void               SaveGame(BGSSaveFormBuffer* a_buf) override;                                          // 0E
		void               LoadGame(BGSLoadFormBuffer* a_buf) override;                                          // 0F
		void               Revert(BGSLoadFormBuffer* a_buf) override;                                            // 12
		void               InitItemImpl() override;                                                              // 13
		void               GetFormDetailedString(char* a_buf, std::uint32_t a_bufLen) override;                  // 16
		void               SetAltered(bool a_set) override;                                                      // 24
		bool               BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;  // 30
		void               CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;                          // 31
		const char*        GetFormEditorID() const override;                                                     // 32
		bool               SetFormEditorID(const char* a_str) override;                                          // 33
		[[nodiscard]] bool IsParentForm() override;                                                              // 34 - { return true; }
		[[nodiscard]] bool IsFormTypeChild(FormType a_type) override;                                            // 36

		TESNPC*                      GetActorOwner();
		bhkWorld*                    GetbhkWorld() const;
		void                         ForEachReference(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const;
		void                         ForEachReferenceInRange(const NiPoint3& a_origin, float a_radius, std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const;
		[[nodiscard]] EXTERIOR_DATA* GetCoordinates();
		[[nodiscard]] TESFaction*    GetFactionOwner();
		[[nodiscard]] INTERIOR_DATA* GetLighting();
		[[nodiscard]] BGSLocation*   GetLocation() const;
		[[nodiscard]] float          GetNorthRotation();
		[[nodiscard]] TESForm*       GetOwner();
		[[nodiscard]] float          GetExteriorWaterHeight() const;
		[[nodiscard]] TESRegionList* GetRegionList(bool a_createIfMissing);
		bool                         GetWaterHeight(const NiPoint3& a_pos, float& a_waterHeight);
		[[nodiscard]] bool           IsAttached() const;
		[[nodiscard]] bool           IsExteriorCell() const;
		[[nodiscard]] bool           IsInteriorCell() const;
		void                         SetActorOwner(TESNPC* a_owner);
		void                         SetFactionOwner(TESFaction* a_owner);
		void                         SetFogColor(Color a_near, Color a_far);
		void                         SetFogPlanes(float a_near, float a_far);
		void                         SetFogPower(float a_power);
		void                         SetHandChanged(bool a_changed);
		void                         SetOwner(TESForm* a_owner);
		void                         SetPublic(bool a_public);
		[[nodiscard]] bool           UsesSkyLighting() const;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                   \
	CellData                                             cellData;         /* 060, 068 - XCLL if interior, XCLC if exterior */ \
	TESObjectLAND*                                       cellLand;         /* 068, 070 */                                      \
	float                                                waterHeight;      /* 070, 078 - XCLW */                               \
	NavMeshArray*                                        navMeshes;        /* 078, 080 */                                      \
	BSTSet<NiPointer<TESObjectREFR>>                     references;       /* 080, 088 */                                      \
	TESForm*                                             unk0B0;           /* 0B0, 0B8 - REFR owner of cell? */                \
	BSTArray<TESObjectREFR*>                             objectList;       /* 0B8, 0C0 - persistent */                         \
	BSTArray<void*>                                      unk0D0;           /* 0D0, 0D8 */                                      \
	BSTArray<BGSWaterCollisionManager::BGSWaterUpdateI*> waterObjects;     /* 0E8, 0F0 */                                      \
	BSTArray<void*>                                      unk100;           /* 100, 108 */                                      \
	mutable BSSpinLock                                   spinLock;         /* 118, 120 */                                      \
	TESWorldSpace*                                       worldSpace;       /* 120, 128 */                                      \
	LOADED_CELL_DATA*                                    loadedData;       /* 128, 130 */                                      \
	BGSLightingTemplate*                                 lightingTemplate; /* 130, 138 - LTMP */                               \
	std::uint64_t                                        unk138;           /* 138, 140 */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x60, 0x68);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x60, 0x68);
		}

		// members
		mutable BSSpinLock                        grassCreateLock;  // 030
		mutable BSSpinLock                        grassTaskLock;    // 038
		stl::enumeration<Flag, std::uint16_t>     cellFlags;        // 040
		std::uint16_t                             cellGameFlags;    // 042
		stl::enumeration<CellState, std::uint8_t> cellState;        // 044
		bool                                      autoWaterLoaded;  // 045
		bool                                      cellDetached;     // 046
		std::uint8_t                              pad047;           // 047
		ExtraDataList                             extraList;        // 048

#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(TESObjectCELL) == 0x140);
#endif
}
#undef RUNTIME_DATA_CONTENT
