#pragma once

namespace RE
{
	class hkStringPtr
	{
	public:
		enum StringFlags
		{
			kMask = static_cast<std::uint32_t>(-1),
			kManaged = 1 << 0
		};

		explicit hkStringPtr(std::string_view a_data, const std::uint32_t a_mask = kMask, const bool a_mark = kManaged);
		hkStringPtr(const char* a_data);

		// member types
		using size_type = std::int32_t;

		// members access
		[[nodiscard]] const char* data() const noexcept;
		[[nodiscard]] const char* c_str() const noexcept;

		// capacity
		[[nodiscard]] bool      empty() const noexcept;
		[[nodiscard]] size_type size() const;
		[[nodiscard]] size_type length() const;

	protected:
		const char* _data;  // 0
	};
	static_assert(sizeof(hkStringPtr) == 0x8);
}
