#pragma once

#include "RE/N/NiObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class ImageSpaceModifierInstanceForm;

	class ImageSpaceModifierInstance : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceModifierInstance;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceModifierInstance;

		~ImageSpaceModifierInstance() override;  // 00

		// add
		virtual bool                            Unk_25(void);                   // 25 - { return 0; }
		virtual void                            Apply() = 0;                    // 26
		virtual ImageSpaceModifierInstanceForm* IsForm();                       // 27 - { return 0; }
		virtual void                            PrintInfo(char* a_dstBuf) = 0;  // 28

		// members
		std::uint32_t         unk10;     // 10
		float                 strength;  // 14
		NiPointer<NiAVObject> target;    // 18
		float                 age;       // 20
		std::uint32_t         flags;     // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceModifierInstance) == 0x28);
}
