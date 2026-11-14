#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;

	class CombatBlackboardKeyBase
	{
	public:
		virtual ~CombatBlackboardKeyBase() = default;                          // 00
		virtual uint32_t             GetObjectSize() { return 0; };            // 01
		virtual void                 CreateObject(void*){};                    // 02
		virtual void                 DestroyObject(void*){};                   // 03
		virtual const BSFixedString& GetName() const { return name; };         // 04
		virtual void                 SaveObject(BGSSaveGameBuffer*, void*){};  // 05
		virtual void                 LoadObject(BGSLoadGameBuffer*, void*){};  // 06

		// members
		BSFixedString name;  // 08
	};
	static_assert(sizeof(CombatBlackboardKeyBase) == 0x10);
}
