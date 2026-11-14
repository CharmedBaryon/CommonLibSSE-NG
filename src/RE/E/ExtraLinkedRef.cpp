#include "RE/E/ExtraLinkedRef.h"

namespace RE
{
	ExtraLinkedRef::ExtraLinkedRef() :
		BSExtraData(),
		linkedRefs()
	{
		stl::emplace_vtable(this);
	}

	ExtraDataType ExtraLinkedRef::GetType() const
	{
		return ExtraDataType::kLinkedRef;
	}

	bool ExtraLinkedRef::IsNotEqual(const BSExtraData* a_rhs) const
	{
		using func_t = decltype(&ExtraLinkedRef::IsNotEqual);
		static REL::Relocation<func_t> func{ RELOCATION_ID(12405, 12539) };
		return func(this, a_rhs);
	}
}
