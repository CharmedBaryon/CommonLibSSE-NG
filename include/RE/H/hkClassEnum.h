#pragma once

namespace RE
{
	class hkStreamWriter;
	class hkCustomAttributes;

	/// Reflection object for enumerated types.
	class hkClassEnum
	{
	public:
		/// A single enumerated name and value pair.
		struct Item
		{
		public:
			/// Create a new enumerated item.
			Item(int v, const char* n) :
				m_value(v), m_name(n) {}

			/// Get the name of this item.
			const char* getName() const { return m_name; }

			/// Get the integer value of this item.
			int getValue() const { return m_value; }

		private:
			int         m_value;
			const char* m_name;
		};

		enum FlagValues
		{
			FLAGS_NONE = 0
		};

	private:
		const char*                                 m_name;        // 00
		const Item*                                 m_items;       // 08
		std::int32_t                                m_numItems;    // 10
		std::int32_t                                pad14;         // 14
		class hkCustomAttributes*                   m_attributes;  // 18
		stl::enumeration<FlagValues, std::uint32_t> m_flags;       // 20
	};
	static_assert(sizeof(hkClassEnum) == 0x28);
}
