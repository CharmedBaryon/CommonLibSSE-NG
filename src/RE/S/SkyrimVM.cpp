#include "RE/S/SkyrimVM.h"
#include "RE/V/VirtualMachine.h"

namespace RE
{
	SkyrimVM* SkyrimVM::GetSingleton()
	{
		REL::Relocation<SkyrimVM**> singleton{ RELOCATION_ID(514315, 400475) };
		return *singleton;
	}

	bool SkyrimVM::QueuePostRenderCall(const BSTSmartPointer<SkyrimScript::DelayFunctor>& a_functor)
	{
		using func_t = decltype(&SkyrimVM::QueuePostRenderCall);
		static REL::Relocation<func_t> func{ RELOCATION_ID(53144, 53955) };
		return func(this, a_functor);
	}

	void SkyrimVM::RelayEvent(VMHandle a_handle, BSFixedString* a_event, BSScript::IFunctionArguments* a_args, SkyrimVM::ISendEventFilter* a_optionalFilter)
	{
		using func_t = decltype(&SkyrimVM::RelayEvent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(53221, 54033) };
		return func(this, a_handle, a_event, a_args, a_optionalFilter);
	}

	// a_handle must be a handle for TESObjectREFR
	// Sends event to handle directly, then relays event to all reference aliases and magic effects attached to reference
	void SkyrimVM::SendAndRelayEvent(VMHandle a_handle, BSFixedString* a_event, BSScript::IFunctionArguments* a_args, SkyrimVM::ISendEventFilter* a_optionalFilter)
	{
		impl.get()->SendEvent(a_handle, *a_event, a_args);
		RelayEvent(a_handle, a_event, a_args, a_optionalFilter);
	}
}
