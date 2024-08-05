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
		REL::Relocation<PlayerControls**> singleton{ RELOCATION_ID(514706, 400864) };
		return *singleton;
	}

	PlayerControls* PlayerControls::Ctor()
	{
		using func_t = decltype(&PlayerControls::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(41257, 42336) };
		return func(this);
	}
}
