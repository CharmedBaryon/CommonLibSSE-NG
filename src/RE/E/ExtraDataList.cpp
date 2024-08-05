#include "RE/E/ExtraDataList.h"

#include "RE/B/BGSKeyword.h"
#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraAshPileRef.h"
#include "RE/E/ExtraCount.h"
#include "RE/E/ExtraEncounterZone.h"
#include "RE/E/ExtraHealth.h"
#include "RE/E/ExtraLinkedRef.h"
#include "RE/E/ExtraMissingLinkedRefIDs.h"
#include "RE/E/ExtraOwnership.h"
#include "RE/E/ExtraReferenceHandle.h"
#include "RE/E/ExtraSoul.h"
#include "RE/E/ExtraTeleport.h"
#include "RE/E/ExtraTextDisplayData.h"
#include "RE/G/GameSettingCollection.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESObjectREFR.h"
#include "SKSE/Version.h"

namespace RE
{
	bool BaseExtraList::PresenceBitfield::HasType(std::uint32_t a_type) const
	{
		const std::uint32_t index = (a_type >> 3);
		if (index >= 0x17) {
			return false;
		}
		const std::uint8_t bitMask = 1 << (a_type % 8);
		return (bits[index] & bitMask) != 0;
	}

	void BaseExtraList::PresenceBitfield::MarkType(std::uint32_t a_type, bool a_cleared)
	{
		const std::uint32_t index = (a_type >> 3);
		const std::uint8_t  bitMask = 1 << (a_type % 8);
		auto&               flag = bits[index];
		if (a_cleared) {
			flag &= ~bitMask;
		} else {
			flag |= bitMask;
		}
	}

	ExtraDataList::iterator ExtraDataList::begin()
	{
		return iterator(_extraData.GetData());
	}

	ExtraDataList::const_iterator ExtraDataList::cbegin() const
	{
		return const_iterator(_extraData.GetData());
	}

	ExtraDataList::const_iterator ExtraDataList::begin() const
	{
		return cbegin();
	}

	ExtraDataList::iterator ExtraDataList::end()
	{
		return iterator(nullptr);
	}

	ExtraDataList::const_iterator ExtraDataList::cend() const
	{
		return const_iterator(nullptr);
	}

	ExtraDataList::const_iterator ExtraDataList::end() const
	{
		return cend();
	}

	bool ExtraDataList::HasType(ExtraDataType a_type) const
	{
		BSReadLockGuard locker(GetLock());
		return _extraData.GetPresence() != nullptr && _extraData.GetPresence()->HasType(static_cast<std::uint32_t>(a_type));
	}

	BSExtraData* ExtraDataList::GetByType(ExtraDataType a_type)
	{
		return GetByTypeImpl(a_type);
	}

	const BSExtraData* ExtraDataList::GetByType(ExtraDataType a_type) const
	{
		return GetByTypeImpl(a_type);
	}

	bool ExtraDataList::Remove(ExtraDataType a_type, BSExtraData* a_toRemove)
	{
		BSWriteLockGuard locker(GetLock());

		if (!a_toRemove) {
			return false;
		}

		bool removed = false;

		if (_extraData.GetData() == a_toRemove) {
			_extraData.GetData() = _extraData.GetData()->next;
			removed = true;
		} else {
			for (auto iter = _extraData.GetData(); iter; iter = iter->next) {
				if (iter->next == a_toRemove) {
					iter->next = a_toRemove->next;
					removed = true;
					break;
				}
			}
		}

		if (removed) {
			MarkType(a_type, true);
		}

		return removed;
	}

	bool ExtraDataList::RemoveByType(ExtraDataType a_type)
	{
		BSWriteLockGuard locker(GetLock());

		if (!_extraData.GetData()) {
			return false;
		}

		bool removed = false;

		while (_extraData.GetData()->GetType() == a_type) {
			auto tmp = _extraData.GetData();
			_extraData.GetData() = _extraData.GetData()->next;
			delete tmp;
			removed = true;
		}

		auto prev = _extraData.GetData();
		for (auto cur = _extraData.GetData()->next; cur; cur = cur->next) {
			if (cur->GetType() == a_type) {
				prev->next = cur->next;
				delete cur;
				cur = prev;
				removed = true;
			}
			prev = cur;
		}

		MarkType(a_type, true);
		return removed;
	}

	BSExtraData* ExtraDataList::Add(BSExtraData* a_toAdd)
	{
		using func_t = decltype(&ExtraDataList::Add);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12176, 12315) };
		return func(this, a_toAdd);
	}

	ObjectRefHandle ExtraDataList::GetAshPileRef()
	{
		auto xAshRef = GetByType<ExtraAshPileRef>();
		return xAshRef ? xAshRef->ashPileRef : ObjectRefHandle();
	}

	std::int32_t ExtraDataList::GetCount() const
	{
		auto xCount = GetByType<ExtraCount>();
		return xCount ? xCount->count : 1;
	}

	const char* ExtraDataList::GetDisplayName(TESBoundObject* a_baseObject)
	{
		const char* result = nullptr;
		float       health = 1.0F;

		auto xHealth = GetByType<ExtraHealth>();
		if (xHealth) {
			health = xHealth->health;
		}

		auto       xText = GetExtraTextDisplayData();
		const bool dfHealth = health <= 1.0F ? (1.0F - health) < 0.001F : (health - 1.0F) < 0.001F;  // check for health == 1.0
		if (!xText && !dfHealth) {
			xText = new ExtraTextDisplayData();
			Add(xText);
		}

		if (xText) {
			result = xText->GetDisplayName(a_baseObject, health);
		} else {
			result = a_baseObject->GetName();
		}

		if (!result || result[0] == '\0') {
			auto gmst = GameSettingCollection::GetSingleton();
			auto sMissingName = gmst ? gmst->GetSetting("sMissingName") : nullptr;
			result = sMissingName ? sMissingName->GetString() : nullptr;
		}

		return result;
	}

	BGSEncounterZone* ExtraDataList::GetEncounterZone()
	{
		auto xZone = GetByType<ExtraEncounterZone>();
		return xZone ? xZone->zone : nullptr;
	}

	ExtraTextDisplayData* ExtraDataList::GetExtraTextDisplayData()
	{
		auto                  xRef = GetByType<ExtraReferenceHandle>();
		auto                  ref = xRef ? xRef->GetOriginalReference() : nullptr;
		ExtraTextDisplayData* xText = nullptr;
		if (ref && !ref->IsDeleted()) {
			xText = ref->extraList.GetByType<ExtraTextDisplayData>();
		}

		return xText ? xText : GetByType<ExtraTextDisplayData>();
	}

	TESObjectREFR* ExtraDataList::GetLinkedRef(BGSKeyword* a_keyword)
	{
		BSReadLockGuard locker(GetLock());

		auto xLinkedRef = GetByType<ExtraLinkedRef>();
		if (!xLinkedRef) {
			return nullptr;
		}

		TESObjectREFR* linkedRef = nullptr;
		for (auto& entry : xLinkedRef->linkedRefs) {
			if (entry.keyword == a_keyword) {
				linkedRef = entry.refr;
				if (!linkedRef && HasType(ExtraDataType::kEditorID)) {
					auto xMissingLinkedRefIDs = GetByType<ExtraMissingLinkedRefIDs>();
					linkedRef = xMissingLinkedRefIDs ? xMissingLinkedRefIDs->GetLinkedRef(a_keyword) : nullptr;
				}
			}

			if (linkedRef) {
				break;
			}
		}

		return linkedRef;
	}

	TESForm* ExtraDataList::GetOwner()
	{
		auto xOwner = GetByType<ExtraOwnership>();
		return xOwner ? xOwner->owner : nullptr;
	}

	SOUL_LEVEL ExtraDataList::GetSoulLevel() const
	{
		auto xSoul = GetByType<ExtraSoul>();
		return xSoul ? *xSoul->soul : SOUL_LEVEL::kNone;
	}

	ObjectRefHandle ExtraDataList::GetTeleportLinkedDoor()
	{
		auto xTeleport = GetByType<ExtraTeleport>();

		return xTeleport && xTeleport->teleportData ?
		           xTeleport->teleportData->linkedDoor :
		           ObjectRefHandle();
	}

	bool ExtraDataList::GetWorn() const
	{
		return HasType<ExtraWorn>() || HasType<ExtraWornLeft>();
	}

	bool ExtraDataList::HasQuestObjectAlias()
	{
		using func_t = decltype(&ExtraDataList::HasQuestObjectAlias);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11913, 12052) };
		return func(this);
	}

	void ExtraDataList::SetCount(std::uint16_t a_count)
	{
		using func_t = decltype(&ExtraDataList::SetCount);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11471, 11617) };
		return func(this, a_count);
	}

	void ExtraDataList::SetEncounterZone(BGSEncounterZone* a_zone)
	{
		if (auto xZone = GetByType<ExtraEncounterZone>()) {
			if (a_zone) {
				xZone->zone = a_zone;
			} else {
				Remove(xZone);
			}
		} else if (a_zone) {
			xZone = new ExtraEncounterZone(a_zone);
			Add(xZone);
		}
	}

	void ExtraDataList::SetExtraFlags(ExtraFlags::Flag a_flags, bool a_enable)
	{
		using func_t = decltype(&ExtraDataList::SetExtraFlags);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11903, 12042) };
		return func(this, a_flags, a_enable);
	}

	void ExtraDataList::SetInventoryChanges(InventoryChanges* a_changes)
	{
		using func_t = decltype(&ExtraDataList::SetInventoryChanges);
		static REL::Relocation<func_t> func{ RELOCATION_ID(11483, 11600) };
		return func(this, a_changes);
	}

	void ExtraDataList::SetOwner(TESForm* a_owner)
	{
		if (a_owner && a_owner->IsDynamicForm()) {
			return;
		}

		auto xOwner = GetByType<ExtraOwnership>();
		if (xOwner) {
			if (a_owner) {
				xOwner->owner = a_owner;
			} else {
				Remove(xOwner);
			}
		} else if (a_owner) {
			xOwner = new ExtraOwnership(a_owner);
			Add(xOwner);
		}
	}

	BSExtraData* ExtraDataList::GetByTypeImpl(ExtraDataType a_type) const
	{
		BSReadLockGuard locker(GetLock());

		if (!HasType(a_type)) {
			return nullptr;
		}

		for (auto iter = _extraData.GetData(); iter; iter = iter->next) {
			if (iter->GetType() == a_type) {
				return const_cast<BSExtraData*>(iter);
			}
		}

		return nullptr;
	}

	void ExtraDataList::MarkType(std::uint32_t a_type, bool a_cleared)
	{
		_extraData.GetPresence()->MarkType(a_type, a_cleared);
	}

	void ExtraDataList::MarkType(ExtraDataType a_type, bool a_cleared)
	{
		MarkType(static_cast<std::uint32_t>(a_type), a_cleared);
	}

	BSReadWriteLock& ExtraDataList::GetLock() const noexcept
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
			return *reinterpret_cast<BSReadWriteLock*>(reinterpret_cast<std::uintptr_t>(this) +
													   (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) == std::strong_ordering::less ? 0x10 : 0x18));
		} else {
			return *reinterpret_cast<BSReadWriteLock*>(reinterpret_cast<std::uintptr_t>(this) + 0x10);
		}
	}

	BSExtraData*& BaseExtraList::GetData() noexcept
	{
		return REL::RelocateMemberIfNewer<BSExtraData*>(SKSE::RUNTIME_SSE_1_6_629, this, 0x0, 0x8);
	}

	const BSExtraData*& BaseExtraList::GetData() const noexcept
	{
		return REL::RelocateMemberIfNewer<const BSExtraData*>(SKSE::RUNTIME_SSE_1_6_629, this, 0x0, 0x8);
	}

	BaseExtraList::PresenceBitfield*& BaseExtraList::GetPresence() noexcept
	{
		return REL::RelocateMemberIfNewer<BaseExtraList::PresenceBitfield*>(SKSE::RUNTIME_SSE_1_6_629, this, 0x08, 0x10);
	}

	const BaseExtraList::PresenceBitfield*& BaseExtraList::GetPresence() const noexcept
	{
		return REL::RelocateMemberIfNewer<const BaseExtraList::PresenceBitfield*>(SKSE::RUNTIME_SSE_1_6_629, this, 0x08, 0x10);
	}
}
