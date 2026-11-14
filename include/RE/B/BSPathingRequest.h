#pragma once

#include "RE/B/BSPathingActorAttributes.h"
#include "RE/B/BSPathingLocation.h"
#include "RE/B/BSPathingSearchParameters.h"
#include "RE/M/MovementActorAvoidanceParameters.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingAvoidNode;
	class MovementParameters;

	class BSPathingRequest : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingRequest;
		inline static constexpr auto VTABLE = VTABLE_BSPathingRequest;
		virtual ~BSPathingRequest();

		using ArrayRefCounted = std::pair<BSTArray<BSPathingAvoidNode>, uint32_t>;

		// add
		virtual std::uint32_t GetType();                                // 01 - CRC32("BSPathingRequest")
		virtual void          CopyTo(BSPathingRequest& a_dest);         // 02
		virtual void          Write(BSPathingStreamWrite* a_stream);    // 03
		virtual void          Read(BSPathingStreamRead* a_stream);      // 04
		virtual void          CheckValid();                             // 05
		virtual void          PrintDebugText(IDebugText* a_debugText);  // 06

		// members
		BSPathingStart                       start;                             // 10
		BSPathingGoal                        goal;                              // 48
		BSPathingRestrictions                restrictions;                      // 98
		BSPathingSearchParameters            searchParameters;                  // B0
		BSPathingActorAttributes             actorAttributes;                   // C0
		MovementActorAvoidanceParameters     movementActorAvoidanceParameters;  // D8
		BSTSmartPointer<IMovementParameters> defaultParameters;                 // F8
	};
	static_assert(sizeof(BSPathingRequest) == 0x100);
}
