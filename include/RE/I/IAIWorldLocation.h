#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiPoint3;
	class TESObjectCELL;
	class TESObjectREFR;
	class TESWorldSpace;

	class IAIWorldLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAIWorldLocation;
		inline static constexpr auto VTABLE = VTABLE_IAIWorldLocation;

		virtual ~IAIWorldLocation() = default;  // 00

		// add
		virtual void                 Unk_01(void) = 0;                              // 01
		virtual void                 Unk_02(void) = 0;                              // 02
		virtual bool                 IsInSameSpace(TESObjectREFR* a_ref) = 0;       // 03
		virtual float                GetDistanceSquared(TESObjectREFR* a_ref) = 0;  // 04
		virtual bool                 IsActorAtLocation(TESObjectREFR* a_ref) = 0;   // 05
		virtual float                GetFacing() = 0;                               // 06
		virtual NiPoint3*            GetPosition() = 0;                             // 07
		virtual TESObjectCELL*       GetCell() = 0;                                 // 08
		virtual TESWorldSpace*       GetWorldSpace() = 0;                           // 09
		virtual float                GetRadius() = 0;                               // 0A
		virtual void                 Unk_0B(void) = 0;                              // 0B
		virtual bool                 HasFacing() = 0;                               // 0C
		virtual bool                 IsMinimumRadius() = 0;                         // 0D
		virtual float                GetAngleTolerance() = 0;                       // 0E
		virtual void                 Unk_0F(void) = 0;                              // 0F
		virtual void                 Unk_10(void) = 0;                              // 10
		virtual void                 Unk_11(void) = 0;                              // 11
		virtual bool                 IsValid() = 0;                                 // 12
		virtual const BSFixedString* GetTypeName() = 0;                             // 13
		virtual void                 SaveGame(BGSSaveGameBuffer* a_buf) = 0;        // 14
		virtual void                 LoadGame(BGSLoadGameBuffer* a_buf) = 0;        // 15
		virtual void                 Unk_16(void) = 0;                              // 16
	};
	static_assert(sizeof(IAIWorldLocation) == 0x8);
}
