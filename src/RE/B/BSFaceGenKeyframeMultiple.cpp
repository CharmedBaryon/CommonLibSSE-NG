#include "RE/B/BSFaceGenKeyframeMultiple.h"

namespace RE
{
	const char* BSFaceGenKeyframeMultiple::GetExpressionName(std::uint32_t a_expression)
	{
		using func_t = decltype(&BSFaceGenKeyframeMultiple::GetExpressionName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26428, 27007) };
		return func(a_expression);
	}

	const char* BSFaceGenKeyframeMultiple::GetModifierName(std::uint32_t a_modifier)
	{
		using func_t = decltype(&BSFaceGenKeyframeMultiple::GetModifierName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26429, 27008) };
		return func(a_modifier);
	}

	const char* BSFaceGenKeyframeMultiple::GetPhonemeName(std::uint32_t a_phoneme)
	{
		using func_t = decltype(&BSFaceGenKeyframeMultiple::GetPhonemeName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26430, 27009) };
		return func(a_phoneme);
	}

	const char* BSFaceGenKeyframeMultiple::GetCustomName(std::uint32_t a_custom)
	{
		using func_t = decltype(&BSFaceGenKeyframeMultiple::GetCustomName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26431, 27010) };
		return func(a_custom);
	}

	void BSFaceGenKeyframeMultiple::SetValue(std::uint32_t a_idx, float a_value)
	{
		assert(a_idx < count);
		assert(values != nullptr);
		values[a_idx] = a_value;
		isUpdated = false;
	}

	void BSFaceGenKeyframeMultiple::Reset()
	{
		std::fill_n(values, count, 0.0f);
		isUpdated = false;
	}

	std::string BSFaceGenKeyframeMultiple::GetValueName(Type a_type, std::uint32_t a_idx)
	{
		const char* name{ nullptr };
		switch (a_type) {
		case Type::Expression:
			name = GetExpressionName(a_idx);
			break;
		case Type::Modifier:
			name = GetModifierName(a_idx);
			break;
		case Type::Phoneme:
			name = GetPhonemeName(a_idx);
			break;
		case Type::Custom:
			name = GetCustomName(a_idx);
			break;
		}
		return name ? name : "";
	}
}
