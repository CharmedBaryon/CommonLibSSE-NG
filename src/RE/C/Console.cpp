#include "RE/C/Console.h"

#include "RE/F/FxDelegateArgs.h"
#include "RE/G/GFxValue.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/U/UI.h"

namespace RE
{
	void Console::ExecuteCommand(const char* a_command)
	{
		const auto ui = UI::GetSingleton();
		if (!ui || ui->menuStack.empty())
			return;

		GFxValue vals[1];
		vals[0].SetString(a_command);

		FxDelegateArgs                                         args(nullptr, ui->menuStack.front().get(), nullptr, vals, 1);
		static REL::Relocation<void (*)(FxDelegateArgs* args)> func{ RELOCATION_ID(50157, 51084) };
		func(&args);
	}

	NiPointer<TESObjectREFR> Console::GetSelectedRef()
	{
		auto handle = GetSelectedRefHandle();
		return handle.get();
	}

	ObjectRefHandle Console::GetSelectedRefHandle()
	{
		static REL::Relocation<ObjectRefHandle*> selectedRef{ RELOCATION_ID(519394, AE_CHECK(SKSE::RUNTIME_SSE_1_6_1130, 405935, 504099)) };
		return *selectedRef;
	}

	TESQuest* Console::GetCommandScriptParentQuest()
	{
		static REL::Relocation<TESQuest**> quest{
			RELOCATION_ID(519336, AE_CHECK(SKSE::RUNTIME_SSE_1_6_1130, 405876, 504093))  // 1.6.640: 405876
		};
		return *quest;
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
