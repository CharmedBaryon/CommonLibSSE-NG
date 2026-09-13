#pragma once

#include "RE/H/HUDObject.h"

namespace RE
{
	class Compass : public HUDObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_Compass;
		inline static constexpr auto VTABLE = VTABLE_Compass;

		Compass(GFxMovieView* a_view);
		~Compass() override = default;  // 00

		//override HUDObject
		void Update() override;                                        // 01
		bool ProcessMessage(UIMessage* a_message) override;            // 02
		void RegisterHUDComponent(FxDelegateArgs& a_params) override;  // 03
		void CleanUp() override;                                       // 04

		TES_HEAP_REDEFINE_NEW();

		GFxValue compassTargetData;  // 28
	};
	static_assert(sizeof(Compass) == 0x40);
}