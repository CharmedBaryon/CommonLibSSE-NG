#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTempEffect.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class BGSImpactData;
	class BGSParticleObjectCloneTask;
	class NiAVObject;
	class NiNode;

	class BSTempEffectParticle : public BSTempEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTempEffectParticle;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTempEffectParticle;
		inline static constexpr auto VTABLE = VTABLE_BSTempEffectParticle;
		inline static constexpr auto TYPE = TEMP_EFFECT_TYPE::kParticle;

		~BSTempEffectParticle() override;  // 00

		// override (BSTempEffect)
		const NiRTTI*                  GetRTTI() const override;       // 02
		void                           Detach() override;              // 27
		bool                           Update(float a_arg1) override;  // 28
		[[nodiscard]] TEMP_EFFECT_TYPE GetType() const override;       // 2C - { return kParticle; }

		static BSTempEffectParticle* Spawn(TESObjectCELL* a_cell, float a_lifetime, const char* a_modelName, const NiPoint3& a_rotation, const NiPoint3& a_position, float a_scale, std::uint32_t a_flags, NiAVObject* a_target)
		{
			using func_t = BSTempEffectParticle* (*)(TESObjectCELL*, float, const char*, const NiPoint3&, const NiPoint3&, float, std::uint32_t, NiAVObject*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29218, 30071) };
			return func(a_cell, a_lifetime, a_modelName, a_rotation, a_position, a_scale, a_flags, a_target);
		}
		static BSTempEffectParticle* Spawn(TESObjectCELL* a_cell, float a_lifetime, const char* a_modelName, const NiMatrix3& a_normal, const NiPoint3& a_position, float a_scale, std::uint32_t a_flags, NiAVObject* a_target)
		{
			using func_t = BSTempEffectParticle* (*)(TESObjectCELL*, float, const char*, const NiMatrix3&, const NiPoint3&, float, std::uint32_t, NiAVObject*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29219, 30072) };
			return func(a_cell, a_lifetime, a_modelName, a_normal, a_position, a_scale, a_flags, a_target);
		}

		// members
		NiPointer<NiAVObject>                       particleObject;           // 30
		BSTSmartPointer<BGSParticleObjectCloneTask> cloneTask;                // 38
		const char*                                 modelName;                // 40
		NiPointer<NiNode>                           dynamicCellNode;          // 48
		NiTransform                                 particleEffectTransform;  // 50
		std::uint32_t                               flags;                    // 84
		NiPointer<NiAVObject>                       spawnNode;                // 88
		NiTransform                                 spawnNodeTransform;       // 90
		std::uint32_t                               padC4;                    // C4
		BGSImpactData*                              impactData;               // C8
		BSSoundHandle                               sound1;                   // D0
		BSSoundHandle                               sound2;                   // DC
		std::uint8_t                                unkE8;                    // E8
		std::uint8_t                                padE9;                    // E9
		std::uint16_t                               unkEA;                    // EA
		std::uint32_t                               unkEC;                    // EC
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSTempEffectParticle) == 0xF0);
};
