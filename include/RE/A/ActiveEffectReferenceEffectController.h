#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiPoint3.h"
#include "RE/R/ReferenceEffectController.h"

namespace RE
{
	class ActiveEffect;

	class ActiveEffectReferenceEffectController : public ReferenceEffectController
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActiveEffectReferenceEffectController;

		~ActiveEffectReferenceEffectController() override;  // 00

		// override (ReferenceEffectController)
		void             Unk_01(void) override;                                                    // 01
		void             Unk_02(void) override;                                                    // 02
		void             Unk_03(void) override;                                                    // 03
		void             SwitchAttachedRoot(std::uint64_t a_arg2, NiNode* a_attachRoot) override;  // 04 - return { effect->SwitchAttachedRoot(a_arg2, a_attachRoot); }
		const NiPoint3&  GetSourcePosition() override;                                             // 05
		bool             GetUseSourcePosition() override;                                          // 06
		bool             GetNoInitialFlare() override;                                             // 07
		bool             GetEffectPersists() override;                                             // 08
		bool             GetGoryVisuals() override;                                                // 09
		void             RemoveHitEffect(ReferenceEffect* a_refEffect) override;                   // 0A
		TESObjectREFR*   GetTargetReference() override;                                            // 0B
		BGSArtObject*    GetHitEffectArt() override;                                               // 0C
		TESEffectShader* GetHitEffectShader() override;                                            // 0D
		bool             GetManagerHandlesSaveLoad() override;                                     // 0E - { return false; }
		bool             EffectShouldFaceTarget() override;                                        // 17
		TESObjectREFR*   GetFacingTarget() override;                                               // 18
		void             SetWindPoint(const NiPoint3& a_point) override;                           // 1E - { windPoint = a_point; }
		const NiPoint3&  GetWindPoint() override;                                                  // 1F - { return windPoint; }
		bool             GetAllowNo3D() override;                                                  // 20
		void             SaveGame(BGSSaveGameBuffer* a_buf) override;                              // 21
		void             LoadGame(BGSLoadGameBuffer* a_buf) override;                              // 22

		// members
		ActiveEffect*   effect;     // 08
		ObjectRefHandle target;     // 10
		NiPoint3        windPoint;  // 14
	};
	static_assert(sizeof(ActiveEffectReferenceEffectController) == 0x20);
}
