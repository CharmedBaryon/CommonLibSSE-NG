#pragma once

#include "RE/H/hkClassEnum.h"
#include "RE/H/hkClassMember.h"

namespace RE
{
	class hkCustomAttributes;

	/// Reflection information for any reflected type.
	class hkClass
	{
	public:
		enum FlagValues
		{
			kFlagsNone = 0,
			kFlagsNotSerializable = 1
		};
		using Flags = stl::enumeration<FlagValues, std::uint32_t>;

		const char*                name;                      // 00
		const hkClass*             parent;                    // 08
		std::int32_t               objectSize;                // 10
		std::int32_t               numImplementedInterfaces;  // 14
		const class hkClassEnum*   declaredEnums;             // 18
		std::int32_t               numDeclaredEnums;          // 20
		std::uint32_t              pad24;                     // 24
		const class hkClassMember* declaredMembers;           // 28
		std::int32_t               numDeclaredMembers;        // 30
		std::uint32_t              pad34;                     // 34
		const void*                defaults;                  // 38
		const hkCustomAttributes*  attributes;                // 40
		Flags                      flags;                     // 48
		std::int32_t               describedVersion;          // 4C
	};
	static_assert(sizeof(hkClass) == 0x50);
}
