#include "RE/C/Console.h"

#include "RE/T/TESObjectREFR.h"

namespace RE
{
	NiPointer<TESObjectREFR> Console::GetSelectedRef()
	{
		auto handle = GetSelectedRefHandle();
		return handle.get();
	}

	ObjectRefHandle Console::GetSelectedRefHandle()
	{
		REL::Relocation<ObjectRefHandle*> selectedRef{ RELOCATION_ID(519394, AE_CHECK(SKSE::RUNTIME_SSE_1_6_1130, 405935, 504099)) };
		return *selectedRef;
	}

	void Console::SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr)
	{
		ObjectRefHandle handle(a_refPtr.get());
		SetSelectedRef_Impl(handle);
	}

	void Console::SetSelectedRef(TESObjectREFR* a_ref)
	{
		ObjectRefHandle handle(a_ref);
		SetSelectedRef_Impl(handle);
	}

	void Console::SetSelectedRef(ObjectRefHandle a_handle)
	{
		SetSelectedRef_Impl(a_handle);
	}

	void Console::SetSelectedRef_Impl(ObjectRefHandle& a_handle)
	{
		using func_t = decltype(&Console::SetSelectedRef_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50164, 51093) };
		return func(this, a_handle);
	}
}
