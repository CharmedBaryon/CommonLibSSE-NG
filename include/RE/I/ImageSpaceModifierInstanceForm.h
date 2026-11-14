#pragma once

#include "RE/I/ImageSpaceModifierInstance.h"

namespace RE
{
	class TESImageSpaceModifier;

	class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceModifierInstanceForm;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceModifierInstanceForm;

		~ImageSpaceModifierInstanceForm() override;  // 00

		// override (ImageSpaceModifierInstance)
		bool                            Unk_25(void) override;               // 25
		void                            Apply() override;                    // 26
		ImageSpaceModifierInstanceForm* IsForm() override;                   // 27
		void                            PrintInfo(char* a_dstBuf) override;  // 28

		static ImageSpaceModifierInstanceForm* Trigger(TESImageSpaceModifier* a_imod, float a_strength, NiAVObject* a_target)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::Trigger);
			static REL::Relocation<func_t> func{ RELOCATION_ID(18185, 18570) };
			return func(a_imod, a_strength, a_target);
		}

		static void Stop(TESImageSpaceModifier* a_imod)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::Stop);
			static REL::Relocation<func_t> func{ RELOCATION_ID(18188, 18573) };
			return func(a_imod);
		}

		// Retargets an already-active instance. Returns false without effect if either the current or
		// new (node) target has a lock-like flag set (checked at +0x20 on both).
		bool SetTarget(TESImageSpaceModifier* a_imod, float a_transitionTime, float a_duration, NiAVObject* a_target)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::SetTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(18183, 18568) };
			return func(this, a_imod, a_transitionTime, a_duration, a_target);
		}

		static void StopCrossFade(float a_seconds)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::StopCrossFade);
			static REL::Relocation<func_t> func{ RELOCATION_ID(18192, 18577) };
			return func(a_seconds);
		}

		// members
		TESImageSpaceModifier* imod;   // 28
		std::uint64_t          unk30;  // 30
		float                  unk38;  // 38
		std::uint32_t          unk3C;  // 3C
		std::uint64_t          unk40;  // 40
		std::uint32_t          unk48;  // 48
	};
	static_assert(sizeof(ImageSpaceModifierInstanceForm) == 0x50);
}
