#pragma once

#include "REL/IDDB.h"

namespace REL
{
	class Offset2ID
	{
	public:
		using value_type = IDDB::mapping_t;
		using container_type = std::vector<value_type>;
		using size_type = typename container_type::size_type;
		using const_iterator = typename container_type::const_iterator;
		using const_reverse_iterator = typename container_type::const_reverse_iterator;

		Offset2ID();

		[[nodiscard]] std::uint64_t operator()(std::size_t a_offset) const;

		[[nodiscard]] const_iterator         begin() const noexcept { return _offset2id.begin(); }
		[[nodiscard]] const_iterator         cbegin() const noexcept { return _offset2id.cbegin(); }
		[[nodiscard]] const_iterator         end() const noexcept { return _offset2id.end(); }
		[[nodiscard]] const_iterator         cend() const noexcept { return _offset2id.cend(); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return _offset2id.rbegin(); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return _offset2id.crbegin(); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return _offset2id.rend(); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return _offset2id.crend(); }
		[[nodiscard]] size_type              size() const noexcept { return _offset2id.size(); }

	private:
		void load_v2();
		void load_v5();

		container_type _offset2id;
	};
}
