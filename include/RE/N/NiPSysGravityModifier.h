#pragma once

#include "RE/N/NiPSysModifier.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiPSysGravityModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysGravityModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysGravityModifier;
		inline static constexpr auto VTABLE = VTABLE_NiPSysGravityModifier;

		enum class ForceType
		{
			kPlanar = 0,
			kSpherical
		};

		~NiPSysGravityModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                        // 1D
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// members
		NiAVObject*                                gravityObj;    // 30
		NiPoint3                                   gravityAxis;   // 38
		float                                      decay;         // 44
		float                                      strength;      // 48
		stl::enumeration<ForceType, std::uint32_t> forceType;     // 4C
		float                                      turbulence;    // 50
		float                                      scale;         // 54
		bool                                       worldAligned;  // 58
		std::uint8_t                               pad59;         // 59
		std::uint16_t                              pad5A;         // 5A
		std::uint32_t                              pad5C;         // 5C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiPSysGravityModifier) == 0x60);
}
