#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	// IMessageBoxCallback for the save-load dialog:
	//   "This save relies on content that is no longer present. Some objects may no longer be
	//    available. Continue Loading?"  (missing masters/plugins).
	// Present in all runtimes (SE/AE/VR). In SE/VR it lives in an anonymous namespace, in AE it is
	// global (hence the generated RTTI___/VTABLE___ names). Run(a_button) receives the selected button
	// index: 1 ("Continue Loading") builds a LoadRequest and submits it to BGSSaveLoadManager; any
	// other value cancels the load.
	// Sibling: LoadGameUnrecognizedContentCallBack (AE-only, the Creations "unrecognized content" dialog).
	class LoadGameMissingContentCallBack : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto             RTTI = RTTI___LoadGameMissingContentCallBack;
		inline static constexpr auto             VTABLE = VTABLE___LoadGameMissingContentCallBack;
		inline static constexpr std::string_view CLASS_NAME = "LoadGameMissingContentCallBack";

		~LoadGameMissingContentCallBack() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  // 01

		// members beyond IMessageBoxCallback (0x10) hold the save-file info used to build the
		// LoadRequest; layout not fully reversed.
	};
}
