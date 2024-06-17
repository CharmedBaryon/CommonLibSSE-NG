#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSWindModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWindModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSWindModifier;
		inline static constexpr auto VTABLE = VTABLE_BSWindModifier;

		~BSWindModifier() override;  // 00

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

		static BSWindModifier* Create(const BSFixedString& a_name, float a_strength);

		// members
		float         strength;  // 30
		std::uint32_t pad34;     // 34

	private:
		BSWindModifier* Ctor();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSWindModifier) == 0x38);
}
