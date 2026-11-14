#pragma once

#include "RE/N/NiObject.h"

namespace RE
{
	class NiAVObjectPalette : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAVObjectPalette;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAVObjectPalette;
		inline static constexpr auto VTABLE = VTABLE_NiAVObjectPalette;

		~NiAVObjectPalette() override = default;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                                  // 02
		void          LoadBinary([[maybe_unused]] NiStream& a_stream) override;  // 18
		void          LinkObject([[maybe_unused]] NiStream& a_stream) override;  // 19
		void          SaveBinary([[maybe_unused]] NiStream& a_stream) override;  // 1B

		// add
		virtual NiAVObject* GetAVObject(BSFixedString& a_name) = 0;                        // 25
		virtual void        SetAVObject(BSFixedString& a_name, NiAVObject* a_object) = 0;  // 26
		virtual void        ResetAndFillFromScenegraph();                                  // 27
	};
	static_assert(sizeof(NiAVObjectPalette) == 0x10);
}