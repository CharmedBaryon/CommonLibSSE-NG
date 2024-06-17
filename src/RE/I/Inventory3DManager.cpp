#include "RE/I/Inventory3DManager.h"

namespace RE
{
	Inventory3DManager* Inventory3DManager::GetSingleton()
	{
		REL::Relocation<Inventory3DManager**> singleton{ RELOCATION_ID(517051, 403559) };
		return *singleton;
	}

	void Inventory3DManager::UpdateItem3D(InventoryEntryData* a_objDesc)
	{
		using func_t = decltype(&Inventory3DManager::UpdateItem3D);
		REL::Relocation<func_t> func{ RELOCATION_ID(50884, 51757) };
		return func(this, a_objDesc);
	}

	void Inventory3DManager::UpdateMagic3D(TESForm* a_form, std::uint32_t a_arg2)
	{
		using func_t = decltype(&Inventory3DManager::UpdateMagic3D);
		REL::Relocation<func_t> func{ RELOCATION_ID(50885, 51758) };
		return func(this, a_form, a_arg2);
	}

	void Inventory3DManager::Clear3D()
	{
		using func_t = decltype(&Inventory3DManager::Clear3D);
		REL::Relocation<func_t> func{ RELOCATION_ID(50886, 51759) };
		return func(this);
	}

	void Inventory3DManager::Render()
	{
		using func_t = decltype(&Inventory3DManager::Render);
		REL::Relocation<func_t> func{ RELOCATION_ID(50882, 51755) };
		return func(this);
	}

	bool Inventory3DManager::ToggleItemZoom()
	{
		using func_t = decltype(&Inventory3DManager::ToggleItemZoom);
		REL::Relocation<func_t> func{ RELOCATION_ID(50887, 51760) };
		return func(this);
	}
}
