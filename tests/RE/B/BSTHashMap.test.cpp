#include "catch2/catch_all.hpp"

#include "RE/B/BSTHashMap.h"

namespace
{
	struct DoubleFreeTracker
	{
		static inline int destroyCount = 0;
		static inline int doubleFreeCount = 0;

		static void Reset()
		{
			destroyCount = 0;
			doubleFreeCount = 0;
		}

		DoubleFreeTracker() = default;
		DoubleFreeTracker(const DoubleFreeTracker&) = delete;
		DoubleFreeTracker& operator=(const DoubleFreeTracker&) = delete;

		DoubleFreeTracker(DoubleFreeTracker&& a_rhs) noexcept :
			_destroyed(a_rhs._destroyed)
		{}

		DoubleFreeTracker& operator=(DoubleFreeTracker&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				_destroyed = a_rhs._destroyed;
			}
			return *this;
		}

		~DoubleFreeTracker()
		{
			++destroyCount;
			if (_destroyed) {
				++doubleFreeCount;
			}
			_destroyed = true;
		}

	private:
		bool _destroyed{ false };
	};

	// Hashes a key to itself so slot placement is deterministic and a collision can be
	// engineered exactly, instead of relying on BSCRC32's distribution.
	struct IdentityHash
	{
		[[nodiscard]] std::uint32_t operator()(int a_key) const noexcept
		{
			return static_cast<std::uint32_t>(a_key);
		}
	};

	// `_capacity`/`_free`/`_good` are protected on BSTScatterTableStandardParent, so a
	// subclass can reach them the same way BSTScatterTable's own member functions do.
	struct SkyrimClearedHashMap : RE::BSTStaticHashMap<int, int, 2048, IdentityHash>
	{
		void ForceSkyrimClear()
		{
			clear();
			_free = _capacity;
			_good = _capacity;
		}

		[[nodiscard]] std::uint32_t DebugGood() const noexcept { return _good; }
	};
}

TEST_CASE("BSTHashMap/NoDoubleFree", "[unit]")
{
	DoubleFreeTracker::Reset();

	SECTION("destroying a populated map destroys each value exactly once")
	{
		{
			RE::BSTStaticHashMap<int, DoubleFreeTracker, 8> map;
			REQUIRE(map.emplace(1, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(2, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(3, DoubleFreeTracker{}).second);
		}  // map destructs here, destroying every occupied entry_type in its fixed buffer

		CHECK(DoubleFreeTracker::doubleFreeCount == 0);
	}

	SECTION("clear() followed by destruction still destroys each value exactly once")
	{
		{
			RE::BSTStaticHashMap<int, DoubleFreeTracker, 8> map;
			REQUIRE(map.emplace(1, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(2, DoubleFreeTracker{}).second);
			map.clear();
			REQUIRE(map.emplace(3, DoubleFreeTracker{}).second);
		}

		CHECK(DoubleFreeTracker::doubleFreeCount == 0);
	}
}

TEST_CASE("BSTHashMap/FreeEntryBoundary", "[unit]")
{
	SkyrimClearedHashMap map;

	// Fill most (but not all) of the table; with the identity hash every key here lands in
	// its own slot, so none of this collides.
	for (int i = 0; i < 2000; ++i) {
		REQUIRE(map.emplace(i, i).second);
	}
	REQUIRE(map.size() == 2000);

	// Forces the table into exactly the state Skyrim's own Clear() leaves it in - every
	// slot freed, `_good` pinned to `_capacity` rather than trusted to this library's own
	// clear() - so the next free-entry scan must start from that out-of-bounds sentinel
	// and move into range before reading anything.
	map.ForceSkyrimClear();
	REQUIRE(map.size() == 0);

	// Key 0 takes slot 0 directly (free real estate) - `_good` is untouched by this insert.
	REQUIRE(map.emplace(0, 0).second);

	// Key 2048 hashes to the same slot as key 0 (2048 & 2047 == 0), forcing the very first
	// get_free_entry() call since clear() while `_good` still equals capacity.
	REQUIRE(map.emplace(2048, 2048).second);

	CHECK(map.DebugGood() == 2047);

	CHECK(map.size() == 2);

	// The regression this guards against: the second insert used to land in a slot the
	// chain never linked to, so it was physically written but unreachable - exactly the
	// in-game symptom, where contains() on the new key comes back false permanently.
	CHECK(map.contains(2048));

	const auto it = map.find(2048);
	REQUIRE(it != map.end());
	CHECK(it->second == 2048);

	std::size_t seen = 0;
	for ([[maybe_unused]] const auto& entry : map) {
		++seen;
	}
	CHECK(seen == map.size());
}
