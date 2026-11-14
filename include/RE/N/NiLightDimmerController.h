#pragma once

#include "RE/N/NiFloatInterpController.h"

namespace RE
{
	class NiLightDimmerController : public NiFloatInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiLightDimmerController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiLightDimmerController;
		inline static constexpr auto VTABLE = VTABLE_NiLightDimmerController;

		~NiLightDimmerController() override;  // 00

		// override (NiFloatInterpController)
		const NiRTTI*      GetRTTI() const override;                                         // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;                // 17
		void               LoadBinary(NiStream& a_stream) override;                          // 18
		void               LinkObject(NiStream& a_stream) override;                          // 19
		bool               RegisterStreamables(NiStream& a_stream) override;                 // 1A
		void               SaveBinary(NiStream& a_stream) override;                          // 1B
		bool               IsEqual(NiObject* a_object) override;                             // 1C
		void               Update(NiUpdateData& a_data) override;                            // 27 - writes the target NiLight's fade
		[[nodiscard]] bool InterpTargetIsCorrectType(NiObjectNET* a_target) const override;  // 3C
		void               GetTargetFloatValue(float& a_value) override;                     // 3D

		static NiLightDimmerController* Create()
		{
			using func_t = decltype(&NiLightDimmerController::Create);
			static REL::Relocation<func_t> func{ RELOCATION_ID(72049, 73695) };
			return func();
		}
	};
	static_assert(sizeof(NiLightDimmerController) == 0x50);
}
