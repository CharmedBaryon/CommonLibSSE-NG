#include "RE/M/MenuControls.h"

#include "RE/M/MenuEventHandler.h"
#include "RE/S/ScreenshotHandler.h"

namespace RE
{
	MenuControls::QueuedReg::QueuedReg(MenuEventHandler* a_handler, bool a_add) :
		handler(a_handler),
		add(a_add),
		pad08(0),
		pad09(0),
		pad0A(0)
	{}

	MenuControls* MenuControls::GetSingleton()
	{
		static REL::Relocation<MenuControls**> singleton{ RELOCATION_ID(515124, 401263) };
		return *singleton;
	}

	void MenuControls::AddHandler(MenuEventHandler* a_handler)
	{
		return RegisterHandler(a_handler);
	}

	void MenuControls::GetKeyRepeatRates(float& a_shortRate, float& a_longRate)
	{
		using func_t = decltype(&MenuControls::GetKeyRepeatRates);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51360, 52207) };
		return func(this, a_shortRate, a_longRate);
	}

	void MenuControls::RegisterHandler(MenuEventHandler* a_handler)
	{
		using func_t = decltype(&MenuControls::RegisterHandler);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51358, 52202) };
		return func(this, a_handler);
	}

	void MenuControls::RemoveHandler(MenuEventHandler* a_handler)
	{
		return UnregisterHandler(a_handler);
	}

	bool MenuControls::QueueScreenshot()
	{
		if (!screenshotHandler || screenshotHandler->screenshotQueued) {
			return false;
		}
		screenshotHandler->screenshotQueued = true;
		return true;
	}

	void MenuControls::SetKeyRepeatRates(float a_shortRate, float a_longRate)
	{
		using func_t = decltype(&MenuControls::SetKeyRepeatRates);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51361, 52208) };
		return func(this, a_shortRate, a_longRate);
	}

	void MenuControls::UnregisterHandler(MenuEventHandler* a_handler)
	{
		using func_t = decltype(&MenuControls::UnregisterHandler);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51359, 52203) };
		return func(this, a_handler);
	}
}
