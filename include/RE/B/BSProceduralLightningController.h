#pragma once

#include "RE/B/BSDynamicTriShape.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSProceduralGeomEvent.h"
#include "RE/B/BSProceduralLightningTasklet.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTaskletGroup.h"
#include "RE/N/NiInterpController.h"
#include "RE/N/NiInterpolator.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSProceduralLightningController :
		public NiInterpController,                    // 00
		public BSTEventSource<BSProceduralGeomEvent>  // 48
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSProceduralLightningController;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSProceduralLightningController;
		inline static constexpr auto VTABLE = VTABLE_BSProceduralLightningController;

		~BSProceduralLightningController() override { Dtor(); }  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// override (NiTimeController)
		void Update(float a_time) override;          // 27
		bool TargetIsRequiredType() const override;  // 2E

		// override (NiInterpController)
		std::uint16_t        GetInterpolatorCount() const override;                                                                                                                                                                   // 2F
		const char*          GetInterpolatorID(std::uint16_t a_index = 0) override;                                                                                                                                                   // 30
		std::uint16_t        GetInterpolatorIndex(const char* a_id) const override;                                                                                                                                                   // 31
		std::uint16_t        GetInterpolatorIndexFx(const BSFixedString& a_id) const override;                                                                                                                                        // 32
		NiInterpolator*      GetInterpolator(std::uint16_t a_index = 0) const override;                                                                                                                                               // 33
		void                 SetInterpolator(NiInterpolator* a_interpolator, std::uint16_t a_index = 0) override;                                                                                                                     // 34
		const char*          GetCtlrID() override;                                                                                                                                                                                    // 36
		NiInterpolator*      CreatePoseInterpolator(std::uint16_t a_index) override;                                                                                                                                                  // 37
		void                 SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index = 0) override;                                                                                                               // 38
		NiBlendInterpolator* CreateBlendInterpolator(std::uint16_t a_index = 0, bool a_managerControlled = false, bool a_accumulateAnimations = false, float a_weightThreshold = 0.0f, std::uint8_t a_arraySize = 2) const override;  // 39
		void                 GuaranteeTimeRange(float a_startTime, float a_endTime) override;                                                                                                                                         // 3A
		bool                 InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const override;                                                                                                         // 3B

		// geometry/cachedBounds are unshifted in VR; VR inserts extra fields
		// right after cachedBounds, so interpolators onward shifts.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                   \
	std::uint8_t                  padE4[0x24];             /* E4 - unidentified */                                             \
	NiPointer<NiInterpolator>     interpolators[9];        /* 108 - matches GetInterpolatorIndex's 9-entry table */            \
	std::uint8_t                  pad150[0x18];            /* 150 - unidentified */                                            \
	float                         duration;                /* 168 */                                                           \
	float                         progress;                /* 16C - duration / (a per-frame helper's return value) */          \
	std::uint8_t                  pad170[2];               /* 170 */                                                           \
	bool                          needsRegeneration;       /* 172 - gates full branch-mesh regen in the mesh builder */        \
	bool                          regenerationSkipped;     /* 173 - 0 after a fresh regen, 1 on the fallback path */           \
	std::uint8_t                  pad174[4];               /* 174 */                                                           \
	BSTaskletGroup                taskGroupHandle;         /* 178 */                                                           \
	BSProceduralLightningTasklet* tasklet;                 /* 180 - refcounted internally; not an NiObject, so no NiPointer */ \
	bool                          interpolator0EventCache; /* 188 - last-frame cached event query from interpolators[0] */     \
	bool                          interpolator1EventCache; /* 189 - last-frame cached event query from interpolators[1] */     \
	std::uint8_t                  pad18A[6];               /* 18A */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xB0);

		// Compared via BSProceduralGeometry::Lightning::operator== in IsEqual and
		// serialized as a pair in SaveBinary/LoadBinary; 4th field unconfirmed.
		struct Lightning
		{
			std::uint16_t a;     // 0 - compared/serialized
			std::uint16_t b;     // 2 - compared/serialized
			std::uint16_t c;     // 4 - compared/serialized
			std::uint16_t pad6;  // 6 - unconfirmed; observed 8-byte stride between instances
		};
		static_assert(sizeof(Lightning) == 0x8);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                            \
	float                         prevBounds[3];           /* E4 - not yet identified */                                   \
	float                         extents[3];              /* F0 - not yet identified */                                   \
	std::uint8_t                  padFC[0x1C];             /* FC - unidentified */                                         \
	NiPointer<NiObject>           unk118;                  /* 118 - refcounted; not yet identified beyond NiObject */      \
	NiPointer<NiInterpolator>     interpolators[9];        /* 120 - matches GetInterpolatorIndex's 9-entry table */        \
	Lightning                     lightning[2];            /* 168 - BSProceduralGeometry::Lightning pair */                \
	float                         unk178;                  /* 178 - written by interpolators[7]'s GetValue call */         \
	std::uint8_t                  pad17C[4];               /* 17C - unidentified */                                        \
	float                         duration;                /* 180 */                                                       \
	float                         progress;                /* 184 */                                                       \
	std::uint8_t                  pad188[2];               /* 188 */                                                       \
	bool                          needsRegeneration;       /* 18A - gates full branch-mesh regen in the mesh builder */    \
	bool                          regenerationSkipped;     /* 18B - 0 after a fresh regen, 1 on the fallback path */       \
	std::uint8_t                  pad18C[4];               /* 18C */                                                       \
	BSTaskletGroup                taskGroupHandle;         /* 190 */                                                       \
	BSProceduralLightningTasklet* tasklet;                 /* 198 */                                                       \
	bool                          interpolator0EventCache; /* 1A0 - last-frame cached event query from interpolators[0] */ \
	bool                          interpolator1EventCache; /* 1A1 - last-frame cached event query from interpolators[1] */ \
	std::uint8_t                  pad1A2[6];               /* 1A2 */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0xC8);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0xE4, 0x0);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0xE4);

		// members
		NiPointer<BSDynamicTriShape> geometry;     // A0 - lightning-bolt mesh geometry; unshifted in VR
		std::uint8_t                 padA8[0x2C];  // A8 - lightning-path working buffer (point/vertex/branch
												   //      pointers); owned alloc freed in dtor; feeds cachedBounds
		float cachedBounds[4];                     // D4 - cached bounding-sphere/transform snapshot; unshifted in VR
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // E4
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // E4
#endif

	private:
		void Dtor();
	};
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(BSProceduralLightningController, 0x190, 0x190, 0x1A8, 0xE8);
}
