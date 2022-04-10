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
		inline static auto RTTI = RTTI_NiCamera;
		inline static auto Ni_RTTI = NiRTTI_NiCamera;

		struct RUNTIME_DATA
		{
			NiFrustum     viewFrustum;       // 00
			float         minNearPlaneDist;  // 1C
			float         maxFarNearRatio;   // 20
			NiRect<float> port;              // 24
			float         lodAdjust;         // 34
		};

		~NiCamera() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17 - { return this; }
		void          LoadBinary(NiStream& a_stream) override;            // 18 - { return; }
		void          LinkObject(NiStream& a_stream) override;            // 19 - { return; }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B - { return; }
		bool          IsEqual(NiObject* a_object) override;               // 1C
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          UpdateWorldBound() override;                        // 2F - { return; }
//		void          UpdateWorldData(NiUpdateData* a_data) override;     // 30

		static bool WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x150, 0x1CC);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x150, 0x1CC);
		}

		// members
		float     worldToCam[4][4];  // 110, 138
#ifndef ENABLE_SKYRIM_VR
		RUNTIME_DATA    runtimeData;       // 150
	};
	static_assert(sizeof(NiCamera) == 0x188);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		NiFrustum*      viewFrustumPtr;    // 178
		BSTArray<void*> unk180;            // 180
		BSTArray<void*> unk198;            // 198
		BSTArray<void*> unk1B0;            // 1B0
		std::uint32_t   unk1C8;            // 1C8
		RUNTIME_DATA    runtimeData;       // 1CC
	};
	static_assert(sizeof(NiCamera) == 0x208);
#else
		std::uint64_t   unk150[7];         // 150
	};
	static_assert(sizeof(NiCamera) == 0x188);
#endif
}
