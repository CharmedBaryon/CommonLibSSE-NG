#include "REL/Offset2ID.h"

namespace REL
{
	Offset2ID::Offset2ID()
	{
		auto& db = IDDB::get();
		if (db._loadedFormat == IDDB::Format::SSEv5) {
			load_v5();
		} else {
			load_v2();
		}

		std::sort(_offset2id.begin(), _offset2id.end(), [](auto&& a_lhs, auto&& a_rhs) {
			return a_lhs.offset < a_rhs.offset;
		});
	}

	void Offset2ID::load_v2()
	{
		const std::span<const IDDB::mapping_t> id2offset = IDDB::get()._id2offset;
		_offset2id.reserve(id2offset.size());
		_offset2id.insert(_offset2id.begin(), id2offset.begin(), id2offset.end());
	}

	void Offset2ID::load_v5()
	{
		const std::span<const std::uint32_t> dense = IDDB::get()._id2offsetDense;
		_offset2id.reserve(dense.size());
		for (std::size_t id = 0; id < dense.size(); ++id) {
			if (dense[id] != 0) {
				_offset2id.push_back({ static_cast<std::uint64_t>(id), static_cast<std::uint64_t>(dense[id]) });
			}
		}
	}

	std::uint64_t Offset2ID::operator()(std::size_t a_offset) const
	{
		const value_type elem{ 0, a_offset };
		const auto       it = std::lower_bound(
            _offset2id.begin(),
            _offset2id.end(),
            elem,
            [](auto&& a_lhs, auto&& a_rhs) {
                return a_lhs.offset < a_rhs.offset;
            });
		if (it == _offset2id.end() || it->offset != a_offset) {
			stl::report_and_fail(
				std::format(
					"Failed to find the offset within the database: 0x{:08X}"sv,
					a_offset));
		}

		return it->id;
	}
}
