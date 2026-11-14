#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	namespace BSAttachTechniques
	{
		struct AttachTechniqueInput
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSAttachTechniques__AttachTechniqueInput;
			inline static constexpr auto VTABLE = VTABLE_BSAttachTechniques__AttachTechniqueInput;

			virtual ~AttachTechniqueInput();  // 00

			// add
			virtual void Clear();  // 01

			// members
			NiPointer<NiNode> current3DRoot;  // 08 - smart ptr
			NiPointer<NiNode> attachedArt;    // 10 - smart ptr
			std::uint32_t     attachPoint;    // 18 - MagicSystem::CastingSource for casting art
			std::uint32_t     pad18;          // 18
		};
		static_assert(sizeof(AttachTechniqueInput) == 0x20);
	}
}
