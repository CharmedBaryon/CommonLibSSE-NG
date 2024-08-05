#pragma once

namespace RE
{
	struct hkpPropertyValue
	{
	public:
		hkpPropertyValue() = default;
		hkpPropertyValue(std::uint64_t a_value);
		hkpPropertyValue(std::int32_t a_value);
		hkpPropertyValue(std::uint32_t a_value);
		hkpPropertyValue(float a_value);
		hkpPropertyValue(void* a_value);

		[[nodiscard]] float         GetFloat() const;
		[[nodiscard]] void*         GetPointer() const;
		[[nodiscard]] std::int32_t  GetSInt() const;
		[[nodiscard]] std::uint32_t GetUInt() const;
		[[nodiscard]] std::uint64_t GetUInt64() const;

		// members
		std::uint64_t data;  // 0
	};
	static_assert(sizeof(hkpPropertyValue) == 0x8);

	class hkpProperty
	{
	public:
		hkpProperty() = default;
		hkpProperty(std::uint32_t a_key, hkpPropertyValue a_value);

		// members
		std::uint32_t    key;               // 00
		std::uint32_t    alignmentPadding;  // 04
		hkpPropertyValue value;             // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpProperty) == 0x10);
}
