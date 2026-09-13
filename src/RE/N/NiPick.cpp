#include "RE/N/NiPick.h"
#include "RE/N/NiAVObject.h"

namespace RE
{
	NiPick::Ptr NiPick::Create(std::uint32_t a_initialSize, std::uint32_t a_growBy)
	{
		auto* pick = NiAlloc<NiPick>(1);
		if (pick) {
			pick->ctor(a_initialSize, a_growBy);
		}
		return Ptr(pick);
	}

	void NiPick::Destroy()
	{
		dtor();
		NiFree(this);
	}

	NiPick* NiPick::ctor(std::uint32_t a_initialSize, std::uint32_t a_growBy)
	{
		using func_t = decltype(&NiPick::ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(70361, 71857) };  //Vr: 0xCD8370
		return func(this, a_initialSize, a_growBy);
	}

	void NiPick::dtor()
	{
		using func_t = decltype(&NiPick::dtor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(70362, 71858) };  //Vr: 0xCD8430
		return func(this);
	}

	bool NiPick::PickObjects(const NiPoint3& a_origin, const NiPoint3& a_direction, bool a_append)
	{
		using func_t = decltype(&NiPick::PickObjects);
		static REL::Relocation<func_t> func{ RELOCATION_ID(70363, 71859) };  //Vr: 0xCD8480
		return func(this, a_origin, a_direction, a_append);
	}
}
