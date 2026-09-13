#include "RE/B/BSProceduralLightningController.h"

using namespace REL;

namespace RE
{
	void BSProceduralLightningController::Dtor()
	{
		RelocateVirtual<void(BSProceduralLightningController*)>(0x00, 0x00, this);
	}

	const NiRTTI* BSProceduralLightningController::GetRTTI() const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetRTTI)>(0x02, 0x02, this);
	}

	NiObject* BSProceduralLightningController::CreateClone(NiCloningProcess& a_cloning)
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::CreateClone)>(0x17, 0x17, this, a_cloning);
	}

	void BSProceduralLightningController::LoadBinary(NiStream& a_stream)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::LoadBinary)>(0x18, 0x18, this, a_stream);
	}

	void BSProceduralLightningController::LinkObject(NiStream& a_stream)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::LinkObject)>(0x19, 0x19, this, a_stream);
	}

	bool BSProceduralLightningController::RegisterStreamables(NiStream& a_stream)
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::RegisterStreamables)>(0x1A, 0x1A, this, a_stream);
	}

	void BSProceduralLightningController::SaveBinary(NiStream& a_stream)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::SaveBinary)>(0x1B, 0x1B, this, a_stream);
	}

	bool BSProceduralLightningController::IsEqual(NiObject* a_object)
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::IsEqual)>(0x1C, 0x1C, this, a_object);
	}

	void BSProceduralLightningController::ProcessClone(NiCloningProcess& a_cloning)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::ProcessClone)>(0x1D, 0x1D, this, a_cloning);
	}

	void BSProceduralLightningController::Update(float a_time)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::Update)>(0x27, 0x27, this, a_time);
	}

	bool BSProceduralLightningController::TargetIsRequiredType() const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::TargetIsRequiredType)>(0x2E, 0x2E, this);
	}

	std::uint16_t BSProceduralLightningController::GetInterpolatorCount() const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetInterpolatorCount)>(0x2F, 0x2F, this);
	}

	const char* BSProceduralLightningController::GetInterpolatorID(std::uint16_t a_index)
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetInterpolatorID)>(0x30, 0x30, this, a_index);
	}

	std::uint16_t BSProceduralLightningController::GetInterpolatorIndex(const char* a_id) const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetInterpolatorIndex)>(0x31, 0x31, this, a_id);
	}

	std::uint16_t BSProceduralLightningController::GetInterpolatorIndexFx(const BSFixedString& a_id) const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetInterpolatorIndexFx)>(0x32, 0x32, this, a_id);
	}

	NiInterpolator* BSProceduralLightningController::GetInterpolator(std::uint16_t a_index) const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetInterpolator)>(0x33, 0x33, this, a_index);
	}

	void BSProceduralLightningController::SetInterpolator(NiInterpolator* a_interpolator, std::uint16_t a_index)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::SetInterpolator)>(0x34, 0x34, this, a_interpolator, a_index);
	}

	const char* BSProceduralLightningController::GetCtlrID()
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::GetCtlrID)>(0x36, 0x36, this);
	}

	NiInterpolator* BSProceduralLightningController::CreatePoseInterpolator(std::uint16_t a_index)
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::CreatePoseInterpolator)>(0x37, 0x37, this, a_index);
	}

	void BSProceduralLightningController::SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::SynchronizePoseInterpolator)>(0x38, 0x38, this, a_interp, a_index);
	}

	NiBlendInterpolator* BSProceduralLightningController::CreateBlendInterpolator(std::uint16_t a_index, bool a_managerControlled, bool a_accumulateAnimations, float a_weightThreshold, std::uint8_t a_arraySize) const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::CreateBlendInterpolator)>(0x39, 0x39, this, a_index, a_managerControlled, a_accumulateAnimations, a_weightThreshold, a_arraySize);
	}

	void BSProceduralLightningController::GuaranteeTimeRange(float a_startTime, float a_endTime)
	{
		RelocateVirtual<decltype(&BSProceduralLightningController::GuaranteeTimeRange)>(0x3A, 0x3A, this, a_startTime, a_endTime);
	}

	bool BSProceduralLightningController::InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const
	{
		return RelocateVirtual<decltype(&BSProceduralLightningController::InterpolatorIsCorrectType)>(0x3B, 0x3B, this, a_interpolator, a_index);
	}
}
