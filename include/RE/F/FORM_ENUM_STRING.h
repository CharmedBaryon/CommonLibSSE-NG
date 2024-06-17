#pragma once

namespace RE
{
	enum class FormType;

	struct FORM_ENUM_STRING
	{
	public:
		[[nodiscard]] static std::span<FORM_ENUM_STRING, 138> GetFormEnumString()
		{
			REL::Relocation<FORM_ENUM_STRING(*)[138]> formEnumString{ RELOCATION_ID(501008, 359120) };
			return { *formEnumString };
		}

		// members
		FormType      formType;    // 00
		const char*   formString;  // 08
		std::uint32_t formCode;    // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FORM_ENUM_STRING) == 0x18);
}
