#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaMirroredSkeleton;
	class hkaSkeleton;
	class hkaSkeletonMapper;
	class hkbAnimationBindingSet;
	class hkbCharacterData;
	class hkbSymbolIdMap;
	class hkCriticalSection;

	class hkbCharacterSetup : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterSetup;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterSetup;

		// members
		hkArray<hkRefPtr<const hkaSkeletonMapper>> retargetingSkeletonMappers;        // 10
		hkRefPtr<const hkaSkeleton>                animationSkeleton;                 // 20
		hkRefPtr<const hkaSkeletonMapper>          ragdollToAnimationSkeletonMapper;  // 28
		hkRefPtr<const hkaSkeletonMapper>          animationToRagdollSkeletonMapper;  // 30
		hkRefPtr<hkbAnimationBindingSet>           animationBindingSet;               // 38
		hkRefPtr<hkbCharacterData>                 data;                              // 40
		hkRefPtr<const hkaSkeleton>                unscaledAnimationSkeleton;         // 48
		mutable hkRefPtr<hkaMirroredSkeleton>      mirroredSkeleton;                  // 50
		hkRefPtr<hkbSymbolIdMap>                   characterPropertyIdMap;            // 58
		mutable hkCriticalSection*                 criticalSection;                   // 60
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbCharacterSetup) == 0x68);
}
