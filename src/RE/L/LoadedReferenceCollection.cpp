#include "RE/L/LoadedReferenceCollection.h"

#include "RE/T/TESObjectREFR.h"

namespace RE
{
	bool LoadedReferenceMap::Insert(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&LoadedReferenceMap::Insert);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17912, 18313) };
		return func(this, a_ref);
	}

	bool LoadedReferenceMap::Remove(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&LoadedReferenceMap::Remove);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17913, 18314) };
		return func(this, a_ref);
	}

	LoadedReferenceCollection* LoadedReferenceCollection::GetSingleton()
	{
		static REL::Relocation<LoadedReferenceCollection**> singleton{ RELOCATION_ID(514727, 400885) };
		return *singleton;
	}

	void LoadedReferenceCollection::AddReference(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&LoadedReferenceCollection::AddReference);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17921, 18322) };
		return func(this, a_ref);
	}

	void LoadedReferenceCollection::RemoveReference(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&LoadedReferenceCollection::RemoveReference);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17922, 18323) };
		return func(this, a_ref);
	}

	LoadedReferenceMap* LoadedReferenceCollection::GetListForType(FormType a_formType)
	{
		using func_t = decltype(&LoadedReferenceCollection::GetListForType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17923, 18324) };
		return func(this, a_formType);
	}
}
