#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTLocklessQueue.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiAccumulator.h"
#include "RE/N/NiCamera.h"
#include "RE/N/NiCullingProcess.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiVisibleArray.h"

namespace RE
{
	class BSCompoundFrustum;
	class BSCullingProcess;
	class BSMultiBound;
	class BSOcclusionPlane;
	class BSPortalGraphEntry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiBound;
	class NiFrustumPlanes;

	struct CullJobDescriptor
	{
		NiPointer<BSShaderAccumulator>   shaderAccumulator;           // 00
		NiPointer<BSShaderAccumulator>   shaderAccumulatorSecondary;  // 08
		NiPointer<NiCamera>              camera;                      // 10
		BSCompoundFrustum*               compoundFrustum;             // 18
		NiFrustum*                       frustum;                     // 20
		BSPortalGraphEntry*              portalGraphEntry;            // 28
		BSCullingProcess*                cullingProcess;              // 30
		NiFrustumPlanes*                 customCullPlanes;            // 38
		NiAVObject*                      scene;                       // 40
		BSTArray<NiPointer<NiAVObject>>* cullingObjects;              // 48
		uint32_t                         cullMode;                    // 50
		float                            lightRadius;                 // 54
		uint32_t                         unk58;                       // 58
		bool                             isParabolic;                 // 5C
		bool                             isDirectionalLight;          // 5D
		bool                             ignorePreprocess;            // 5E
		bool                             doCustomCullPlanes;          // 5F
		bool                             cameraRelatedUpdates;        // 60
		bool                             unk61;                       // 61
		bool                             updateAccumulateFlag;        // 62
	};
	static_assert(sizeof(CullJobDescriptor) == 0x68);

	class BSCullingProcess : public NiCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSCullingProcess;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSCullingProcess;
		inline static constexpr auto VTABLE = VTABLE_BSCullingProcess;

		enum class BSCPCullingType
		{
			kNormal = 0,
			kAllPass = 1,
			kAllFail = 2,
			kIgnoreMultiBounds = 3,
			kForceMultiBoundsNoUpdate = 4
		};

		struct Data
		{
		public:
			// members
			BSGeometry*  geometry;              // 00
			std::int32_t alphaGroupStartIndex;  // 08
			std::int32_t alphaGroupStopIndex;   // 0C
		};
		static_assert(sizeof(Data) == 0x10);

		struct CullingContext
		{
			CullingContext();

			NiPointer<NiAccumulator>   accumulator;           // 00
			NiPointer<NiRefObject>     unk08;                 // 08
			NiPointer<NiCamera>        camera;                // 10
			BSCompoundFrustum*         compoundFrustum;       // 18
			const NiFrustum*           frustum;               // 20
			BSPortalGraphEntry*        portalGraphEntry;      // 28
			NiCullingProcess*          cullingProcess;        // 30
			const NiFrustumPlanes*     customCullPlanes;      // 38
			NiPointer<NiAVObject>      scene;                 // 40
			NiVisibleArray*            visibleSet;            // 48
			REX::Enum<BSCPCullingType> cullMode;              // 50
			float                      unk54;                 // 54
			std::uint32_t              unk58;                 // 58
			bool                       useParabolicCulling;   // 5C
			std::uint8_t               unk5D;                 // 5D
			bool                       ignorePreprocess;      // 5E
			bool                       doCustomCullPlanes;    // 5F
			bool                       cameraRelatedUpdates;  // 60
			bool                       unk61;                 // 61
			bool                       updateAccumulateFlag;  // 62
			std::uint8_t               pad63[0x5];            // 63
		};
		static_assert(sizeof(CullingContext) == 0x68);

		// override (NiCullingProcess)
		const NiRTTI* GetRTTI() const override;  // 00

		~BSCullingProcess() override;  // 15

		void Process1(NiAVObject* a_object, std::int32_t a_alphaGroupIndex) override;                         // 16
		void Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet) override;  // 17
		void AppendVirtual(BSGeometry& a_visible, std::int32_t a_alphaGroupIndex) override;                   // 18

		// add
		virtual void               AppendNonAccum(NiAVObject& a_object, std::int32_t a_alphaGroupIndex);  // 19
		virtual bool               TestBaseVisibility1(BSMultiBound& a_bound);                            // 1A
		virtual bool               TestBaseVisibility2(BSOcclusionPlane& a_bound);                        // 1B
		[[nodiscard]] virtual bool TestBaseVisibility3(const NiBound& a_bound);                           // 1C

		bool        AddShared(NiAVObject* a_object);
		static void Process(CullingContext& a_context);

		BSTArray<NiPointer<NiAVObject>>                                          objectArray;          // 00128
		BSTLocklessQueue::ObjMultiProdCons<Data, 4096, 0>                        cullQueue;            // 00140
		BSTHashMap<NiAVObject*, bool>                                            roomSharedMap;        // 30160
		BSPortalGraphEntry*                                                      portalGraphEntry;     // 30190
		REX::Enum<BSCPCullingType>                                               cullMode;             // 30198
		BSCompoundFrustum*                                                       compoundFrustum;      // 301A0
		REX::Enum<BSCPCullingType>                                               cullModeStack[10];    // 301A8
		std::uint32_t                                                            cullModeStackIndex;   // 301D0
		bool                                                                     recurseToGeometry;    // 301D4
		bool                                                                     isGroupingAlphas;     // 301D5
		std::uint16_t                                                            unk301D6;             // 301D6
		BSTArray<BSTObjectArena<RE::BSGeometry*, BSTObjectArenaScrapAlloc, 32>*> alphaGroups;          // 301D8
		std::int32_t                                                             alphaGroupIndex;      // 301F0
		std::uint32_t                                                            alphaGroupStopIndex;  // 301F4
	};
	static_assert(sizeof(BSCullingProcess) == 0x301F8);
}
