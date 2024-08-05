#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiFrustum.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRect.h"

namespace RE
{
	class NiCamera : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiCamera;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiCamera;
		inline static constexpr auto VTABLE = VTABLE_NiCamera;

		struct RUNTIME_DATA
		{
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	define RUNTIME_DATA_CONTENT float worldToCam[4][4]; /* 0 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x40);
#elif defined(EXCLUSIVE_SKYRIM_VR)
#	define RUNTIME_DATA_CONTENT                   \
		float           worldToCam[4][4]; /* 0 */  \
		NiFrustum*      viewFrustumPtr;   /* 40 */ \
		BSTArray<void*> unk180;           /* 48 */ \
		BSTArray<void*> unk198;           /* 60 */ \
		BSTArray<void*> unk1B0;           /* 78 */ \
		std::uint32_t   unk1C8;           /* 90 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x98);
#else
#	define RUNTIME_DATA_CONTENT float worldToCam[4][4]; /* 0 */
			RUNTIME_DATA_CONTENT
		};
#endif

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
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17 - { return this; }
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

		static bool BoundInFrustum(const NiBound& a_bound, NiCamera* a_camera);
		static bool NodeInFrustum(NiAVObject* a_node, NiCamera* a_camera);
		static bool PointInFrustum(const NiPoint3& a_point, NiCamera* a_camera, float a_radius);
		bool        WindowPointToRay(std::int32_t a_x, std::int32_t a_y, NiPoint3& a_origin, NiPoint3& a_dir, float a_windowWidth, float a_windowHeight);
		bool        WorldPtToScreenPt3(const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);
		static bool WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x150, 0x1CC);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x150, 0x1CC);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;   // 110, 138
		RUNTIME_DATA2_CONTENT;  // 150, 1CC
#endif
	private:
		KEEP_FOR_RE();
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiCamera) == 0x188);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiCamera) == 0x208);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
