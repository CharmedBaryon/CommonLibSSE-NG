#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectCELL;
	class TESObjectREFR;
	class TESWorldSpace;

	struct TeleportPath
	{
	public:
		struct ParentSpaceNode
		{
		public:
			// members
			bool           isWorldspace;  // 00
			char           pad01[7];      // 01
			TESWorldSpace* worldspace;    // 08
			TESObjectCELL* interiorCell;  // 10
		};
		static_assert(sizeof(ParentSpaceNode) == 0x18);

		struct TeleportLink
		{
		public:
			// members
			TESObjectREFR* ref;               // 00
			NiPoint3       teleportLocation;  // 08
		};
		static_assert(sizeof(TeleportLink) == 0x18);

		// members
		BSTArray<ParentSpaceNode> spaces;        // 00 - each cell in sequence between the current cell and the target cell
		BSTArray<TeleportLink>    teleportRefs;  // 18 - each teleport ref in sequence between the current cell and the target cell
		NiPoint3                  start;         // 30
		NiPoint3                  end;           // 3C
	};
	static_assert(sizeof(TeleportPath) == 0x48);
}
