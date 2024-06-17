#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbProjectStringData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbProjectStringData;
		inline static constexpr auto VTABLE = VTABLE_hkbProjectStringData;

		// members
		hkArray<hkStringPtr> animationFilenames;  // 10
		hkArray<hkStringPtr> behaviorFilenames;   // 20
		hkArray<hkStringPtr> characterFilenames;  // 30
		hkArray<hkStringPtr> eventNames;          // 40
		hkStringPtr          animationPath;       // 50
		hkStringPtr          behaviorPath;        // 58
		hkStringPtr          characterPath;       // 60
		hkStringPtr          scriptsPath;         // 68
		hkStringPtr          fullPathToSource;    // 70
		hkStringPtr          rootPath;            // 78
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbProjectStringData) == 0x80);
}
