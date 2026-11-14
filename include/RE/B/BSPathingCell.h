#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class bhkWorld;
	class BSPathingSpace;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	struct BSPathingNumericIDVisitor;

	class BSPathingCell : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingCell;
		inline static constexpr auto VTABLE = VTABLE_BSPathingCell;

		virtual ~BSPathingCell();  // 00

		// add
		virtual std::uint32_t GetType() const = 0;                                             // 01 - crc32 hash of class name
		virtual void          Write(const BSPathingStreamWrite& a_stream) = 0;                 // 02
		virtual void          Read(const BSPathingStreamRead& a_stream) = 0;                   // 03
		virtual void          FixupNumericID(BSPathingNumericIDVisitor& a_visitor) = 0;        // 04
		virtual void          GetSpace(BSTSmartPointer<BSPathingSpace>& a_out) = 0;            // 05
		virtual bhkWorld*     GetBhkWorld() = 0;                                               // 06
		virtual bool          QValid() const = 0;                                              // 07
		virtual bool          QAttached() const = 0;                                           // 08
		virtual bool          QLoaded() const = 0;                                             // 09
		virtual bool          IsInSameSpace(BSTSmartPointer<BSPathingCell>* a_otherCell) = 0;  // 0A
	};
	static_assert(sizeof(BSPathingCell) == 0x10);
}
