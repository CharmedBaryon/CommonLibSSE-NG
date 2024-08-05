#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	template <class T>
	class hkRefPtr;

	class hkbAnimationBindingWithTriggers;
	class hkbAssetBundle;

	class hkbAnimationBindingSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbAnimationBindingSet;
		inline static constexpr auto VTABLE = VTABLE_hkbAnimationBindingSet;

		// members
		hkArray<hkbAnimationBindingWithTriggers*> bindings;      // 10
		hkArray<hkRefPtr<hkbAssetBundle>>         assetBundles;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbAnimationBindingSet) == 0x30);
}
