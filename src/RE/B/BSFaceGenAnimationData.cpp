#include "RE/B/BSFaceGenAnimationData.h"

namespace RE
{
	void BSFaceGenAnimationData::SetExpressionOverride(std::uint32_t a_idx, float a_value)
	{
		using func_t = decltype(&BSFaceGenAnimationData::SetExpressionOverride);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25980, 26594) };
		func(this, a_idx, a_value);
	}

	void BSFaceGenAnimationData::ClearExpressionOverride() noexcept
	{
		exprOverride = false;
	}

	void BSFaceGenAnimationData::Reset(float a_timer, bool a_resetExpression, bool a_resetModifierAndPhoneme, bool a_resetCustom, bool a_closeEyes)
	{
		using func_t = decltype(&BSFaceGenAnimationData::Reset);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25977, 26586) };
		func(this, a_timer, a_resetExpression, a_resetModifierAndPhoneme, a_resetCustom, a_closeEyes);
	}

	std::uint32_t BSFaceGenAnimationData::GetActiveExpression() const
	{
		std::uint32_t expression = BSFaceGenKeyframeMultiple::Expression::MoodNeutral;

		for (std::uint32_t i = 0; i < expression3.count; ++i) {
			if (expression3.values[i] > expression3.values[expression]) {
				expression = i;
			}
		}

		return expression;
	}
}
