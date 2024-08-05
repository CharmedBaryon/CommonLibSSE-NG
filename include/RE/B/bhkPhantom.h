#pragma once

#include "RE/B/bhkWorldObject.h"

namespace RE
{
	class bhkPhantom : public bhkWorldObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkPhantom;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkPhantom;
		inline static constexpr auto VTABLE = VTABLE_bhkPhantom;

		~bhkPhantom() override;  // 00

		// override (bhkWorldObject)
		const NiRTTI* GetRTTI() const override;           // 02
		void          RemoveFromCurrentWorld() override;  // 2A

		// members
		std::uint64_t unk28;  // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkPhantom) == 0x30);
}
