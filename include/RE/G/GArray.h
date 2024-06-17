#pragma once

#include "RE/G/GAllocator.h"
#include "RE/G/GArrayBase.h"
#include "RE/G/GArrayData.h"
#include "RE/G/GArrayDefaultPolicy.h"
#include "RE/G/GStats.h"

namespace RE
{
	template <class T, std::uint32_t SID = GStatGroup::kGStat_Default_Mem, class SizePolicy = GArrayDefaultPolicy>
	class GArray : public GArrayBase<GArrayData<T, GAllocatorGH<T, SID>, SizePolicy>>
	{
	public:
		using ValueType = T;
		using AllocatorType = GAllocatorGH<T, SID>;
		using SizePolicyType = SizePolicy;
		using SelfType = GArray<T, SID, SizePolicy>;
		using BaseType = GArrayBase<GArrayData<T, GAllocatorGH<T, SID>, SizePolicy>>;

		GArray() :
			BaseType()
		{}

		GArray(std::int32_t a_size) :
			BaseType(a_size)
		{}

		GArray(const SizePolicyType& a_policy) :
			BaseType()
		{
			SetSizePolicy(a_policy);
		}

		GArray(const SelfType& a_array) :
			BaseType(a_array)
		{}

		const SelfType& operator=(const SelfType& a_array)
		{
			BaseType::operator=(a_array);
			return *this;
		}

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GArray<void*>) == 0x18);
}
