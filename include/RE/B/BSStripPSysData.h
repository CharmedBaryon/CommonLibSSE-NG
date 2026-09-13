#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiPSysData.h"

namespace RE
{
	struct StripPointData
	{
	public:
		// members
		RE::NiPoint3  ptCenter;               // 00
		RE::NiPoint3  verts[4];               // 0C
		RE::NiPoint3  lastverts[4];           // 3C
		RE::NiPoint3  directionVector;        // 6C
		RE::NiPoint3  tangentSideVectors[2];  // 78
		std::uint64_t unk90;                  // 90
		std::uint32_t unk98;                  // 98
		RE::NiColorA  pointColor;             // 9c
		float         pointSize;              // AC
		float         pointRadius;            // B0
		float         ptCreationTime;         // B4
	};
	static_assert(sizeof(StripPointData) == 0xB8);

	struct StripData
	{
	public:
		// members
		StripPointData* ptRingBuffer;    // 00
		std::uint32_t   pointCount;      // 08
		std::uint32_t   segmentCount;    // 0C
		int             ptCapacity;      // 10
		int             headIndex;       // 14
		int             tailIndex;       // 18
		float           lastUpdateTime;  // 1C
		double          lastPtUpdate;    // 20
	};
	static_assert(sizeof(StripData) == 0x28);

	class BSStripPSysData : NiPSysData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSStripPSysData;
		inline static constexpr auto VTABLE = VTABLE_BSStripPSysData;

		~BSStripPSysData() override;  // 00

		// override (NiPSysData)
		const NiRTTI* GetRTTI() const override;                                // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;       // 17
		void          LoadBinary(NiStream& a_stream) override;                 // 18
		void          LinkObject(NiStream& a_stream) override;                 // 19
		bool          RegisterStreamables(NiStream& a_stream) override;        // 1A
		void          SaveBinary(NiStream& a_stream) override;                 // 1B
		bool          IsEqual(NiObject* a_object) override;                    // 1C
		void          RemoveParticle(std::uint16_t a_particleCount) override;  // 28

		// members
		StripData* stripData;      // A8
		float      unkB0;          // B0
		float      unkB4;          // B4
		float      pointLifetime;  // B8
		short      maxPointCount;  // BC
		bool       doZPrepass;     // BE
	};
	STATIC_ASSERT_SIZE(BSStripPSysData, 0xC0, 0xC0, 0xC0, 0x28);
}
