#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiFrustum.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRect.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiMatrix44;
	class NiCamera : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiCamera;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiCamera;
		inline static constexpr auto VTABLE = VTABLE_NiCamera;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT float worldToCam[4][4]; /* 0 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x40);

		// VR Layout
		struct RUNTIME_DATA_VR
		{
#define RUNTIME_DATA_CONTENT_VR                                                              \
	float                   worldToCam[4][4];   /* 00 */                                     \
	NiFrustum*              viewFrustumBuffer;  /* 40 - UpdateProjection writes here */      \
	NiFrustum*              viewFrustumArray;   /* 48 - per-eye frustums for GetNearPlane */ \
	BSTArray<NiRect<float>> eyeViewportRects;   /* 50 */                                     \
	BSTArray<NiMatrix44>    eyeViewMatrices;    /* 68 */                                     \
	void*                   eyeCullingProcs[2]; /* 80 */                                     \
	std::uint32_t           unk1C8;             /* 90 */

			RUNTIME_DATA_CONTENT_VR
		};
		static_assert(sizeof(RUNTIME_DATA_VR) == 0x98);
		static_assert(offsetof(RUNTIME_DATA_VR, viewFrustumBuffer) == 0x40);
		static_assert(offsetof(RUNTIME_DATA_VR, viewFrustumArray) == 0x48);
		static_assert(offsetof(RUNTIME_DATA_VR, eyeViewportRects) == 0x50);
		static_assert(offsetof(RUNTIME_DATA_VR, eyeViewMatrices) == 0x68);
		static_assert(offsetof(RUNTIME_DATA_VR, eyeCullingProcs) == 0x80);
		static_assert(offsetof(RUNTIME_DATA_VR, unk1C8) == 0x90);

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                \
	NiFrustum     viewFrustum;      /* 00 */ \
	float         minNearPlaneDist; /* 1C */ \
	float         maxFarNearRatio;  /* 20 */ \
	NiRect<float> port;             /* 24 */ \
	float         lodAdjust;        /* 34 */

			RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x38);

		~NiCamera() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18 - { return; }
		void          LinkObject(NiStream& a_stream) override;            // 19 - { return; }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B - { return; }
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateWorldBound() override;                     // 2F - { return; }
		void UpdateWorldData(NiUpdateData* a_data) override;  // 30
#endif

		static bool BoundInFrustum(const NiBound& a_bound, RE::NiCamera* a_camera);
		bool        NodeInFrustum(NiAVObject* a_node);
		bool        PointInFrustum(const NiPoint3& a_point, float a_radius);

		bool        WindowPointToRay(std::int32_t a_x, std::int32_t a_y, NiPoint3& a_origin, NiPoint3& a_dir, float a_windowWidth, float a_windowHeight);
		bool        WorldPtToScreenPt3(const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);
		static bool WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);

		// Called by CreateClone: copies worldToCam, viewFrustum, and world.translate onto a_target.
		void CopyMembers(NiCamera* a_target, NiCloningProcess& a_cloning);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x110, 0);
		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA2, GetRuntimeData2, 0x150, 0x1CC);
		VR_RUNTIME_DATA_ACCESSOR(RUNTIME_DATA_VR, GetVRRuntimeData, 0x138);

		// return left in VR
		[[nodiscard]] float GetNearPlane() const
		{
			if (REL::Module::IsVR()) {
				return GetVRRuntimeData().viewFrustumArray->fNear;
			}
			// Fallback to Flat data
			return GetRuntimeData2().viewFrustum.fNear;
		}

#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;   // 110
		RUNTIME_DATA2_CONTENT;  // 150
#elif defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT_VR;  // 138
		RUNTIME_DATA2_CONTENT;    // 1CC
#endif
	};
	STATIC_ASSERT_SIZE(NiCamera, 0x188, 0x188, 0x208, 0x110);
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT_VR
#undef RUNTIME_DATA2_CONTENT