#include "RE/R/ReferenceEffectController.h"

#include "RE/B/BSTempEffect.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRTTI.h"
#include "RE/P/ProcessLists.h"
#include "RE/R/ReferenceEffect.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	void ReferenceEffectController::HandleEvent([[maybe_unused]] const BSFixedString& a_event) {}

	float ReferenceEffectController::GetElapsedTime() { return 0.0f; }

	float ReferenceEffectController::GetScale() { return 1.0f; }

	void ReferenceEffectController::SwitchAttachedRoot([[maybe_unused]] NiNode* a_root, [[maybe_unused]] NiNode* a_attachRoot) {}

	const NiPoint3& ReferenceEffectController::GetSourcePosition() { return NiPoint3::Zero(); }

	bool ReferenceEffectController::GetUseSourcePosition() { return true; }

	bool ReferenceEffectController::GetNoInitialFlare() { return false; }

	bool ReferenceEffectController::GetEffectPersists() { return true; }

	bool ReferenceEffectController::GetGoryVisuals() { return false; }

	void ReferenceEffectController::RemoveHitEffect([[maybe_unused]] ReferenceEffect* a_refEffect) {}

	NiAVObject* ReferenceEffectController::GetAttachRoot()
	{
		auto ref = GetTargetReference();
		return ref ? ref->Get3D() : nullptr;
	}

	float ReferenceEffectController::GetParticleAttachExtent() { return 0.0f; }

	bool ReferenceEffectController::GetUseParticleAttachExtent() { return false; }

	bool ReferenceEffectController::GetDoParticles() { return true; }

	bool ReferenceEffectController::GetParticlesUseLocalSpace() { return false; }

	bool ReferenceEffectController::GetUseRootWorldRotate() { return false; }

	bool ReferenceEffectController::GetIsRootActor()
	{
		auto ref = GetTargetReference();
		return ref ? ref->formType == FormType::ActorCharacter : false;
	}

	bool ReferenceEffectController::GetClearWhenCellIsUnloaded() { return false; }

	bool ReferenceEffectController::EffectShouldFaceTarget() { return false; }

	TESObjectREFR* ReferenceEffectController::GetFacingTarget() { return nullptr; }

	bool ReferenceEffectController::GetShaderUseParentCell() { return true; }

	bool ReferenceEffectController::EffectAttachesToCamera() { return false; }

	bool ReferenceEffectController::EffectRotatesWithCamera() { return false; }

	bool ReferenceEffectController::GetAllowTargetRoot() { return true; }

	bool ReferenceEffectController::IsReadyForAttach() { return true; }

	void ReferenceEffectController::SetWindPoint([[maybe_unused]] const NiPoint3& a_point) {}

	const NiPoint3& ReferenceEffectController::GetWindPoint() { return NiPoint3::Zero(); }

	bool ReferenceEffectController::GetAllowNo3D() { return false; }

	void ReferenceEffectController::SaveGame([[maybe_unused]] BGSSaveGameBuffer* a_buf) {}

	void ReferenceEffectController::LoadGame([[maybe_unused]] BGSLoadGameBuffer* a_buf) {}

	void ReferenceEffectController::Start(ReferenceEffect** a_effectOut)
	{
		using func_t = decltype(&ReferenceEffectController::Start);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33961, 34761) };
		return func(this, a_effectOut);
	}

	void ReferenceEffectController::Stop()
	{
		const auto processLists = ProcessLists::GetSingleton();

		if (!processLists)
			return;

		BSSpinLockGuard locker(processLists->magicEffectsLock);

		for (auto& effect : processLists->magicEffects) {
			if (auto referenceEffect = netimmerse_cast<ReferenceEffect*>(effect.get())) {
				if (referenceEffect->controller == this) {
					effect.reset();
				}
			}
		}
	}
}
