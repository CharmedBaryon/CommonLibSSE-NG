#pragma once

#include "RE/A/AttachTechniqueInput.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	class TESRace;
	class bhkWorld;

	class RefAttachTechniqueInput : public BSAttachTechniques::AttachTechniqueInput
	{
	public:
		inline static constexpr auto RTTI = RTTI_RefAttachTechniqueInput;
		inline static constexpr auto VTABLE = VTABLE_RefAttachTechniqueInput;

		~RefAttachTechniqueInput() override;  // 00

		// override (BSAttachTechniques::AttachTechniqueInput)
		void Clear() override;  // 01

		// members
		TESObjectREFR* actor;            // 20
		TESRace*       actorRace;        // 28
		bhkWorld*      physicsWorld;     // 30
		std::uint32_t  collisionFilter;  // 38
		std::uint32_t  unk3C;            // 3C
		BSFixedString  nodeName;         // 40
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(RefAttachTechniqueInput) == 0x48);
}
