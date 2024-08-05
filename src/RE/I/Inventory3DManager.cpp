#include "RE/I/Inventory3DManager.h"

namespace RE
{
	Inventory3DManager* Inventory3DManager::GetSingleton()
	{
		REL::Relocation<Inventory3DManager**> singleton{ RELOCATION_ID(517051, 403559) };
		return *singleton;
	}

	void Inventory3DManager::Begin3D(INTERFACE_LIGHT_SCHEME a_scheme)
	{
		using func_t = decltype(&Inventory3DManager::Begin3D);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50881, 51754) };
		return func(this, a_scheme);
	}

	void Inventory3DManager::End3D()
	{
		using func_t = decltype(&Inventory3DManager::End3D);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50883, 51756) };
		return func(this);
	}

	void Inventory3DManager::LoadInventoryItem(InventoryEntryData* a_objDesc)
	{
		using func_t = void (*)(Inventory3DManager*, InventoryEntryData*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50884, 51757) };
		return func(this, a_objDesc);
	}

	void Inventory3DManager::LoadInventoryItem(TESBoundObject* a_object, ExtraDataList* a_extraDataList)
	{
		using func_t = void (*)(Inventory3DManager*, TESBoundObject*, ExtraDataList*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50885, 51758) };
		return func(this, a_object, a_extraDataList);
	}

	void Inventory3DManager::Render()
	{
		using func_t = decltype(&Inventory3DManager::Render);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50882, 51755) };
		return func(this);
	}

	bool Inventory3DManager::ToggleItemZoom()
	{
		using func_t = decltype(&Inventory3DManager::ToggleItemZoom);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50887, 51760) };
		return func(this);
	}

	void Inventory3DManager::UnloadInventoryItem()
	{
		using func_t = decltype(&Inventory3DManager::UnloadInventoryItem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50886, 51759) };
		return func(this);
	}
}
