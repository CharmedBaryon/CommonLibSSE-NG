#include "RE/N/NiTimeController.h"

namespace RE
{
	const NiRTTI* NiTimeController::GetRTTI() const
	{
		REL::Relocation<const NiRTTI*> rtti{ NiTimeController::Ni_RTTI };
		return rtti.get();
	}

	void NiTimeController::LoadBinary(NiStream& a_stream)
	{
		using func_t = decltype(&NiTimeController::LoadBinary);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69433, 70810) };
		return func(this, a_stream);
	}

	void NiTimeController::LinkObject(NiStream& a_stream)
	{
		using func_t = decltype(&NiTimeController::LinkObject);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69434, 70811) };
		return func(this, a_stream);
	}

	bool NiTimeController::RegisterStreamables(NiStream& a_stream)
	{
		using func_t = decltype(&NiTimeController::RegisterStreamables);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69435, 70812) };
		return func(this, a_stream);
	}

	void NiTimeController::SaveBinary(NiStream& a_stream)
	{
		using func_t = decltype(&NiTimeController::SaveBinary);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69436, 70813) };
		return func(this, a_stream);
	}

	bool NiTimeController::IsEqual(NiObject* a_object)
	{
		using func_t = decltype(&NiTimeController::IsEqual);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69437, 70814) };
		return func(this, a_object);
	}

	void NiTimeController::ProcessClone(NiCloningProcess& a_cloning)
	{
		using func_t = decltype(&NiTimeController::ProcessClone);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69449, 70826) };
		return func(this, a_cloning);
	}

	void NiTimeController::Start(float a_time)
	{
		using func_t = decltype(&NiTimeController::Start);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69440, 70817) };
		return func(this, a_time);
	}

	void NiTimeController::Stop()
	{
		using func_t = decltype(&NiTimeController::Stop);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69441, 70818) };
		return func(this);
	}

	void NiTimeController::SetTarget(NiObjectNET* a_target)
	{
		using func_t = decltype(&NiTimeController::SetTarget);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69442, 70819) };
		return func(this, a_target);
	}

	float NiTimeController::ComputeScaledTime(float a_time)
	{
		using func_t = decltype(&NiTimeController::ComputeScaledTime);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69447, 70824) };
		return func(this, a_time);
	}

	void NiTimeController::StartAnimations(NiObjectNET* a_target)
	{
		using func_t = decltype(&NiTimeController::StartAnimations);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69444, 70821) };
		return func(a_target);
	}

	NiTimeController* NiTimeController::ctor()
	{
		using func_t = decltype(&NiTimeController::ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69438, 70815) };
		return func(this);
	}

	void NiTimeController::dtor()
	{
		using func_t = decltype(&NiTimeController::dtor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69439, 70816) };
		return func(this);
	}
}
