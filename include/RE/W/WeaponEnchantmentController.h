#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class Actor;
	class ActorMagicCaster;
	class TESObjectWEAP;

	class WeaponEnchantmentController : public ReferenceEffectController
	{
	public:
		inline static constexpr auto RTTI = RTTI_WeaponEnchantmentController;
		inline static constexpr auto VTABLE = VTABLE_WeaponEnchantmentController;

		virtual ~WeaponEnchantmentController() = default;  // 00

		// override
		RE::TESObjectREFR*   GetTargetReference() override;          // 0B
		RE::BGSArtObject*    GetHitEffectArt() override;             // 0C
		RE::TESEffectShader* GetHitEffectShader() override;          // 0D
		bool                 GetManagerHandlesSaveLoad() override;   // 0E
		RE::NiAVObject*      GetAttachRoot() override;               // 0F
		float                GetParticleAttachExtent() override;     // 10
		bool                 GetUseParticleAttachExtent() override;  // 11
		bool                 GetDoParticles() override;              // 12
		bool                 GetParticlesUseLocalSpace() override;   // 13
		bool                 GetUseRootWorldRotate() override;       // 14
		bool                 GetIsRootActor() override;              // 15
		bool                 GetShaderUseParentCell() override;      // 19
		bool                 GetAllowTargetRoot() override;          // 2C
		bool                 IsReadyForAttach() override;            // 1D

		void SetAttachRoot()
		{
			using func_t = decltype(&WeaponEnchantmentController::SetAttachRoot);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34074, 34871) };
			func(this);
		}

		// members
		ActorMagicCaster*     caster;       // 08
		Actor*                target;       // 10
		TESEffectShader*      shader;       // 18
		BGSArtObject*         art;          // 20
		NiPointer<NiAVObject> attachRoot;   // 28
		TESObjectWEAP*        lastWeapon;   // 30
		bool                  firstPerson;  // 38
		std::uint8_t          pad39;        // 39
		std::uint16_t         pad3A;        // 3A
		std::uint32_t         pad3C;        // 3C
	};
	static_assert(sizeof(WeaponEnchantmentController) == 0x40);
}
