#include "RE/T/TESObjectREFR.h"

#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BGSKeyword.h"
#include "RE/B/BSFixedString.h"
#include "RE/E/ExtraCharge.h"
#include "RE/E/ExtraContainerChanges.h"
#include "RE/E/ExtraDroppedItemList.h"
#include "RE/E/ExtraEnchantment.h"
#include "RE/E/ExtraFlags.h"
#include "RE/E/ExtraLock.h"
#include "RE/E/ExtraOwnership.h"
#include "RE/E/ExtraReferenceHandle.h"
#include "RE/E/ExtraTextDisplayData.h"
#include "RE/F/FormTraits.h"
#include "RE/I/InventoryChanges.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/M/Misc.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiControllerManager.h"
#include "RE/N/NiControllerSequence.h"
#include "RE/N/NiMath.h"
#include "RE/N/NiTimeController.h"
#include "RE/T/TESContainer.h"
#include "RE/T/TESDataHandler.h"
#include "RE/T/TESEnchantableForm.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "SKSE/Logger.h"

namespace RE
{
	NiPointer<TESObjectREFR> TESObjectREFR::LookupByHandle(RefHandle a_refHandle)
	{
		NiPointer<TESObjectREFR> ref;
		LookupReferenceByHandle(a_refHandle, ref);
		return ref;
	}

	bool TESObjectREFR::LookupByHandle(RefHandle a_refHandle, NiPointer<TESObjectREFR>& a_refrOut)
	{
		return LookupReferenceByHandle(a_refHandle, a_refrOut);
	}

	TESObjectREFR* TESObjectREFR::FindReferenceFor3D(NiAVObject* a_object3D)
	{
		using func_t = decltype(&TESObjectREFR::FindReferenceFor3D);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::FindReferenceFor3D };
		return func(a_object3D);
	}

	ObjectRefHandle TESObjectREFR::CreateRefHandle()
	{
		return GetHandle();
	}

	void TESObjectREFR::DoTrap(TrapData& a_data)
	{
		return DoTrap1(a_data);
	}

	void TESObjectREFR::DoTrap(TrapEntry* a_trap, TargetEntry* a_target)
	{
		return DoTrap2(a_trap, a_target);
	}

	NiAVObject* TESObjectREFR::Get3D() const
	{
		return Get3D2();
	}

	NiAVObject* TESObjectREFR::Get3D(bool a_firstPerson) const
	{
		return Get3D1(a_firstPerson);
	}

	TESNPC* TESObjectREFR::GetActorOwner()
	{
		auto xOwnership = extraList.GetByType<ExtraOwnership>();
		if (xOwnership && xOwnership->owner && xOwnership->owner->Is(FormType::NPC)) {
			return static_cast<TESNPC*>(xOwnership->owner);
		} else {
			return nullptr;
		}
	}

	NiPoint3 TESObjectREFR::GetAngle() const
	{
		return data.angle;
	}

	float TESObjectREFR::GetAngleX() const
	{
		return data.angle.x;
	}

	float TESObjectREFR::GetAngleY() const
	{
		return data.angle.y;
	}

	float TESObjectREFR::GetAngleZ() const
	{
		return data.angle.z;
	}

	float TESObjectREFR::GetBaseHeight() const
	{
		auto height = static_cast<float>(refScale) / 100.0F;
		auto obj = GetObjectReference();
		auto npc = obj ? obj->As<TESNPC>() : nullptr;
		if (npc) {
			height *= npc->GetHeight();
		}
		return height;
	}

	TESBoundObject* TESObjectREFR::GetBaseObject()
	{
		return data.objectReference;
	}

	const TESBoundObject* TESObjectREFR::GetBaseObject() const
	{
		return data.objectReference;
	}

	const BSTSmartPointer<BipedAnim>& TESObjectREFR::GetBiped() const
	{
		return GetBiped2();
	}

	const BSTSmartPointer<BipedAnim>& TESObjectREFR::GetBiped(bool a_firstPerson) const
	{
		return GetBiped1(a_firstPerson);
	}

	TESContainer* TESObjectREFR::GetContainer() const
	{
		auto obj = GetObjectReference();
		return obj ? obj->As<TESContainer>() : nullptr;
	}

	BGSLocation* TESObjectREFR::GetCurrentLocation() const
	{
		using func_t = decltype(&TESObjectREFR::GetCurrentLocation);
		REL::Relocation<func_t> func{ REL::RelocationID(19385, 19812) };
		return func(this);
	}

	const char* TESObjectREFR::GetDisplayFullName()
	{
		using func_t = decltype(&TESObjectREFR::GetDisplayFullName);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::GetDisplayFullName };
		return func(this);
	}

	auto TESObjectREFR::GetDroppedInventory()
		-> InventoryDropMap
	{
		return GetDroppedInventory([]([[maybe_unused]] TESBoundObject&) -> bool {
			return true;
		});
	}

	auto TESObjectREFR::GetDroppedInventory(std::function<bool(TESBoundObject&)> a_filter)
		-> InventoryDropMap
	{
		using container_t = InventoryDropMap::mapped_type::second_type;

		InventoryDropMap results;

		auto xDrop = extraList.GetByType<ExtraDroppedItemList>();
		if (!xDrop) {
			return results;
		}

		for (auto& handle : xDrop->droppedItemList) {
			auto ref = handle.get();
			if (!ref) {
				continue;
			}

			auto object = ref->GetObjectReference();
			if (!object || !a_filter(*object)) {
				continue;
			}

			auto count = ref->extraList.GetCount();
			auto it = results.find(object);
			if (it != results.end()) {
				it->second.first += count;
				it->second.second.push_back(handle);
			} else {
				auto mapped = std::make_pair(count, container_t());
				mapped.second.push_back(handle);
				auto insIt = results.emplace(object, std::move(mapped));
				assert(insIt.second);
			}
		}

		return results;
	}

	BGSLocation* TESObjectREFR::GetEditorLocation() const
	{
		return GetEditorLocation1();
	}

	bool TESObjectREFR::GetEditorLocation(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback)
	{
		return GetEditorLocation2(a_outPos, a_outRot, a_outWorldOrCell, a_fallback);
	}

	std::optional<double> TESObjectREFR::GetEnchantmentCharge() const
	{
		std::optional<double> result;
		auto                  obj = GetObjectReference();
		auto                  ench = obj ? obj->As<TESEnchantableForm>() : nullptr;
		if (ench && ench->formEnchanting && ench->amountofEnchantment != 0) {
			result.emplace(100.0);
		}

		auto xCharge = extraList.GetByType<ExtraCharge>();
		auto xEnch = extraList.GetByType<ExtraEnchantment>();
		if (xEnch && xEnch->enchantment && xEnch->charge != 0) {
			if (xCharge) {
				result.emplace((static_cast<double>(xCharge->charge) /
								   static_cast<double>(xEnch->charge)) *
							   100.0);
			} else {
				result.emplace(100.0);
			}
		} else if (xCharge && ench && ench->formEnchanting && ench->amountofEnchantment != 0) {
			result.emplace((static_cast<double>(xCharge->charge) /
							   static_cast<double>(ench->amountofEnchantment)) *
						   100.0);
		}

		return result;
	}

	TESFaction* TESObjectREFR::GetFactionOwner()
	{
		auto xOwnership = extraList.GetByType<ExtraOwnership>();
		if (xOwnership && xOwnership->owner && xOwnership->owner->Is(FormType::Faction)) {
			return static_cast<TESFaction*>(xOwnership->owner);
		} else {
			return nullptr;
		}
	}

	ObjectRefHandle TESObjectREFR::GetHandle()
	{
		return ObjectRefHandle(this);
	}

	float TESObjectREFR::GetHeadingAngle(const NiPoint3& a_pos, bool a_abs)
	{
		float theta = NiFastATan2(a_pos.x - GetPositionX(), a_pos.y - GetPositionY());
		float heading = rad_to_deg(theta - GetAngleZ());

		if (heading < -180.0f) {
			heading += 360.0f;
		}

		if (heading > 180.0f) {
			heading -= 360.0f;
		}

		return a_abs ? NiAbs(heading) : heading;
	}

	float TESObjectREFR::GetHeight() const
	{
		const auto min = GetBoundMin();
		const auto max = GetBoundMax();
		const auto diff = max.z - min.z;
		const auto height = GetBaseHeight() * diff;

		return height;
	}

	auto TESObjectREFR::GetInventory()
		-> InventoryItemMap
	{
		return GetInventory([](TESBoundObject&) { return true; });
	}

	auto TESObjectREFR::GetInventory(std::function<bool(TESBoundObject&)> a_filter)
		-> InventoryItemMap
	{
		InventoryItemMap results;

		auto invChanges = GetInventoryChanges();
		if (invChanges && invChanges->entryList) {
			for (auto& entry : *invChanges->entryList) {
				if (entry && entry->object && a_filter(*entry->object)) {
					[[maybe_unused]] auto it =
						results.emplace(
							entry->object,
							std::make_pair(
								entry->countDelta,
								std::make_unique<InventoryEntryData>(*entry)));
					assert(it.second);
				}
			}
		}

		auto container = GetContainer();
		if (container) {
			const auto ignore = [&](TESBoundObject* a_object) {
				const auto it = results.find(a_object);
				const auto entryData =
					it != results.end() ?
                        it->second.second.get() :
                        nullptr;
				return entryData ? entryData->IsLeveled() : false;
			};

			container->ForEachContainerObject([&](ContainerObject& a_entry) {
				auto obj = a_entry.obj;
				if (obj && !ignore(obj) && a_filter(*obj)) {
					auto it = results.find(obj);
					if (it == results.end()) {
						[[maybe_unused]] auto insIt =
							results.emplace(
								obj,
								std::make_pair(
									a_entry.count,
									std::make_unique<InventoryEntryData>(obj, 0)));
						assert(insIt.second);
					} else {
						it->second.first += a_entry.count;
					}
				}
				return true;
			});
		}

		return results;
	}

	std::int32_t TESObjectREFR::GetInventoryCount()
	{
		auto         counts = GetInventoryCounts();
		std::int32_t total = 0;
		for (auto& elem : counts) {
			total += elem.second;
		}
		return total;
	}

	auto TESObjectREFR::GetInventoryCounts()
		-> InventoryCountMap
	{
		return GetInventoryCounts([](TESBoundObject&) { return true; });
	}

	auto TESObjectREFR::GetInventoryCounts(std::function<bool(TESBoundObject&)> a_filter)
		-> InventoryCountMap
	{
		auto              itemMap = GetInventory(std::move(a_filter));
		InventoryCountMap results;
		for (const auto& [key, value] : itemMap) {
			results[key] = value.first;
		}
		return results;
	}

	InventoryChanges* TESObjectREFR::GetInventoryChanges()
	{
		if (!extraList.HasType<ExtraContainerChanges>()) {
			if (!InitInventoryIfRequired()) {
				ForceInitInventoryChanges();
			}
		}

		auto xContChanges = extraList.GetByType<ExtraContainerChanges>();
		return xContChanges ? xContChanges->changes : nullptr;
	}

	TESObjectREFR* TESObjectREFR::GetLinkedRef(BGSKeyword* a_keyword)
	{
		return extraList.GetLinkedRef(a_keyword);
	}

	REFR_LOCK* TESObjectREFR::GetLock() const
	{
		using func_t = decltype(&TESObjectREFR::GetLock);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::GetLock };
		return func(this);
	}

	LOCK_LEVEL TESObjectREFR::GetLockLevel() const
	{
		auto state = GetLock();
		return state ? state->GetLockLevel(this) : LOCK_LEVEL::kUnlocked;
	}

	const char* TESObjectREFR::GetName() const
	{
		auto obj = GetObjectReference();
		return obj ? obj->GetName() : "";
	}

	NiAVObject* TESObjectREFR::GetNodeByName(const BSFixedString& a_nodeName)
	{
		auto node = Get3D();
		return node ? node->GetObjectByName(a_nodeName) : nullptr;
	}

	TESForm* TESObjectREFR::GetOwner() const
	{
		using func_t = decltype(&TESObjectREFR::GetOwner);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::GetOwner };
		return func(this);
	}

	NiControllerSequence* TESObjectREFR::GetSequence(stl::zstring a_name) const
	{
		auto node = Get3D();
		if (!node) {
			return nullptr;
		}

		auto controller = node->GetControllers();
		if (!controller) {
			return nullptr;
		}

		auto manager = controller->AsNiControllerManager();
		return manager ? manager->GetSequenceByName(a_name) : nullptr;
	}

	std::uint32_t TESObjectREFR::GetStealValue(const InventoryEntryData* a_entryData, std::uint32_t a_numItems, bool a_useMult) const
	{
		using func_t = decltype(&TESObjectREFR::GetStealValue);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::GetStealValue };
		return func(this, a_entryData, a_numItems, a_useMult);
	}

	void TESObjectREFR::GetTransform(NiTransform& a_transform) const
	{
		using func_t = decltype(&TESObjectREFR::GetTransform);
		REL::Relocation<func_t> func{ REL::RelocationID(19326, 19753) };
		return func(this, a_transform);
	}

	float TESObjectREFR::GetWaterHeight() const
	{
		float waterHeight = -NI_INFINITY;

		if (loadedData) {
			waterHeight = loadedData->relevantWaterHeight;
			if (waterHeight != -NI_INFINITY) {
				return waterHeight;
			}
		}

		return parentCell ? parentCell->GetExteriorWaterHeight() : waterHeight;
	}

	float TESObjectREFR::GetWeight() const
	{
		auto obj = GetObjectReference();
		return obj ? obj->GetWeight() : 0.0F;
	}

	float TESObjectREFR::GetWeightInContainer()
	{
		using func_t = decltype(&TESObjectREFR::GetWeightInContainer);
		REL::Relocation<func_t> func{ REL::RelocationID(19277, 19703) };
		return func(this);
	}

	TESWorldSpace* TESObjectREFR::GetWorldspace() const
	{
		auto cell = parentCell;
		if (!cell) {
			cell = GetSaveParentCell();
		}

		if (cell && cell->IsExteriorCell()) {
			return cell->worldSpace;
		} else {
			return nullptr;
		}
	}

	bool TESObjectREFR::HasCollision() const
	{
		return (formFlags & RecordFlags::kCollisionsDisabled) == 0;
	}

	bool TESObjectREFR::HasContainer() const
	{
		return GetContainer() != nullptr;
	}

	bool TESObjectREFR::HasKeyword(const BGSKeyword* a_keyword) const
	{
		return HasKeywordHelper(a_keyword);
	}

	bool TESObjectREFR::HasQuestObject() const
	{
		using func_t = decltype(&TESObjectREFR::HasQuestObject);
		REL::Relocation<func_t> func{ REL::RelocationID(19201, 19627) };
		return func(this);
	}

	void TESObjectREFR::InitChildActivates(TESObjectREFR* a_actionRef)
	{
		using func_t = decltype(&TESObjectREFR::InitChildActivates);
		REL::Relocation<func_t> func{ REL::RelocationID(19857, 20264) };
		return func(this, a_actionRef);
	}

	bool TESObjectREFR::InitInventoryIfRequired(bool a_ignoreContainerExtraData)
	{
		using func_t = decltype(&TESObjectREFR::InitInventoryIfRequired);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::InitInventoryIfRequired };
		return func(this, a_ignoreContainerExtraData);
	}

	ModelReferenceEffect* TESObjectREFR::InstantiateHitArt(BGSArtObject* a_art, float a_dur, TESObjectREFR* a_facingRef, bool a_faceTarget, bool a_attachToCamera, NiAVObject* a_attachNode, bool a_interfaceEffect)
	{
		using func_t = decltype(&TESObjectREFR::InstantiateHitArt);
		REL::Relocation<func_t> func{ REL::RelocationID(22289, 22769) };
		return func(this, a_art, a_dur, a_facingRef, a_faceTarget, a_attachToCamera, a_attachNode, a_interfaceEffect);
	}

	ShaderReferenceEffect* TESObjectREFR::InstantiateHitShader(TESEffectShader* a_shader, float a_dur, TESObjectREFR* a_facingRef, bool a_faceTarget, bool a_attachToCamera, NiAVObject* a_attachNode, bool a_interfaceEffect)
	{
		using func_t = decltype(&TESObjectREFR::InstantiateHitShader);
		REL::Relocation<func_t> func{ REL::RelocationID(19446, 19872) };
		return func(this, a_shader, a_dur, a_facingRef, a_faceTarget, a_attachToCamera, a_attachNode, a_interfaceEffect);
	}

	bool TESObjectREFR::Is3DLoaded() const
	{
		return Get3D() != nullptr;
	}

	bool TESObjectREFR::IsActivationBlocked() const
	{
		auto xFlags = extraList.GetByType<ExtraFlags>();
		return xFlags && xFlags->IsActivationBlocked();
	}

	bool TESObjectREFR::IsAnOwner(const Actor* a_testOwner, bool a_useFaction, bool a_requiresOwner) const
	{
		using func_t = decltype(&TESObjectREFR::IsAnOwner);
		REL::Relocation<func_t> func{ REL::RelocationID(19805, 20210) };
		return func(this, a_testOwner, a_useFaction, a_requiresOwner);
	}

	bool TESObjectREFR::IsCrimeToActivate()
	{
		using func_t = decltype(&TESObjectREFR::IsCrimeToActivate);
		REL::Relocation<func_t> func{ REL::RelocationID(19400, 19827) };
		return func(this);
	}

	bool TESObjectREFR::IsDisabled() const
	{
		return (formFlags & RecordFlags::kInitiallyDisabled) != 0;
	}

	bool TESObjectREFR::IsEnchanted() const
	{
		auto xEnch = extraList.GetByType<ExtraEnchantment>();
		if (xEnch && xEnch->enchantment) {
			return true;
		}

		auto obj = GetObjectReference();
		if (obj) {
			auto ench = obj->As<TESEnchantableForm>();
			if (ench && ench->formEnchanting) {
				return true;
			}
		}

		return false;
	}

	bool TESObjectREFR::IsHorse() const
	{
		auto dobj = BGSDefaultObjectManager::GetSingleton();
		if (!dobj) {
			return false;
		}

		auto keyword = dobj->GetObject<BGSKeyword>(DefaultObjectID::kKeywordHorse);
		return keyword && *keyword ? HasKeyword(*keyword) : false;
	}

	bool TESObjectREFR::IsInitiallyDisabled() const
	{
		return (formFlags & RecordFlags::kInitiallyDisabled) != 0;
	}

	bool TESObjectREFR::IsInWater() const
	{
		return GetWaterHeight() > GetPositionZ();
	}

	bool TESObjectREFR::IsLocked() const
	{
		return GetLockLevel() != LOCK_LEVEL::kUnlocked;
	}

	bool TESObjectREFR::IsMarkedForDeletion() const
	{
		return (formFlags & RecordFlags::kDeleted) != 0;
	}

	bool TESObjectREFR::IsOffLimits()
	{
		return IsCrimeToActivate();
	}

	void TESObjectREFR::MoveTo(TESObjectREFR* a_target)
	{
		assert(a_target);

		auto handle = a_target->GetHandle();
		MoveTo_Impl(handle, a_target->GetParentCell(), a_target->GetWorldspace(), a_target->GetPosition(), a_target->data.angle);
	}

	bool TESObjectREFR::MoveToNode(TESObjectREFR* a_target, const BSFixedString& a_nodeName)
	{
		assert(a_target);
		auto node = a_target->Get3D();
		if (!node) {
			SKSE::log::debug("Cannot move the target because it does not have 3D");
			return false;
		}

		auto object = node->GetObjectByName(a_nodeName);
		if (!object) {
			SKSE::log::debug("Target does not have a node named {}", a_nodeName.c_str());
			return false;
		}

		return MoveToNode(a_target, object);
	}

	bool TESObjectREFR::MoveToNode(TESObjectREFR* a_target, NiAVObject* a_node)
	{
		assert(a_target && a_node);
		auto&    position = a_node->world.translate;
		NiPoint3 rotation;
		a_node->world.rotate.ToEulerAnglesXYZ(rotation);
		auto handle = a_target->GetHandle();
		MoveTo_Impl(handle, a_target->GetParentCell(), GetWorldspace(), position, rotation);
		return true;
	}

	NiPointer<TESObjectREFR> TESObjectREFR::PlaceObjectAtMe(TESBoundObject* a_baseToPlace, bool a_forcePersist) const
	{
		const auto handle = TESDataHandler::GetSingleton()->CreateReferenceAtLocation(a_baseToPlace, GetPosition(), GetAngle(), GetParentCell(), GetWorldspace(), nullptr, nullptr, ObjectRefHandle(), a_forcePersist, true);
		return handle.get();
	}

	void TESObjectREFR::PlayAnimation(stl::zstring a_from, stl::zstring a_to)
	{
		auto node = Get3D();
		if (!node) {
			return;
		}

		auto controller = node->GetControllers();
		if (!controller) {
			return;
		}

		auto manager = controller->AsNiControllerManager();
		if (!manager) {
			return;
		}

		auto fromSeq = manager->GetSequenceByName(a_from);
		auto toSeq = manager->GetSequenceByName(a_to);
		if (!fromSeq || !toSeq) {
			return;
		}

		PlayAnimation(manager, toSeq, fromSeq);
	}

	void TESObjectREFR::PlayAnimation(NiControllerManager* a_manager, NiControllerSequence* a_toSeq, NiControllerSequence* a_fromSeq)
	{
		PlayAnimation_Impl(a_manager, a_toSeq, a_fromSeq);
	}

	void TESObjectREFR::SetActivationBlocked(bool a_blocked)
	{
		extraList.SetExtraFlags(ExtraFlags::Flag::kBlockActivate, a_blocked);
	}

	void TESObjectREFR::SetCollision(bool a_enable)
	{
		if (a_enable) {
			formFlags &= ~RecordFlags::kCollisionsDisabled;
		} else {
			formFlags |= RecordFlags::kCollisionsDisabled;
		}
	}

	bool TESObjectREFR::SetDisplayName(const BSFixedString& a_name, bool a_force)
	{
		bool renamed = false;

		auto xTextData = extraList.GetByType<ExtraTextDisplayData>();
		if (xTextData) {
			bool inUse = xTextData->displayNameText || xTextData->ownerQuest;
			if (inUse && a_force) {
				xTextData->displayNameText = nullptr;
				xTextData->ownerQuest = nullptr;
			}
			renamed = !inUse || a_force;
			xTextData->SetName(a_name.c_str());
		} else {
			xTextData = new ExtraTextDisplayData(a_name.c_str());
			extraList.Add(xTextData);
			renamed = true;
		}

		return renamed;
	}

	bool TESObjectREFR::SetMotionType(MotionType a_motionType, bool a_allowActivate)
	{
		auto node = Get3D();
		if (!node) {
			SKSE::log::debug("Target does not have 3D");
			return false;
		}

		auto result = node->SetMotionType(static_cast<std::uint32_t>(a_motionType), true, false, a_allowActivate);
		AddChange(ChangeFlags::kHavokMoved);
		return result;
	}

	void TESObjectREFR::SetPosition(float a_x, float a_y, float a_z)
	{
		return SetPosition(NiPoint3(a_x, a_y, a_z));
	}

	void TESObjectREFR::SetPosition(NiPoint3 a_pos)
	{
		MoveTo_Impl(ObjectRefHandle(), GetParentCell(), GetWorldspace(), a_pos, data.angle);
	}

	InventoryChanges* TESObjectREFR::ForceInitInventoryChanges()
	{
		auto changes = MakeInventoryChanges();
		if (changes) {
			changes->InitLeveledItems();
			changes->InitFromContainerExtra();
			changes->InitScripts();
		}
		return changes;
	}

	InventoryChanges* TESObjectREFR::MakeInventoryChanges()
	{
		using func_t = decltype(&TESObjectREFR::MakeInventoryChanges);
		REL::Relocation<func_t> func{ REL::RelocationID(15802, 16040) };
		return func(this);
	}

	void TESObjectREFR::MoveTo_Impl(const ObjectRefHandle& a_targetHandle, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, const NiPoint3& a_position, const NiPoint3& a_rotation)
	{
		using func_t = decltype(&TESObjectREFR::MoveTo_Impl);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::MoveTo };
		return func(this, a_targetHandle, a_targetCell, a_selfWorldSpace, a_position, a_rotation);
	}

	void TESObjectREFR::PlayAnimation_Impl(NiControllerManager* a_manager, NiControllerSequence* a_toSeq, NiControllerSequence* a_fromSeq, bool a_arg4)
	{
		using func_t = decltype(&TESObjectREFR::PlayAnimation_Impl);
		REL::Relocation<func_t> func{ Offset::TESObjectREFR::PlayAnimation };
		return func(this, a_manager, a_toSeq, a_fromSeq, a_arg4);
	}

	void TESObjectREFR::SetObjectReference(TESBoundObject* a_object)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::SetObjectReference)>(0x84, 0x85, this, a_object);
	}

	void TESObjectREFR::MoveHavok(bool a_forceRec)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::MoveHavok)>(0x85, 0x86, this, a_forceRec);
	}

	void TESObjectREFR::GetLinearVelocity(NiPoint3& a_velocity) const
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::GetLinearVelocity)>(0x86, 0x87, this, a_velocity);
	}

	void TESObjectREFR::SetActionComplete(bool a_set)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::SetActionComplete)>(0x87, 0x88, this, a_set);
	}

	void TESObjectREFR::SetMovementComplete(bool a_set)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::SetMovementComplete)>(0x88, 0x89, this, a_set);
	}

	void TESObjectREFR::Disable()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Disable)>(0x89, 0x8A, this);
	}

	void TESObjectREFR::ResetInventory(bool a_leveledOnly)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::ResetInventory)>(0x8A, 0x8B, this, a_leveledOnly);
	}

	void TESObjectREFR::Unk_8B()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_8B)>(0x8B, 0x8C, this);
	}

	void TESObjectREFR::Unk_8C()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_8C)>(0x8C, 0x8D, this);
	}

	NiAVObject* TESObjectREFR::GetCurrent3D() const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::GetCurrent3D)>(0x8D, 0x8E, this);
	}

	Explosion* TESObjectREFR::AsExplosion()
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::AsExplosion)>(0x8E, 0x8F, this);
	}

	Projectile* TESObjectREFR::AsProjectile()
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::AsProjectile)>(0x8F, 0x90, this);
	}

	bool TESObjectREFR::OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::OnAddCellPerformQueueReference)>(0x90, 0x91, this, a_cell);
	}

	void TESObjectREFR::DoMoveToHigh()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::DoMoveToHigh)>(0x91, 0x92, this);
	}

	void TESObjectREFR::TryMoveToMiddleLow()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::TryMoveToMiddleLow)>(0x92, 0x93, this);
	}

	bool TESObjectREFR::TryChangeSkyCellActorsProcessLevel()
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::TryChangeSkyCellActorsProcessLevel)>(0x93, 0x94, this);
	}

	void TESObjectREFR::Unk_94()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_94)>(0x94, 0x95, this);
	}

	void TESObjectREFR::Unk_95()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_95)>(0x95, 0x96, this);
	}

	void TESObjectREFR::Unk_96()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_96)>(0x96, 0x97, this);
	}

	TESObjectCELL* TESObjectREFR::GetSaveParentCell() const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::GetSaveParentCell)>(0x97, 0x98, this);
	}

	void TESObjectREFR::SetParentCell(TESObjectCELL* a_cell)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::SetParentCell)>(0x98, 0x99, this, a_cell);
	}

	bool TESObjectREFR::IsDead(bool a_notEssential) const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::IsDead)>(0x99, 0x9A, this, a_notEssential);
	}

	BSAnimNoteReceiver* TESObjectREFR::CreateAnimNoteReceiver()
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::CreateAnimNoteReceiver)>(0x9A, 0x9B, this);
	}

	BSAnimNoteReceiver* TESObjectREFR::GetAnimNoteReceiver()
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::GetAnimNoteReceiver)>(0x9B, 0x9C, this);
	}

	bool TESObjectREFR::ProcessInWater(hkpCollidable* a_collidable, float a_waterHeight, float a_deltaTime)
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::ProcessInWater)>(0x9C, 0x9D, this, a_collidable, a_waterHeight, a_deltaTime);
	}

	void TESObjectREFR::Unk_9D()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_9D)>(0x9D, 0x9E, this);
	}

	TESAmmo* TESObjectREFR::GetCurrentAmmo() const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::GetCurrentAmmo)>(0x9E, 0x9F, this);
	}

	BGSDecalGroup* TESObjectREFR::GetDecalGroup() const
	{
		return REL::RelocateVirtual<decltype(&TESObjectREFR::GetDecalGroup)>(0x9F, 0xA0, this);
	}

	void TESObjectREFR::Unk_A0()
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::Unk_A0)>(0xA0, 0xA1, this);
	}

	void TESObjectREFR::UnequipItem(std::uint64_t a_arg1, TESBoundObject* a_object)
	{
		REL::RelocateVirtual<decltype(&TESObjectREFR::UnequipItem)>(0xA1, 0xA2, this, a_arg1, a_object);
	}
}
