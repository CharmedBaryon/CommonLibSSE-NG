#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/Relocation.h"

namespace RE
{
	class TESObjectCELL;

	// Tracks the currently-loaded exterior cell and up to 6 neighbor cells,
	// maintaining a combined AABB and toggling bhkRigidBody collision-response
	// flags for refs entering/leaving the loaded bound as the player moves.
	class LoadedAreaBound : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_LoadedAreaBound;
		inline static constexpr auto VTABLE = VTABLE_LoadedAreaBound;

		~LoadedAreaBound() override;  // 00

		// On cell change, recomputes the AABB from a_cell and propagates it to
		// the neighbor cells' Havok worlds; on nullptr, calls Clear() instead.
		void SetCurrentCell(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&LoadedAreaBound::SetCurrentCell);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25415, 25946) };
			func(this, a_cell);
		}

		// Releases the neighbor-cell/entry state and resets cachedCell/counts.
		void Clear()
		{
			using func_t = decltype(&LoadedAreaBound::Clear);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25416, 25947) };
			func(this);
		}

		// members
		NiPointer<NiRefObject> neighborCells[6];  // 10 - suspected NiPointer<TESObjectCELL>[6]; pointee type unconfirmed
		TESObjectCELL*         cachedCell;        // 40
		std::uint8_t           flags;             // 48 - bit0 gates a "playable"-cell special case
		std::uint8_t           unk49[0xB];        // 49
		std::uint32_t          unk54;             // 54 - count; mirrors unk58/unk5C after a clear
		std::uint32_t          unk58;             // 58
		std::uint32_t          unk5C;             // 5C
		void*                  bucketArray;       // 60 - embedded hash/scatter-table; ctor sets a static "empty" sentinel
		std::uint8_t           unk68[8];          // 68
		void*                  entries;           // 70 - heap array of 0x18-byte entries (refcounted sub-pointer at +0x10); tracks toggled bhkRigidBody handles
		NiPoint3               boundsMin;         // 78
		NiPoint3               boundsMax;         // 84
		float                  marginX;           // 90 - per-axis padding constant, passed in at construction
		float                  marginY;           // 94
		float                  marginZ;           // 98
		float                  marginW;           // 9C
	};
	static_assert(sizeof(LoadedAreaBound) == 0xA0);
}
