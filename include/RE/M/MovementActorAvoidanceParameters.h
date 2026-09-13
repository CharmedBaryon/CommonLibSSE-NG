#pragma once

namespace RE
{
	class MovementActorAvoidanceParameters
	{
	public:
		enum class Type : uint32_t
		{
			kAllActors = 0x0,
			kNoActor = 0x1,
			kUnk2 = 0x2,
			kIgnoreOneActor = 0x3,
			kMask = 0x3,
		};
		using AVOIDANCE_TYPE = stl::enumeration<Type, uint32_t>;

		// members
		BSTSmallArray<std::uint32_t, 1> actors;    // 00
		AVOIDANCE_TYPE                  flags;     // 18
		int                             field_1C;  // 1C
	};
	static_assert(sizeof(MovementActorAvoidanceParameters) == 0x20);
}
