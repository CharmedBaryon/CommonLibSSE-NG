#include "RE/A/Actor.h"

#include "RE/A/AIProcess.h"
#include "RE/A/ActorMagicCaster.h"
#include "RE/B/BGSAttackData.h"
#include "RE/B/BGSColorForm.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSAnimationGraphManager.h"
#include "RE/B/BSFaceGenAnimationData.h"
#include "RE/B/BSFaceGenNiNode.h"
#include "RE/B/BShkbAnimationGraph.h"
#include "RE/B/bhkCharacterController.h"
#include "RE/E/ExtraCanTalkToPlayer.h"
#include "RE/E/ExtraFactionChanges.h"
#include "RE/E/ExtraLeveledCreature.h"
#include "RE/F/FixedStrings.h"
#include "RE/F/FormTraits.h"
#include "RE/H/HighProcessData.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/M/MiddleHighProcessData.h"
#include "RE/M/Misc.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiMath.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/ProcessLists.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESObjectMISC.h"
#include "RE/T/TESRace.h"
#include "RE/T/TESWorldSpace.h"

using namespace REL;

namespace RE
{
	NiPointer<Actor> Actor::LookupByHandle(RefHandle a_refHandle)
	{
		NiPointer<Actor> ref;
		LookupReferenceByHandle(a_refHandle, ref);
		return ref;
	}

	bool Actor::LookupByHandle(RefHandle a_refHandle, NiPointer<Actor>& a_refrOut)
	{
		return LookupReferenceByHandle(a_refHandle, a_refrOut);
	}

	bool Actor::AddAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const
	{
		BSAnimationGraphManagerPtr graphManager;
		GetAnimationGraphManager(graphManager);
		if (graphManager) {
			bool sinked = false;
			for (const auto& animationGraph : graphManager->graphs) {
				if (sinked) {
					break;
				}
				const auto eventSource = animationGraph->GetEventSource<BSAnimationGraphEvent>();
				for (const auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						sinked = true;
						break;
					}
				}
			}
			if (!sinked) {
				graphManager->graphs.front()->GetEventSource<BSAnimationGraphEvent>()->AddEventSink(a_sink);
				return true;
			}
		}
		return false;
	}

	void Actor::AddCastPower(SpellItem* a_power)
	{
		using func_t = decltype(&Actor::AddCastPower);
		REL::Relocation<func_t> func{ RELOCATION_ID(37787, 38736) };
		return func(this, a_power);
	}

	bool Actor::AddSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::AddSpell);
		REL::Relocation<func_t> func{ Offset::Actor::AddSpell };
		return func(this, a_spell);
	}

	void Actor::AddToFaction(TESFaction* a_faction, std::int8_t a_rank)
	{
		using func_t = decltype(&Actor::AddToFaction);
		REL::Relocation<func_t> func{ RELOCATION_ID(36678, 37686) };
		return func(this, a_faction, a_rank);
	}

	void Actor::AllowBleedoutDialogue(bool a_canTalk)
	{
		if (a_canTalk) {
			GetActorRuntimeData().boolFlags.set(BOOL_FLAGS::kCanSpeakToEssentialDown);
		} else {
			GetActorRuntimeData().boolFlags.reset(BOOL_FLAGS::kCanSpeakToEssentialDown);
		}
	}

	void Actor::AllowPCDialogue(bool a_talk)
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (!xTalk) {
			xTalk = new ExtraCanTalkToPlayer();
			extraList.Add(xTalk);
		}

		xTalk->talk = a_talk;
	}

	void Actor::CastPermanentMagic(bool a_wornItemEnchantments, bool a_baseSpells, bool a_raceSpells, bool a_everyActorAbility)
	{
		using func_t = decltype(&Actor::CastPermanentMagic);
		REL::Relocation<func_t> func{ RELOCATION_ID(37804, 38753) };
		return func(this, a_wornItemEnchantments, a_baseSpells, a_raceSpells, a_everyActorAbility);
	}

	bool Actor::CanAttackActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::CanAttackActor);
		REL::Relocation<func_t> func{ RELOCATION_ID(36532, 37532) };
		return func(this, a_actor);
	}

	bool Actor::CanFlyHere() const
	{
		const auto* worldSpace = GetWorldspace();
		return worldSpace && worldSpace->HasMaxHeightData();
	}

	bool Actor::CanOfferServices() const
	{
		const auto* vendorFac = GetVendorFaction();
		return vendorFac ? vendorFac->OffersServices() : false;
	}

	bool Actor::CanPickpocket() const
	{
		auto* _race = GetActorRuntimeData().race;
		if (!_race) {
			return false;
		}
		return _race->AllowsPickpocket() && !IsPlayerTeammate();
	}

	bool Actor::CanTalkToPlayer() const
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (xTalk) {
			return xTalk->talk;
		} else {
			auto* _race = GetActorRuntimeData().race;
			return _race != nullptr && _race->AllowsPCDialogue();
		}
	}

	bool Actor::CanUseIdle(TESIdleForm* a_idle) const
	{
		using func_t = decltype(&Actor::CanUseIdle);
		REL::Relocation<func_t> func{ RELOCATION_ID(36224, 37205) };
		return func(this, a_idle);
	}

	void Actor::ClearArrested()
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess && _currentProcess->IsArrested()) {
			_currentProcess->SetArrested(false);
			EvaluatePackage(false, false);
			auto procManager = ProcessLists::GetSingleton();
			if (procManager) {
				procManager->StopCombatAndAlarmOnActor(this, true);
			}
		}
	}

	void Actor::ClearExpressionOverride()
	{
		auto faceGen = GetFaceGenAnimationData();
		if (faceGen) {
			faceGen->ClearExpressionOverride();
		}
	}

	ActorHandle Actor::CreateRefHandle()
	{
		return GetHandle();
	}

	bool Actor::Decapitate()
	{
		using func_t = decltype(&Actor::Decapitate);
		REL::Relocation<func_t> func{ RELOCATION_ID(36631, 37639) };
		return func(this);
	}

	void Actor::DeselectSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::DeselectSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37820, 38769) };
		return func(this, a_spell);
	}

	void Actor::DispelAlteredStates(EffectArchetype a_exception)
	{
		using func_t = decltype(&Actor::DispelAlteredStates);
		REL::Relocation<func_t> func{ RELOCATION_ID(37864, 38819) };
		return func(this, a_exception);
	}

	void Actor::DispelWornItemEnchantments()
	{
		using func_t = decltype(&Actor::DispelWornItemEnchantments);
		REL::Relocation<func_t> func{ Offset::Actor::DispelWornItemEnchantments };
		return func(this);
	}

	void Actor::DoReset3D(bool a_updateWeight)
	{
		using func_t = decltype(&Actor::DoReset3D);
		REL::Relocation<func_t> func{ Offset::Actor::DoReset3D };
		return func(this, a_updateWeight);
	}

	void Actor::EnableAI(bool a_enable)
	{
		if (a_enable) {
			GetActorRuntimeData().boolBits.set(BOOL_BITS::kProcessMe);
		} else {
			GetActorRuntimeData().boolBits.reset(BOOL_BITS::kProcessMe);
			if (const auto controller = GetCharController()) {
				controller->SetLinearVelocityImpl(0.0f);
			}
		}
	}

	void Actor::EndInterruptPackage(bool a_skipDialogue)
	{
		using func_t = decltype(&Actor::EndInterruptPackage);
		REL::Relocation<func_t> func{ RELOCATION_ID(36475, 37474) };
		return func(this, a_skipDialogue);
	}

	void Actor::EvaluatePackage(bool a_immediate, bool a_resetAI)
	{
		using func_t = decltype(&Actor::EvaluatePackage);
		REL::Relocation<func_t> func{ RELOCATION_ID(36407, 37401) };
		return func(this, a_immediate, a_resetAI);
	}

	TESNPC* Actor::GetActorBase()
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	const TESNPC* Actor::GetActorBase() const
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	float Actor::GetActorValueModifier(ACTOR_VALUE_MODIFIER a_modifier, ActorValue a_value) const
	{
		using func_t = decltype(&Actor::GetActorValueModifier);
		REL::Relocation<func_t> func{ RELOCATION_ID(37524, 38469) };
		return func(this, a_modifier, a_value);
	}

	float Actor::GetAimAngle() const
	{
		bool aimActive{ false };
		GetGraphVariableBool(FixedStrings::GetSingleton()->bAimActive, aimActive);
		if (!aimActive) {
			return GetAngleX();
		}

		float aimPitchCurrent;
		GetGraphVariableFloat(FixedStrings::GetSingleton()->aimPitchCurrent, aimPitchCurrent);
		return -aimPitchCurrent;
	}

	float Actor::GetAimHeading() const
	{
		const float heading = GetHeading(false);

		float aimHeadingCurrent{ 0.0f };
		GetGraphVariableFloat(FixedStrings::GetSingleton()->aimHeadingCurrent, aimHeadingCurrent);

		return heading - aimHeadingCurrent;
	}

	InventoryEntryData* Actor::GetAttackingWeapon()
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (!_currentProcess || !_currentProcess->high || !_currentProcess->high->attackData || !_currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = _currentProcess->high->attackData;
		auto proc = _currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	const InventoryEntryData* Actor::GetAttackingWeapon() const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (!_currentProcess || !_currentProcess->high || !_currentProcess->high->attackData || !_currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = _currentProcess->high->attackData;
		auto proc = _currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	bhkCharacterController* Actor::GetCharController() const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		return _currentProcess ? _currentProcess->GetCharController() : nullptr;
	}

	uint32_t Actor::GetCollisionFilterInfo(uint32_t& a_outCollisionFilterInfo)
	{
		using func_t = decltype(&Actor::GetCollisionFilterInfo);
		REL::Relocation<func_t> func{ RELOCATION_ID(36559, 37560) };
		return func(this, a_outCollisionFilterInfo);
	}

	NiPointer<Actor> Actor::GetCommandingActor() const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		return _currentProcess ? _currentProcess->GetCommandingActor().get() : NiPointer<Actor>{};
	}

	TESFaction* Actor::GetCrimeFaction()
	{
		return GetCrimeFactionImpl();
	}

	const TESFaction* Actor::GetCrimeFaction() const
	{
		return GetCrimeFactionImpl();
	}

	TESPackage* Actor::GetCurrentPackage()
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			return _currentProcess->GetRunningPackage();
		}
		return nullptr;
	}

	const TESPackage* Actor::GetCurrentPackage() const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			return _currentProcess->GetRunningPackage();
		}
		return nullptr;
	}

	TESShout* Actor::GetCurrentShout()
	{
		if (GetActorRuntimeData().currentProcess) {
			return GetActorRuntimeData().currentProcess->GetCurrentShout();
		}
		return nullptr;
	}

	const TESShout* Actor::GetCurrentShout() const
	{
		if (GetActorRuntimeData().currentProcess) {
			return GetActorRuntimeData().currentProcess->GetCurrentShout();
		}
		return nullptr;
	}

	InventoryEntryData* Actor::GetEquippedEntryData(bool a_leftHand) const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (!_currentProcess || !_currentProcess->middleHigh) {
			return nullptr;
		}

		auto proc = _currentProcess->middleHigh;
		return a_leftHand ? proc->leftHand : proc->rightHand;
	}

	TESForm* Actor::GetEquippedObject(bool a_leftHand) const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			if (a_leftHand) {
				return _currentProcess->GetEquippedLeftHand();
			} else {
				return _currentProcess->GetEquippedRightHand();
			}
		} else {
			return nullptr;
		}
	}

	TESForm* Actor::GetEquippedObjectInSlot(const BGSEquipSlot* slot) const
	{
		auto _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			for (const auto& equippedObject : _currentProcess->equippedForms) {
				if (equippedObject.slot == slot) {
					return equippedObject.object;
				}
			}
		}

		return nullptr;
	}

	float Actor::GetEquippedWeight()
	{
		if (GetActorRuntimeData().equippedWeight < 0.0f) {
			return CalcEquippedWeight();
		}
		return GetActorRuntimeData().equippedWeight;
	}

	std::int32_t Actor::GetFactionRank(TESFaction* a_faction, bool a_isPlayer)
	{
		using func_t = decltype(&Actor::GetFactionRank);
		REL::Relocation<func_t> func{ RELOCATION_ID(36668, 37676) };
		return func(this, a_faction, a_isPlayer);
	}

	std::int32_t Actor::GetGoldAmount(bool a_noInit)
	{
		const auto inv = GetInventory([](TESBoundObject& a_object) -> bool {
			return a_object.IsGold();
		},
			a_noInit);

		const auto dobj = BGSDefaultObjectManager::GetSingleton();
		if (!dobj) {
			return 0;
		}

		const auto gold = dobj->GetObject<TESObjectMISC>(DefaultObjectID::kGold);
		const auto it = inv.find(*gold);
		return it != inv.end() ? it->second.first : 0;
	}

	ActorHandle Actor::GetHandle()
	{
		return ActorHandle(this);
	}

	NiAVObject* Actor::GetHeadPartObject(BGSHeadPart::HeadPartType a_type)
	{
		const auto actorBase = GetActorBase();
		const auto faceNode = GetFaceNodeSkinned();
		const auto facePart = actorBase ? actorBase->GetCurrentHeadPartByType(a_type) : nullptr;
		return faceNode && facePart ? faceNode->GetObjectByName(facePart->formEditorID) : nullptr;
	}

	float Actor::GetHeight()
	{
		const auto min = GetBoundMin();
		const auto max = GetBoundMax();
		const auto diff = max.z - min.z;
		const auto height = GetBaseHeight() * diff;

		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (!_currentProcess || !_currentProcess->InHighProcess()) {
			return height;
		}

		const auto cachedHeight = _currentProcess->GetCachedHeight();
		if (cachedHeight == 0.0) {
			_currentProcess->SetCachedHeight(height);
			return height;
		} else {
			return cachedHeight;
		}
	}

	HighProcessData* Actor::GetHighProcess() const
	{
		const auto& runtimeData = GetActorRuntimeData();
		return runtimeData.currentProcess ? runtimeData.currentProcess->high : nullptr;
	}

	Actor* Actor::GetKiller() const
	{
		if (IsDead(false)) {
			return nullptr;
		}

		return GetActorRuntimeData().myKiller.get().get();
	}

	std::uint16_t Actor::GetLevel() const
	{
		using func_t = decltype(&Actor::GetLevel);
		REL::Relocation<func_t> func{ Offset::Actor::GetLevel };
		return func(this);
	}

	MiddleHighProcessData* Actor::GetMiddleHighProcess() const
	{
		const auto& runtimeData = GetActorRuntimeData();
		return runtimeData.currentProcess ? runtimeData.currentProcess->middleHigh : nullptr;
	}

	bool Actor::GetMount(NiPointer<Actor>& a_outMount)
	{
		using func_t = decltype(&Actor::GetMount);
		REL::Relocation<func_t> func{ RELOCATION_ID(37757, 38702) };
		return func(this, a_outMount);
	}

	double Actor::GetMoveDirectionRelativeToFacing()
	{
		using func_t = decltype(&Actor::GetMoveDirectionRelativeToFacing);
		REL::Relocation<func_t> func{ RELOCATION_ID(36935, 37960) };
		return func(this);
	}

	bool Actor::GetMountedBy(NiPointer<Actor>& a_outRider)
	{
		using func_t = decltype(&Actor::GetMountedBy);
		REL::Relocation<func_t> func{ RELOCATION_ID(37758, 38703) };
		return func(this, a_outRider);
	}

	ObjectRefHandle Actor::GetOccupiedFurniture() const
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			return _currentProcess->GetOccupiedFurniture();
		} else {
			return {};
		}
	}

	TESRace* Actor::GetRace() const
	{
		auto* _race = GetActorRuntimeData().race;
		if (_race) {
			return _race;
		}

		auto base = GetActorBase();
		return base ? base->race : nullptr;
	}

	float Actor::GetRegenDelay(ActorValue a_actorValue) const
	{
		const auto& runtimeData = GetActorRuntimeData();
		if (runtimeData.currentProcess) {
			return runtimeData.currentProcess->GetRegenDelay(a_actorValue);
		}
		return 0.0f;
	}

	bool Actor::GetRider(NiPointer<Actor>& a_outRider)
	{
		using func_t = decltype(&Actor::GetRider);
		REL::Relocation<func_t> func{ RELOCATION_ID(37758, 38703) };
		return func(this, a_outRider);
	}

	TESObjectARMO* Actor::GetSkin() const
	{
		if (const auto base = GetActorBase(); base && base->skin) {
			return base->skin;
		} else if (const auto aRace = GetRace(); aRace && aRace->skin) {
			return aRace->skin;
		}
		return nullptr;
	}

	TESObjectARMO* Actor::GetSkin(BGSBipedObjectForm::BipedObjectSlot a_slot, bool a_noInit)
	{
		if (const auto worn = GetWornArmor(a_slot, a_noInit); worn) {
			return worn;
		}
		return GetSkin();
	}

	SOUL_LEVEL Actor::GetSoulSize() const
	{
		using func_t = decltype(&Actor::GetSoulSize);
		REL::Relocation<func_t> func{ RELOCATION_ID(37862, 38817) };
		return func(this);
	}

	float Actor::GetTotalCarryWeight()
	{
		using func_t = decltype(&Actor::GetTotalCarryWeight);
		REL::Relocation<func_t> func{ RELOCATION_ID(36456, 37452) };
		return func(this);
	}

	TESFaction* Actor::GetVendorFaction()
	{
		auto* _vendorFaction = GetActorRuntimeData().vendorFaction;
		if (!_vendorFaction) {
			CalculateCurrentVendorFaction();
		}
		return _vendorFaction;
	}

	const TESFaction* Actor::GetVendorFaction() const
	{
		auto* _vendorFaction = GetActorRuntimeData().vendorFaction;
		if (!_vendorFaction) {
			CalculateCurrentVendorFaction();
		}
		return _vendorFaction;
	}

	float Actor::GetVoiceRecoveryTime()
	{
		using func_t = decltype(&Actor::GetVoiceRecoveryTime);
		REL::Relocation<func_t> func{ RELOCATION_ID(37854, 38808) };
		return func(this);
	}

#if !defined(ENABLE_SKYRIM_VR)
	float Actor::GetWarmthRating() const
	{
		using func_t = decltype(&Actor::GetWarmthRating);
		REL::Relocation<func_t> func{ RELOCATION_ID(25834, 26394) };
		return func(this);
	}
#endif

	TESObjectARMO* Actor::GetWornArmor(BGSBipedObjectForm::BipedObjectSlot a_slot, bool a_noInit)
	{
		const auto inv = GetInventory([](TESBoundObject& a_object) {
			return a_object.IsArmor();
		},
			a_noInit);

		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count > 0 && entry->IsWorn()) {
				const auto armor = item->As<TESObjectARMO>();
				if (armor && armor->HasPartOf(a_slot)) {
					return armor;
				}
			}
		}

		return nullptr;
	}

	TESObjectARMO* Actor::GetWornArmor(FormID a_formID, bool a_noInit)
	{
		const auto inv = GetInventory([=](TESBoundObject& a_object) {
			return a_object.IsArmor() && a_object.GetFormID() == a_formID;
		},
			a_noInit);

		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count > 0 && entry->IsWorn()) {
				return item->As<TESObjectARMO>();
			}
		}

		return nullptr;
	}

	bool Actor::HasKeyword(const BGSKeyword* a_keyword) const
	{
		return HasKeywordHelper(a_keyword);
	}

	bool Actor::HasKeywordString(std::string_view a_formEditorID)
	{
		const auto base = GetActorBase();
		return base && base->HasApplicableKeywordString(a_formEditorID);
	}

	bool Actor::HasLineOfSight(TESObjectREFR* a_ref, bool& a_arg2)
	{
		using func_t = decltype(&Actor::HasLineOfSight);
		REL::Relocation<func_t> func{ RELOCATION_ID(53029, 53829) };
		return func(this, a_ref, a_arg2);
	}

	bool Actor::HasOutfitItems(BGSOutfit* a_outfit)
	{
		using func_t = decltype(&Actor::HasOutfitItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(19265, 19691) };
		return func(this, a_outfit);
	}

	bool Actor::HasPerk(BGSPerk* a_perk) const
	{
		using func_t = decltype(&Actor::HasPerk);
		REL::Relocation<func_t> func{ Offset::Actor::HasPerk };
		return func(this, a_perk);
	}

	bool Actor::HasShout(TESShout* a_shout) const
	{
		using func_t = decltype(&Actor::HasShout);
		REL::Relocation<func_t> func{ RELOCATION_ID(37829, 38783) };
		return func(this, a_shout);
	}

	bool Actor::HasSpell(SpellItem* a_spell) const
	{
		using func_t = decltype(&Actor::HasSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37828, 38782) };
		return func(this, a_spell);
	}

	void Actor::InitiateDoNothingPackage()
	{
		using func_t = decltype(&Actor::InitiateDoNothingPackage);
		REL::Relocation<func_t> func{ RELOCATION_ID(36408, 37402) };
		return func(this);
	}

	void Actor::InterruptCast(bool a_restoreMagicka) const
	{
		using func_t = decltype(&Actor::InterruptCast);
		REL::Relocation<func_t> func{ RELOCATION_ID(37808, 38757) };
		return func(this, a_restoreMagicka);
	}

	bool Actor::IsAttacking() const
	{
		using func_t = decltype(&Actor::IsAttacking);
		REL::Relocation<func_t> func{ RELOCATION_ID(37637, 38590) };
		return func(this);
	}

	bool Actor::IsAIEnabled() const
	{
		return GetActorRuntimeData().boolBits.all(BOOL_BITS::kProcessMe);
	}

	bool Actor::IsAlarmed() const
	{
		auto currentPackage = GetCurrentPackage();
		return currentPackage && currentPackage->packData.packType.get() == PACKAGE_PROCEDURE_TYPE::kAlarm;
	}

	bool Actor::IsAMount() const
	{
		return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kIsAMount);
	}

	bool Actor::IsAnimationDriven() const
	{
		bool result = false;
		return GetGraphVariableBool("bAnimationDriven", result) && result;
	}

	bool Actor::IsBeingRidden() const
	{
		return IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsBlocking() const
	{
		using func_t = decltype(&Actor::IsBlocking);
		REL::Relocation<func_t> func{ RELOCATION_ID(36927, 37952) };
		return func(this);
	}

	bool Actor::IsCasting(MagicItem* a_spell) const
	{
		using func_t = decltype(&Actor::IsCasting);
		REL::Relocation<func_t> func{ RELOCATION_ID(37810, 38759) };
		return func(this, a_spell);
	}

	bool Actor::IsCommandedActor() const
	{
		return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kIsCommandedActor);
	}

	bool Actor::IsCurrentShout(SpellItem* a_power)
	{
		using func_t = decltype(&Actor::IsCurrentShout);
		REL::Relocation<func_t> func{ RELOCATION_ID(37858, 38812) };
		return func(this, a_power);
	}

	bool Actor::IsDualCasting() const
	{
		auto _currentProcess = GetActorRuntimeData().currentProcess;
		if (!_currentProcess) {
			return false;
		}

		const auto highProcess = _currentProcess->high;
		return highProcess && highProcess->isDualCasting;
	}

	bool Actor::IsEssential() const
	{
		return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kEssential);
	}

	bool Actor::IsFactionInCrimeGroup(const TESFaction* a_faction) const
	{
		auto crimFac = GetCrimeFaction();
		if (!crimFac) {
			return false;
		}

		if (crimFac == a_faction) {
			return true;
		} else {
			return crimFac->IsFactionInCrimeGroup(a_faction);
		}
	}

	bool Actor::IsGhost() const
	{
		using func_t = decltype(&Actor::IsGhost);
		REL::Relocation<func_t> func{ Offset::Actor::GetGhost };
		return func(this);
	}

	bool Actor::IsGuard() const
	{
		return GetActorRuntimeData().boolBits.all(BOOL_BITS::kGuard);
	}

	bool Actor::IsHostileToActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::IsHostileToActor);
		REL::Relocation<func_t> func{ Offset::Actor::GetHostileToActor };
		return func(this, a_actor);
	}

	bool Actor::IsInCastPowerList(SpellItem* a_power)
	{
		using func_t = decltype(&Actor::IsInCastPowerList);
		REL::Relocation<func_t> func{ RELOCATION_ID(37793, 38742) };
		return func(this, a_power);
	}

	bool Actor::IsInMidair() const
	{
		using func_t = decltype(&Actor::IsInMidair);
		REL::Relocation<func_t> func{ RELOCATION_ID(36259, 37243) };
		return func(this);
	}

	bool Actor::IsInRagdollState() const
	{
		using func_t = decltype(&Actor::IsInRagdollState);
		REL::Relocation<func_t> func{ RELOCATION_ID(36492, 37491) };
		return func(this);
	}

	bool Actor::IsLeveled() const
	{
		using func_t = decltype(&Actor::IsLeveled);
		REL::Relocation<func_t> func{ RELOCATION_ID(19824, 20229) };
		return func(this);
	}

	bool Actor::IsLimbGone(std::uint32_t a_limb)
	{
		using func_t = decltype(&Actor::IsLimbGone);
		REL::Relocation<func_t> func{ RELOCATION_ID(19338, 19765) };
		return func(this, a_limb);
	}

	bool Actor::IsMoving() const
	{
		using func_t = decltype(&Actor::IsMoving);
		REL::Relocation<func_t> func{ RELOCATION_ID(36928, 37953) };
		return func(this);
	}

	bool Actor::IsOnMount() const
	{
		return !IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsOverEncumbered() const
	{
		using func_t = decltype(&Actor::IsOverEncumbered);
		REL::Relocation<func_t> func{ RELOCATION_ID(36457, 37453) };
		return func(this);
	}

	bool Actor::IsPlayerTeammate() const
	{
		return GetActorRuntimeData().boolBits.all(BOOL_BITS::kPlayerTeammate);
	}

	bool Actor::IsProtected() const
	{
		return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kProtected);
	}

	bool Actor::IsRunning() const
	{
		using func_t = decltype(&Actor::IsRunning);
		REL::Relocation<func_t> func{ Offset::Actor::IsRunning };
		return func(this);
	}

	bool Actor::IsSneaking() const
	{
		if (!AsActorState()->IsSneaking()) {
			return false;
		}

		if (AsActorState()->IsSwimming()) {
			return false;
		}

		if (IsOnMount()) {
			return false;
		}

		return true;
	}

	bool Actor::IsSummoned() const noexcept
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		return _currentProcess && _currentProcess->GetIsSummonedCreature();
	}

	bool Actor::IsTrespassing() const
	{
		return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kIsTrespassing);
	}

	void Actor::KillImmediate()
	{
		using func_t = decltype(&Actor::KillImmediate);
		REL::Relocation<func_t> func{ RELOCATION_ID(36723, 37735) };
		return func(this);
	}

	void Actor::PlayASound(BSSoundHandle& a_result, FormID a_formID, bool a_arg3, std::uint32_t a_flags)
	{
		using func_t = decltype(&Actor::PlayASound);
		REL::Relocation<func_t> func{ RELOCATION_ID(36730, 37743) };
		return func(this, a_result, a_formID, a_arg3, a_flags);
	}

	void Actor::ProcessVATSAttack(MagicCaster* a_caster, bool a_hasTargetAnim, TESObjectREFR* a_target, bool a_leftHand)
	{
		// in VR the function exists but is void.
		using func_t = decltype(&Actor::ProcessVATSAttack);
		REL::Relocation<func_t> func{ RELOCATION_ID(40230, 41233) };
		return func(this, a_caster, a_hasTargetAnim, a_target, a_leftHand);
	}

	void Actor::RemoveAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const
	{
		BSAnimationGraphManagerPtr graphManager;
		GetAnimationGraphManager(graphManager);
		if (graphManager) {
			bool sinked = true;
			for (const auto& animationGraph : graphManager->graphs) {
				if (!sinked) {
					break;
				}
				const auto eventSource = animationGraph->GetEventSource<BSAnimationGraphEvent>();
				for (const auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						eventSource->RemoveEventSink(a_sink);
						sinked = false;
						break;
					}
				}
			}
		}
	}

	void Actor::RemoveCastScroll(SpellItem* a_spell, MagicSystem::CastingSource a_source)
	{
		using func_t = decltype(&Actor::RemoveCastScroll);
		REL::Relocation<func_t> func{ RELOCATION_ID(37798, 38747) };
		return func(this, a_spell, a_source);
	}

	void Actor::RemoveExtraArrows3D()
	{
		extraList.RemoveByType(ExtraDataType::kAttachedArrows3D);
	}

	void Actor::RemoveFromFaction(RE::TESFaction* a_faction)
	{
		using func_t = decltype(&Actor::RemoveFromFaction);
		REL::Relocation<func_t> func{ RELOCATION_ID(36680, 37688) };
		return func(this, a_faction);
	}

	bool Actor::RemoveSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::RemoveSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37772, 38717) };
		return func(this, a_spell);
	}

	std::int32_t Actor::RequestDetectionLevel(Actor* a_target, DETECTION_PRIORITY a_priority)
	{
		using func_t = decltype(&Actor::RequestDetectionLevel);
		REL::Relocation<func_t> func{ Offset::Actor::RequestDetectionLevel };
		return func(this, a_target, a_priority);
	}

	bool Actor::SetDefaultOutfit(BGSOutfit* a_outfit, bool a_update3D)
	{
		const auto npc = GetActorBase();
		if (!npc || !a_outfit || npc->defaultOutfit == a_outfit) {
			return false;
		}
		RemoveOutfitItems(npc->defaultOutfit);
		npc->SetDefaultOutfit(a_outfit);
		InitInventoryIfRequired();
		if (!IsDisabled()) {
			AddWornOutfit(a_outfit, a_update3D);
		}
		return true;
	}

	void Actor::SetLifeState(ACTOR_LIFE_STATE a_lifeState)
	{
		using func_t = decltype(&Actor::SetLifeState);
		REL::Relocation<func_t> func{ RELOCATION_ID(36604, 37612) };
		return func(this, a_lifeState);
	}

	bool Actor::SetSleepOutfit(BGSOutfit* a_outfit, bool a_update3D)
	{
		const auto npc = GetActorBase();
		if (!npc || !a_outfit || npc->sleepOutfit == a_outfit) {
			return false;
		}
		RemoveOutfitItems(npc->sleepOutfit);
		npc->SetSleepOutfit(a_outfit);
		InitInventoryIfRequired();
		if (!IsDisabled()) {
			AddWornOutfit(a_outfit, a_update3D);
		}
		return true;
	}

	void Actor::SetRotationX(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationX);
		REL::Relocation<func_t> func{ RELOCATION_ID(36602, 37610) };
		return func(this, a_angle);
	}

	void Actor::SetRotationZ(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationZ);
		REL::Relocation<func_t> func{ RELOCATION_ID(36248, 37230) };
		return func(this, a_angle);
	}

	void Actor::StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner, bool a_allowWarning)
	{
		using func_t = decltype(&Actor::StealAlarm);
		REL::Relocation<func_t> func{ RELOCATION_ID(36427, 37422) };
		return func(this, a_ref, a_object, a_num, a_total, a_owner, a_allowWarning);
	}

	void Actor::StopAlarmOnActor()
	{
		EndInterruptPackage(false);

		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			_currentProcess->ClearActionHeadtrackTarget(true);
		}
	}

	void Actor::StopInteractingQuick(bool a_unk02)
	{
		using func_t = decltype(&Actor::StopInteractingQuick);
		REL::Relocation<func_t> func{ RELOCATION_ID(37752, 38697) };
		return func(this, a_unk02);
	}

	void Actor::StopMoving(float a_delta)
	{
		using func_t = decltype(&Actor::StopMoving);
		REL::Relocation<func_t> func{ RELOCATION_ID(36801, 37817) };
		return func(this, a_delta);
	}

	void Actor::SwitchRace(TESRace* a_race, bool a_player)
	{
		using func_t = decltype(&Actor::SwitchRace);
		REL::Relocation<func_t> func{ Offset::Actor::SwitchRace };
		return func(this, a_race, a_player);
	}

	void Actor::TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_ownership, std::int32_t a_crime)
	{
		using func_t = decltype(&Actor::TrespassAlarm);
		REL::Relocation<func_t> func{ RELOCATION_ID(36432, 37427) };
		return func(this, a_ref, a_ownership, a_crime);
	}

	void Actor::UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData)
	{
		using func_t = decltype(&Actor::UpdateArmorAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateArmorAbility };
		return func(this, a_armor, a_extraData);
	}

	void Actor::UpdateAwakeSound(NiAVObject* a_obj3D)
	{
		using func_t = decltype(&Actor::UpdateAwakeSound);
		REL::Relocation<func_t> func{ RELOCATION_ID(36943, 37968) };
		return func(this, a_obj3D);
	}

	void Actor::Update3DModel()
	{
		auto* _currentProcess = GetActorRuntimeData().currentProcess;
		if (_currentProcess) {
			_currentProcess->Update3DModel(this);
		}
	}

	void Actor::UpdateHairColor()
	{
		auto npc = GetActorBase();
		if (npc && npc->headRelatedData) {
			const auto hairColor = npc->headRelatedData->hairColor;
			if (hairColor) {
				NiColor color;
				color.red = static_cast<float>(hairColor->color.red) / static_cast<float>(128.0);
				color.green = static_cast<float>(hairColor->color.green) / static_cast<float>(128.0);
				color.blue = static_cast<float>(hairColor->color.blue) / static_cast<float>(128.0);

				auto model = Get3D(false);
				if (model) {
					model->UpdateHairColor(color);
				}
			}
		}
	}

	void Actor::UpdateRegenDelay(ActorValue a_actorValue, float a_regenDelay)
	{
		const auto& runtimeData = GetActorRuntimeData();
		if (runtimeData.currentProcess) {
			runtimeData.currentProcess->UpdateRegenDelay(a_actorValue, a_regenDelay);
		}
	}

	void Actor::UpdateSkinColor()
	{
		const auto* npc = GetActorBase();
		if (npc) {
			NiColor color;
			color.red = static_cast<float>(npc->bodyTintColor.red) / static_cast<float>(255.0);
			color.green = static_cast<float>(npc->bodyTintColor.green) / static_cast<float>(255.0);
			color.blue = static_cast<float>(npc->bodyTintColor.blue) / static_cast<float>(255.0);

			auto thirdPerson = Get3D(false);
			if (thirdPerson) {
				thirdPerson->UpdateBodyTint(color);
			}

			auto firstPerson = Get3D(true);
			if (firstPerson) {
				firstPerson->UpdateBodyTint(color);
			}
		}
	}

	void Actor::UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand)
	{
		using func_t = decltype(&Actor::UpdateWeaponAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateWeaponAbility };
		return func(this, a_weapon, a_extraData, a_leftHand);
	}

	void Actor::VisitArmorAddon(TESObjectARMO* a_armor, TESObjectARMA* a_arma, std::function<void(bool a_firstPerson, NiAVObject& a_obj)> a_visitor)
	{
		enum
		{
			k3rd,
			k1st,
			kTotal
		};

		char addonString[REX::W32::MAX_PATH]{ '\0' };
		a_arma->GetNodeName(addonString, this, a_armor, -1);
		std::array<NiAVObject*, kTotal> skeletonRoot = { Get3D(k3rd), Get3D(k1st) };
		if (skeletonRoot[k1st] == skeletonRoot[k3rd]) {
			skeletonRoot[k1st] = nullptr;
		}
		for (std::size_t i = 0; i < skeletonRoot.size(); ++i) {
			if (skeletonRoot[i]) {
				const auto obj = skeletonRoot[i]->GetObjectByName(addonString);
				if (obj) {
					a_visitor(i == k1st, *obj);
				}
			}
		}
	}

	bool Actor::VisitFactions(std::function<bool(TESFaction* a_faction, std::int8_t a_rank)> a_visitor)
	{
		auto base = GetActorBase();
		if (base) {
			for (auto& factionInfo : base->factions) {
				if (a_visitor(factionInfo.faction, factionInfo.rank)) {
					return true;
				}
			}

			auto factionChanges = extraList.GetByType<ExtraFactionChanges>();
			if (factionChanges) {
				for (auto& change : factionChanges->factionChanges) {
					if (a_visitor(change.faction, change.rank)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	void Actor::VisitSpells(ForEachSpellVisitor& a_visitor)
	{
		using func_t = decltype(&Actor::VisitSpells);
		REL::Relocation<func_t> func{ RELOCATION_ID(37827, 38781) };
		return func(this, a_visitor);
	}

	std::uint8_t Actor::WhoIsCasting()
	{
		std::uint8_t result{ 0 };
		for (auto i = 0; i < 4; i++) {
			if (auto magicCaster = GetActorRuntimeData().magicCasters[i]) {
				auto castingSource = magicCaster->GetCastingSource();
				if (magicCaster->currentSpell) {
					result |= 1 << std::to_underlying(castingSource);
				}
			}
		}

		return result;
	}

	bool Actor::WouldBeStealing(const TESObjectREFR* a_target) const
	{
		return a_target != nullptr && !a_target->IsAnOwner(this, true, false);
	}

	void Actor::CalculateCurrentVendorFaction() const
	{
		using func_t = decltype(&Actor::CalculateCurrentVendorFaction);
		REL::Relocation<func_t> func{ RELOCATION_ID(36392, 37383) };
		return func(this);
	}

	float Actor::CalcEquippedWeight()
	{
		using func_t = decltype(&Actor::CalcEquippedWeight);
		REL::Relocation<func_t> func{ RELOCATION_ID(37016, 38044) };
		return func(this);
	}

	TESFaction* Actor::GetCrimeFactionImpl() const
	{
		if (IsCommandedActor()) {
			return nullptr;
		}

		auto xFac = extraList.GetByType<ExtraFactionChanges>();
		if (xFac && (xFac->crimeFaction || xFac->removeCrimeFaction)) {
			return xFac->crimeFaction;
		}

		auto base = GetActorBase();
		return base ? base->crimeFaction : nullptr;
	}

	void Actor::AddWornOutfit(BGSOutfit* a_outfit, bool a_forceUpdate)
	{
		using func_t = decltype(&Actor::AddWornOutfit);
		REL::Relocation<func_t> func{ RELOCATION_ID(19266, 19692) };
		return func(this, a_outfit, a_forceUpdate);
	}

	void Actor::RemoveOutfitItems(BGSOutfit* a_outfit)
	{
		using func_t = decltype(&Actor::RemoveOutfitItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(19264, 19690) };
		return func(this, a_outfit);
	}

#ifdef SKYRIM_CROSS_VR
	void Actor::Unk_A2()
	{
		RelocateVirtual<decltype(&Actor::Unk_A2)>(0x0A2, 0x0A3, this);
	}

	void Actor::PlayPickUpSound(TESBoundObject* a_object, bool a_pickup, bool a_use)
	{
		RelocateVirtual<decltype(&Actor::PlayPickUpSound)>(0x0A3, 0x0A4, this, a_object, a_pickup, a_use);
	}

	float Actor::GetHeading(bool a_ignoreRaceSettings) const
	{
		return RelocateVirtual<decltype(&Actor::GetHeading)>(0x0A4, 0x0A5, this, a_ignoreRaceSettings);
	}

	void Actor::SetAvoidanceDisabled(bool a_set)
	{
		RelocateVirtual<decltype(&Actor::SetAvoidanceDisabled)>(0x0A5, 0x0A6, this, a_set);
	}

	void Actor::DrawWeaponMagicHands(bool a_draw)
	{
		RelocateVirtual<decltype(&Actor::DrawWeaponMagicHands)>(0x0A6, 0x0A8, this, a_draw);
	}

	void Actor::DetachCharController()
	{
		RelocateVirtual<decltype(&Actor::DetachCharController)>(0x0A7, 0x0A9, this);
	}

	void Actor::RemoveCharController()
	{
		RelocateVirtual<decltype(&Actor::RemoveCharController)>(0x0A8, 0x0AA, this);
	}

	void Actor::SetPosition(const NiPoint3& a_pos, bool a_updateCharController)
	{
		RelocateVirtual<decltype(&Actor::SetPosition)>(0x0A9, 0x0AB, this, a_pos, a_updateCharController);
	}

	void Actor::KillDying()
	{
		RelocateVirtual<decltype(&Actor::KillDying)>(0x0AA, 0x0AC, this);
	}

	void Actor::Resurrect(bool a_resetInventory, bool a_attach3D)
	{
		RelocateVirtual<decltype(&Actor::Resurrect)>(0x0AB, 0x0AD, this, a_resetInventory, a_attach3D);
	}

	bool Actor::PutActorOnMountQuick()
	{
		return RelocateVirtual<decltype(&Actor::PutActorOnMountQuick)>(0x0AC, 0x0AE, this);
	}

	void Actor::Update(float a_delta)
	{
		RelocateVirtual<decltype(&Actor::Update)>(0x0AD, 0x0AF, this, a_delta);
	}

	void Actor::UpdateNoAI(float a_delta)
	{
		RelocateVirtual<decltype(&Actor::UpdateNoAI)>(0x0AE, 0x0B0, this, a_delta);
	}

	void Actor::UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_controller)
	{
		RelocateVirtual<decltype(&Actor::UpdateCharacterControllerSimulationSettings)>(0x0AF, 0x0B1, this, a_controller);
	}

	void Actor::PotentiallyFixRagdollState()
	{
		RelocateVirtual<decltype(&Actor::PotentiallyFixRagdollState)>(0x0B0, 0x0B2, this);
	}

	void Actor::UpdateNonRenderSafe(float a_delta)
	{
		RelocateVirtual<decltype(&Actor::UpdateNonRenderSafe)>(0x0B1, 0x0B3, this, a_delta);
	}

	void Actor::OnItemEquipped(bool a_playAnim)
	{
		RelocateVirtual<decltype(&Actor::OnItemEquipped)>(0x0B2, 0x0B4, this, a_playAnim);
	}

	void Actor::Unk_B3()
	{
		RelocateVirtual<decltype(&Actor::Unk_B3)>(0x0B3, 0x0B5, this);
	}

	void Actor::Unk_B4()
	{
		RelocateVirtual<decltype(&Actor::Unk_B4)>(0x0B4, 0x0B6, this);
	}

	void Actor::SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_amount)
	{
		RelocateVirtual<decltype(&Actor::SetCrimeGoldValue)>(0x0B5, 0x0B7, this, a_faction, a_violent, a_amount);
	}

	void Actor::ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_amount)
	{
		RelocateVirtual<decltype(&Actor::ModCrimeGoldValue)>(0x0B6, 0x0B8, this, a_faction, a_violent, a_amount);
	}

	void Actor::RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_amount)
	{
		RelocateVirtual<decltype(&Actor::RemoveCrimeGoldValue)>(0x0B7, 0x0B9, this, a_faction, a_violent, a_amount);
	}

	std::uint32_t Actor::GetCrimeGoldValue(const TESFaction* a_faction) const
	{
		return RelocateVirtual<decltype(&Actor::GetCrimeGoldValue)>(0x0B8, 0x0BA, this, a_faction);
	}

	void Actor::GoToPrison(TESFaction* a_faction, bool a_removeInventory, bool a_realJail)
	{
		RelocateVirtual<decltype(&Actor::GoToPrison)>(0x0B9, 0x0BB, this, a_faction, a_removeInventory, a_realJail);
	}

	void Actor::ServePrisonTime()
	{
		RelocateVirtual<decltype(&Actor::ServePrisonTime)>(0x0BA, 0x0BC, this);
	}

	void Actor::PayFine(TESFaction* a_faction, bool a_goToJail, bool a_removeStolenItems)
	{
		RelocateVirtual<decltype(&Actor::PayFine)>(0x0BB, 0x0BD, this, a_faction, a_goToJail, a_removeStolenItems);
	}

	bool Actor::GetCannibal()
	{
		return RelocateVirtual<decltype(&Actor::GetCannibal)>(0x0BC, 0x0BE, this);
	}

	void Actor::SetCannibal(bool a_set)
	{
		RelocateVirtual<decltype(&Actor::SetCannibal)>(0x0BD, 0x0BF, this, a_set);
	}

	bool Actor::GetVampireFeed()
	{
		return RelocateVirtual<decltype(&Actor::GetVampireFeed)>(0x0BE, 0x0C0, this);
	}

	void Actor::SetVampireFeed(bool a_set)
	{
		RelocateVirtual<decltype(&Actor::SetVampireFeed)>(0x0BF, 0x0C1, this, a_set);
	}

	void Actor::InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture)
	{
		RelocateVirtual<decltype(&Actor::InitiateVampireFeedPackage)>(0x0C0, 0x0C2, this, a_target, a_furniture);
	}

	void Actor::InitiateCannibalPackage(Actor* a_target)
	{
		RelocateVirtual<decltype(&Actor::InitiateCannibalPackage)>(0x0C1, 0x0C3, this, a_target);
	}

	void Actor::GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset)
	{
		RelocateVirtual<decltype(&Actor::GetEyeVector)>(0x0C2, 0x0C4, this, a_origin, a_direction, a_includeCameraOffset);
	}

	void Actor::SetRefraction(bool a_enable, float a_refraction)
	{
		RelocateVirtual<decltype(&Actor::SetRefraction)>(0x0C3, 0x0C5, this, a_enable, a_refraction);
	}

	void Actor::Unk_C4()
	{
		RelocateVirtual<decltype(&Actor::Unk_C4)>(0x0C4, 0x0C6, this);
	}

	void Actor::Unk_C5()
	{
		RelocateVirtual<decltype(&Actor::Unk_C5)>(0x0C5, 0x0C7, this);
	}

	void Actor::Unk_C6()
	{
		RelocateVirtual<decltype(&Actor::Unk_C6)>(0x0C6, 0x0C8, this);
	}

	float Actor::GetAcrobatics() const
	{
		return RelocateVirtual<decltype(&Actor::GetAcrobatics)>(0x0C7, 0x0C9, this);
	}

	bhkCharacterController* Actor::Move(float a_arg2, const NiPoint3& a_position)
	{
		return RelocateVirtual<decltype(&Actor::Move)>(0x0C8, 0x0CA, this, a_arg2, a_position);
	}

	void Actor::Unk_C9()
	{
		RelocateVirtual<decltype(&Actor::Unk_C9)>(0x0C9, 0x0CB, this);
	}

	void Actor::OnArmorActorValueChanged()
	{
		RelocateVirtual<decltype(&Actor::OnArmorActorValueChanged)>(0x0CA, 0x0CC, this);
	}

	ObjectRefHandle Actor::DropObject(const TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, const NiPoint3* a_dropLoc, const NiPoint3* a_rotate)
	{
		return RelocateVirtual<decltype(&Actor::DropObject)>(0x0CB, 0x0CD, this, a_object, a_extraList, a_count, a_dropLoc, a_rotate);
	}

	void Actor::PickUpObject(TESObjectREFR* a_object, std::int32_t a_count, bool a_arg3, bool a_playSound)
	{
		RelocateVirtual<decltype(&Actor::PickUpObject)>(0x0CC, 0x0CE, this, a_object, a_count, a_arg3, a_playSound);
	}

	void Actor::AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped)
	{
		RelocateVirtual<decltype(&Actor::AttachArrow)>(0x0CD, 0x0CF, this, a_biped);
	}

	void Actor::DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped)
	{
		RelocateVirtual<decltype(&Actor::DetachArrow)>(0x0CE, 0x0D0, this, a_biped);
	}

	bool Actor::AddShout(TESShout* a_shout)
	{
		return RelocateVirtual<decltype(&Actor::AddShout)>(0x0CF, 0x0D1, this, a_shout);
	}

	void Actor::UnlockWord(TESWordOfPower* a_power)
	{
		RelocateVirtual<decltype(&Actor::UnlockWord)>(0x0D0, 0x0D2, this, a_power);
	}

	void Actor::Unk_D1()
	{
		RelocateVirtual<decltype(&Actor::Unk_D1)>(0x0D1, 0x0D3, this);
	}

	std::uint32_t Actor::UseAmmo(std::uint32_t a_shotCount)
	{
		return RelocateVirtual<decltype(&Actor::UseAmmo)>(0x0D2, 0x0D4, this, a_shotCount);
	}

	bool Actor::CalculateCachedOwnerIsInCombatantFaction() const
	{
		return RelocateVirtual<decltype(&Actor::CalculateCachedOwnerIsInCombatantFaction)>(0x0D3, 0x0D5, this);
	}

	CombatGroup* Actor::GetCombatGroup() const
	{
		return RelocateVirtual<decltype(&Actor::GetCombatGroup)>(0x0D4, 0x0D6, this);
	}

	void Actor::SetCombatGroup(CombatGroup* a_group)
	{
		RelocateVirtual<decltype(&Actor::SetCombatGroup)>(0x0D5, 0x0D7, this, a_group);
	}

	bool Actor::CheckValidTarget(TESObjectREFR& a_target)
	{
		return RelocateVirtual<decltype(&Actor::CheckValidTarget)>(0x0D6, 0x0D8, this, a_target);
	}

	bool Actor::InitiateTresPassPackage(TrespassPackage* a_trespassPackage)
	{
		return RelocateVirtual<decltype(&Actor::InitiateTresPassPackage)>(0x0D7, 0x0D9, this, a_trespassPackage);
	}

	void Actor::InitiateDialogue(Actor* a_target, PackageLocation* a_loc1, PackageLocation* a_loc2)
	{
		RelocateVirtual<decltype(&Actor::InitiateDialogue)>(0x0D8, 0x0DA, this, a_target, a_loc1, a_loc2);
	}

	void Actor::SetSize(float a_size)
	{
		RelocateVirtual<decltype(&Actor::SetSize)>(0x0D9, 0x0DB, this, a_size);
	}

	void Actor::EndDialogue()
	{
		RelocateVirtual<decltype(&Actor::EndDialogue)>(0x0DA, 0x0DC, this);
	}

	Actor* Actor::SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_activator)
	{
		return RelocateVirtual<decltype(&Actor::SetUpTalkingActivatorActor)>(0x0DB, 0x0DD, this, a_target, a_activator);
	}

	void Actor::InitiateSpectator(Actor* a_target)
	{
		RelocateVirtual<decltype(&Actor::InitiateSpectator)>(0x0DC, 0x0DE, this, a_target);
	}

	void Actor::InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runOnce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist)
	{
		RelocateVirtual<decltype(&Actor::InitiateFlee)>(0x0DD, 0x0DF, this, a_fleeRef, a_runOnce, a_knows, a_combatMode, a_cell, a_ref, a_fleeFromDist, a_fleeToDist);
	}

	void Actor::InitiateGetUpPackage()
	{
		RelocateVirtual<decltype(&Actor::InitiateGetUpPackage)>(0x0DE, 0x0E0, this);
	}

	void Actor::PutCreatedPackage(TESPackage* a_package, bool a_tempPackage, bool a_createdPackage, bool a_allowFromFurniture)
	{
		RelocateVirtual<decltype(&Actor::PutCreatedPackage)>(0x0DF, 0x0E1, this, a_package, a_tempPackage, a_createdPackage, a_allowFromFurniture);
	}

	void Actor::UpdateAlpha()
	{
		RelocateVirtual<decltype(&Actor::UpdateAlpha)>(0x0E0, 0x0E2, this);
	}

	void Actor::SetAlpha(float a_alpha)
	{
		RelocateVirtual<decltype(&Actor::SetAlpha)>(0x0E1, 0x0E3, this, a_alpha);
	}

	float Actor::GetAlpha()
	{
		return RelocateVirtual<decltype(&Actor::GetAlpha)>(0x0E2, 0x0E4, this);
	}

	bool Actor::IsInCombat() const
	{
		return RelocateVirtual<decltype(&Actor::IsInCombat)>(0x0E3, 0x0E5, this);
	}

	void Actor::UpdateCombat()
	{
		RelocateVirtual<decltype(&Actor::UpdateCombat)>(0x0E4, 0x0E6, this);
	}

	void Actor::StopCombat()
	{
		RelocateVirtual<decltype(&Actor::StopCombat)>(0x0E5, 0x0E7, this);
	}

	float Actor::CalcArmorRating()
	{
		return RelocateVirtual<decltype(&Actor::CalcArmorRating)>(0x0E6, 0x0E8, this);
	}

	float Actor::GetArmorBaseFactorSum()
	{
		return RelocateVirtual<decltype(&Actor::GetArmorBaseFactorSum)>(0x0E7, 0x0E9, this);
	}

	float Actor::CalcUnarmedDamage()
	{
		return RelocateVirtual<decltype(&Actor::CalcUnarmedDamage)>(0x0E8, 0x0EA, this);
	}

	void Actor::Unk_E9()
	{
		RelocateVirtual<decltype(&Actor::Unk_E9)>(0x0E9, 0x0EB, this);
	}

	void Actor::Unk_EA()
	{
		RelocateVirtual<decltype(&Actor::Unk_EA)>(0x0EA, 0x0EC, this);
	}

	float Actor::GetRunSpeed()
	{
		return RelocateVirtual<decltype(&Actor::GetRunSpeed)>(0x0EB, 0x0ED, this);
	}

	float Actor::GetJogSpeed()
	{
		return RelocateVirtual<decltype(&Actor::GetJogSpeed)>(0x0EC, 0x0EE, this);
	}

	float Actor::GetFastWalkSpeed()
	{
		return RelocateVirtual<decltype(&Actor::GetFastWalkSpeed)>(0x0ED, 0x0EF, this);
	}

	float Actor::GetWalkSpeed()
	{
		return RelocateVirtual<decltype(&Actor::GetWalkSpeed)>(0x0EE, 0x0F0, this);
	}

	void Actor::WeaponSwingCallBack()
	{
		RelocateVirtual<decltype(&Actor::WeaponSwingCallBack)>(0x0EF, 0x0F1, this);
	}

	void Actor::SetActorStartingPosition()
	{
		RelocateVirtual<decltype(&Actor::SetActorStartingPosition)>(0x0F0, 0x0F2, this);
	}

	bool Actor::MoveToHigh()
	{
		return RelocateVirtual<decltype(&Actor::MoveToHigh)>(0x0F1, 0x0F3, this);
	}

	bool Actor::MovetoLow()
	{
		return RelocateVirtual<decltype(&Actor::MovetoLow)>(0x0F2, 0x0F4, this);
	}

	bool Actor::MovetoMiddleLow()
	{
		return RelocateVirtual<decltype(&Actor::MovetoMiddleLow)>(0x0F3, 0x0F5, this);
	}

	bool Actor::MoveToMiddleHigh()
	{
		return RelocateVirtual<decltype(&Actor::MoveToMiddleHigh)>(0x0F4, 0x0F6, this);
	}

	bool Actor::HasBeenAttacked() const
	{
		return RelocateVirtual<decltype(&Actor::HasBeenAttacked)>(0x0F5, 0x0F7, this);
	}

	void Actor::SetBeenAttacked(bool a_set)
	{
		return RelocateVirtual<decltype(&Actor::SetBeenAttacked)>(0x0F6, 0x0F8, this, a_set);
	}

	void Actor::UseSkill(ActorValue a_av, float a_points, TESForm* a_arg3)
	{
		RelocateVirtual<decltype(&Actor::UseSkill)>(0x0F7, 0x0F9, this, a_av, a_points, a_arg3);
	}

	bool Actor::IsAtPoint(const NiPoint3& a_point, float a_radius, bool a_expandRadius, bool a_alwaysTestHeight)
	{
		return RelocateVirtual<decltype(&Actor::IsAtPoint)>(0x0F8, 0x0FA, this, a_point, a_radius, a_expandRadius, a_alwaysTestHeight);
	}

	bool Actor::IsInFaction(const TESFaction* faction) const
	{
		return RelocateVirtual<decltype(&Actor::IsInFaction)>(0x0F9, 0x0FB, this, faction);
	}

	void Actor::ForEachPerk(PerkEntryVisitor& a_visitor) const
	{
		RelocateVirtual<decltype(&Actor::ForEachPerk)>(0x0FA, 0x0FC, this, a_visitor);
	}

	void Actor::AddPerk(BGSPerk* a_perk, std::uint32_t a_rank)
	{
		RelocateVirtual<decltype(&Actor::AddPerk)>(0x0FB, 0x0FD, this, a_perk, a_rank);
	}

	void Actor::RemovePerk(BGSPerk* a_perk)
	{
		RelocateVirtual<decltype(&Actor::RemovePerk)>(0x0FC, 0x0FE, this, a_perk);
	}

	void Actor::ApplyTemporaryPerk(BGSPerk* a_perk)
	{
		RelocateVirtual<decltype(&Actor::ApplyTemporaryPerk)>(0x0FD, 0x0FF, this, a_perk);
	}

	void Actor::RemoveTemporaryPerk(BGSPerk* a_perk)
	{
		RelocateVirtual<decltype(&Actor::RemoveTemporaryPerk)>(0x0FE, 0x100, this, a_perk);
	}

	bool Actor::HasPerkEntries(EntryPoint a_entryType) const
	{
		return RelocateVirtual<decltype(&Actor::HasPerkEntries)>(0x0FF, 0x101, this, a_entryType);
	}

	void Actor::ForEachPerkEntry(EntryPoint a_entryType, PerkEntryVisitor& a_visitor) const
	{
		RelocateVirtual<decltype(&Actor::ForEachPerkEntry)>(0x100, 0x102, this, a_entryType, a_visitor);
	}

	void Actor::ApplyPerksFromBase()
	{
		RelocateVirtual<decltype(&Actor::ApplyPerksFromBase)>(0x101, 0x103, this);
	}

	void Actor::StartPowerAttackCoolDown()
	{
		RelocateVirtual<decltype(&Actor::StartPowerAttackCoolDown)>(0x102, 0x104, this);
	}

	bool Actor::IsPowerAttackCoolingDown() const
	{
		return RelocateVirtual<decltype(&Actor::IsPowerAttackCoolingDown)>(0x103, 0x105, this);
	}

	void Actor::HandleHealthDamage(Actor* a_attacker, float a_damage)
	{
		RelocateVirtual<decltype(&Actor::HandleHealthDamage)>(0x104, 0x106, this, a_attacker, a_damage);
	}

	void Actor::Unk_105()
	{
		RelocateVirtual<decltype(&Actor::Unk_105)>(0x105, 0x107, this);
	}

	void Actor::Unk_106()
	{
		RelocateVirtual<decltype(&Actor::Unk_106)>(0x106, 0x108, this);
	}

	bool Actor::QSpeakingDone() const
	{
		return RelocateVirtual<decltype(&Actor::QSpeakingDone)>(0x107, 0x109, this);
	}

	void Actor::SetSpeakingDone(bool a_set)
	{
		RelocateVirtual<decltype(&Actor::SetSpeakingDone)>(0x108, 0x10A, this, a_set);
	}

	void Actor::CreateMovementController()
	{
		RelocateVirtual<decltype(&Actor::CreateMovementController)>(0x109, 0x10B, this);
	}

	EmotionType Actor::GetEmotionType()
	{
		return RelocateVirtual<decltype(&Actor::GetEmotionType)>(0x10A, 0x10C, this);
	}

	void Actor::SetEmotionType(EmotionType a_emotionType)
	{
		RelocateVirtual<decltype(&Actor::SetEmotionType)>(0x10B, 0x10D, this, a_emotionType);
	}

	std::uint32_t Actor::GetEmotionValue()
	{
		return RelocateVirtual<decltype(&Actor::GetEmotionValue)>(0x10C, 0x10E, this);
	}

	void Actor::SetEmotionValue(std::uint32_t a_emotionValue)
	{
		RelocateVirtual<decltype(&Actor::SetEmotionValue)>(0x10D, 0x10F, this, a_emotionValue);
	}

	void Actor::KillImpl(Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant)
	{
		RelocateVirtual<decltype(&Actor::KillImpl)>(0x10E, 0x110, this, a_attacker, a_damage, a_sendEvent, a_ragdollInstant);
	}

	bool Actor::DrinkPotion(AlchemyItem* a_potion, ExtraDataList* a_extralist)
	{
		return RelocateVirtual<decltype(&Actor::DrinkPotion)>(0x10F, 0x111, this, a_potion, a_extralist);
	}

	bool Actor::CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason)
	{
		return RelocateVirtual<decltype(&Actor::CheckCast)>(0x110, 0x112, this, a_spell, a_dualCast, a_reason);
	}

	void Actor::CheckTempModifiers()
	{
		RelocateVirtual<decltype(&Actor::CheckTempModifiers)>(0x111, 0x113, this);
	}

	std::int32_t Actor::GetCurrentShoutLevel()
	{
		return RelocateVirtual<decltype(&Actor::GetCurrentShoutLevel)>(0x112, 0x114, this);
	}

	void Actor::SetLastRiddenMount(ActorHandle a_mount)
	{
		RelocateVirtual<decltype(&Actor::SetLastRiddenMount)>(0x113, 0x115, this, a_mount);
	}

	ActorHandle Actor::QLastRiddenMount() const
	{
		return RelocateVirtual<decltype(&Actor::QLastRiddenMount)>(0x114, 0x116, this);
	}

	bool Actor::CalculateCachedOwnerIsUndead() const
	{
		return RelocateVirtual<decltype(&Actor::CalculateCachedOwnerIsUndead)>(0x115, 0x117, this);
	}

	bool Actor::CalculateCachedOwnerIsNPC() const
	{
		return RelocateVirtual<decltype(&Actor::CalculateCachedOwnerIsNPC)>(0x116, 0x118, this);
	}

	void Actor::Unk_117()
	{
		RelocateVirtual<decltype(&Actor::Unk_117)>(0x117, 0x119, this);
	}

	void Actor::InitValues()
	{
		RelocateVirtual<decltype(&Actor::InitValues)>(0x118, 0x11A, this);
	}

	const BSFixedString& Actor::GetResponseString() const
	{
		return RelocateVirtual<decltype(&Actor::GetResponseString)>(0x119, 0x11B, this);
	}

	void Actor::ModifyMovementData(float a_delta, NiPoint3& a_arg3, NiPoint3& a_arg4)
	{
		RelocateVirtual<decltype(&Actor::ModifyMovementData)>(0x11A, 0x11C, this, a_delta, a_arg3, a_arg4);
	}

	void Actor::UpdateCombatControllerSettings()
	{
		RelocateVirtual<decltype(&Actor::UpdateCombatControllerSettings)>(0x11B, 0x11D, this);
	}

	void Actor::UpdateFadeSettings(bhkCharacterController* a_controller)
	{
		RelocateVirtual<decltype(&Actor::UpdateFadeSettings)>(0x11C, 0x11E, this, a_controller);
	}

	bool Actor::ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, float a_delta, ActorMotionFeedbackOutput& a_output)
	{
		return RelocateVirtual<decltype(&Actor::ComputeMotionFeedbackSpeedAndDirection)>(0x11D, 0x11F, this, a_data, a_delta, a_output);
	}

	bool Actor::UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_output)
	{
		return RelocateVirtual<decltype(&Actor::UpdateFeedbackGraphSpeedAndDirection)>(0x11E, 0x120, this, a_output);
	}

	void Actor::UpdateActor3DPosition()
	{
		RelocateVirtual<decltype(&Actor::UpdateActor3DPosition)>(0x11F, 0x121, this);
	}

	void Actor::PrecacheData()
	{
		RelocateVirtual<decltype(&Actor::PrecacheData)>(0x120, 0x122, this);
	}

	void Actor::WornArmorChanged()
	{
		RelocateVirtual<decltype(&Actor::WornArmorChanged)>(0x121, 0x123, this);
	}

	void Actor::ProcessTracking(float a_delta, NiAVObject* a_obj3D)
	{
		RelocateVirtual<decltype(&Actor::ProcessTracking)>(0x122, 0x124, this, a_delta, a_obj3D);
	}

	void Actor::Unk_123()
	{
		RelocateVirtual<decltype(&Actor::Unk_123)>(0x123, 0x125, this);
	}

	void Actor::CreateActorMover()
	{
		RelocateVirtual<decltype(&Actor::CreateActorMover)>(0x124, 0x126, this);
	}

	void Actor::DestroyActorMover()
	{
		RelocateVirtual<decltype(&Actor::DestroyActorMover)>(0x125, 0x127, this);
	}

	bool Actor::ShouldRespondToActorCollision(const MovementMessageActorCollision& a_msg, const ActorHandlePtr& a_target)
	{
		return RelocateVirtual<decltype(&Actor::ShouldRespondToActorCollision)>(0x126, 0x128, this, a_msg, a_target);
	}

	float Actor::CheckClampDamageModifier(ActorValue a_av, float a_delta)
	{
		return RelocateVirtual<decltype(&Actor::CheckClampDamageModifier)>(0x127, 0x129, this, a_av, a_delta);
	}
#endif
}
