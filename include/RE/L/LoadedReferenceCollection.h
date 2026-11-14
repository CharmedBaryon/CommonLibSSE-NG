#pragma once

#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTHashMap.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class TESObjectREFR;

	// Spin-locked map of loaded references keyed by form ID.
	struct LoadedReferenceMap
	{
	public:
		// Returns false when a reference with the same form ID is already present.
		bool Insert(TESObjectREFR* a_ref);
		// Returns true when a reference with the same form ID was found and erased.
		bool Remove(TESObjectREFR* a_ref);

		// members
		BSTHashMap<FormID, ObjectRefHandle> references;      // 00
		std::uint32_t                       spinLock;        // 30
		std::uint32_t                       count;           // 34
		std::uint32_t                       lastUpdateTick;  // 38
		std::uint32_t                       pad3C;           // 3C
	};
	static_assert(sizeof(LoadedReferenceMap) == 0x40);

	// Engine singleton that indexes every loaded reference by form type.
	class LoadedReferenceCollection
	{
	public:
		[[nodiscard]] static LoadedReferenceCollection* GetSingleton();

		// Adds a_ref to the inventory-object map, to the map for its base form type
		// (see GetListForType) and, for doors with teleport data, to teleportDoors.
		void AddReference(TESObjectREFR* a_ref);
		// Removes a_ref from the maps AddReference fills.
		void RemoveReference(TESObjectREFR* a_ref);
		// Returns the map for Container, Furniture, Weapon, Ammo, NPC or IdleMarker, else nullptr.
		[[nodiscard]] LoadedReferenceMap* GetListForType(FormType a_formType);

		// members
		LoadedReferenceMap unk000;         // 000
		LoadedReferenceMap items;          // 040 - inventory-object references
		LoadedReferenceMap weapons;        // 080
		LoadedReferenceMap ammo;           // 0C0
		LoadedReferenceMap containers;     // 100
		LoadedReferenceMap actors;         // 140
		LoadedReferenceMap teleportDoors;  // 180
		LoadedReferenceMap furniture;      // 1C0
		LoadedReferenceMap idleMarkers;    // 200
	};
	static_assert(sizeof(LoadedReferenceCollection) == 0x240);
}
