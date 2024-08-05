#include "RE/H/hkReferencedObject.h"

namespace RE
{
	hkReferencedObject::hkReferencedObject() :
		memSizeAndFlags(0),
		referenceCount(1),
		pad0C(0)
	{}

	const hkClass* hkReferencedObject::GetClassType() const
	{
		return nullptr;
	}

	void hkReferencedObject::CalcContentStatistics(hkStatisticsCollector*, const hkClass*) const
	{
		return;
	}

	void hkReferencedObject::AddReference() const
	{
		using func_t = decltype(&hkReferencedObject::AddReference);
		static REL::Relocation<func_t> func{ RELOCATION_ID(56606, 57010) };
		return func(this);
	}

	std::int32_t hkReferencedObject::GetAllocatedSize() const
	{
		return memSizeAndFlags & kMemSize;
	}

	std::int32_t hkReferencedObject::GetReferenceCount() const
	{
		return referenceCount;
	}

	void hkReferencedObject::RemoveReference() const
	{
		using func_t = decltype(&hkReferencedObject::RemoveReference);
		static REL::Relocation<func_t> func{ RELOCATION_ID(56607, 57011) };
		return func(this);
	}
}
