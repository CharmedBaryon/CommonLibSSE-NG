#pragma once

namespace RE
{
	template <class T, class Hash>
	class GHashsetCachedEntry
	{
	public:
		GHashsetCachedEntry() :
			nextInChain(-2),
			hashValue(0),
			value{}
		{}

		GHashsetCachedEntry(const GHashsetCachedEntry& a_entry) :
			nextInChain(a_entry.nextInChain),
			hashValue(a_entry.hashValue),
			value(a_entry.value)
		{}

		GHashsetCachedEntry(const T& a_key, SPInt a_next) :
			nextInChain(a_next),
			hashValue(0),
			value(a_key)
		{}

		[[nodiscard]] bool IsEmpty() const
		{
			return nextInChain == -2;
		}

		[[nodiscard]] bool IsEndOfChain() const
		{
			return nextInChain == -1;
		}

		[[nodiscard]] UPInt GetCachedHash([[maybe_unused]] UPInt a_maskValue) const
		{
			return hashValue;
		}

		void SetCachedHash(UPInt a_hashValue)
		{
			hashValue = a_hashValue;
		}

		void Clear()
		{
			value.~C();
			nextInChain = -2;
		}

		void Free()
		{
			Clear();
		}

		// members
		SPInt nextInChain;  // 00
		UPInt hashValue;    // 08
		T     value;        // 10
	private:
		KEEP_FOR_RE()
	};
	// size == 0x10 + sizeof(T)
}
