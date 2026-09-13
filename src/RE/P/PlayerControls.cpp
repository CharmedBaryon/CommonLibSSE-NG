#include "RE/P/PlayerControls.h"

#include "RE/A/ActivateHandler.h"
#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	PlayerControls::PlayerControls()
	{
		Ctor();
	}

	PlayerControls* PlayerControls::GetSingleton()
	{
		static REL::Relocation<PlayerControls**> singleton{ RELOCATION_ID(514706, 400864) };
		return *singleton;
	}

	PlayerControls* PlayerControls::Ctor()
	{
		using func_t = decltype(&PlayerControls::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(41257, 42336) };
		return func(this);
	}

	void PlayerControls::RegisterHandler(PlayerInputHandler* a_handler, bool a_addToHeldStateHandlers)
	{
		using func_t = decltype(&PlayerControls::RegisterHandler);
		static REL::Relocation<func_t> func{ RELOCATION_ID(41277, 42356) };
		return func(this, a_handler, a_addToHeldStateHandlers);
	}

	void PlayerControls::UnregisterHandler(PlayerInputHandler* a_handler)
	{
		using func_t = decltype(&PlayerControls::UnregisterHandler);
		static REL::Relocation<func_t> func{ RELOCATION_ID(41278, 42357) };
		return func(this, a_handler);
	}
}
