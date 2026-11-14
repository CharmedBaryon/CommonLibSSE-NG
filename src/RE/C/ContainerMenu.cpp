#include "RE/C/ContainerMenu.h"

namespace RE
{
	ContainerMenu::ContainerMode ContainerMenu::GetContainerMode()
	{
		static REL::Relocation<ContainerMode*> mode{ RELOCATION_ID(519396, 405937) };
		return *mode;
	}

	RefHandle ContainerMenu::GetTargetRefHandle()
	{
		static REL::Relocation<RefHandle*> handle{ RELOCATION_ID(519421, 405962) };
		return *handle;
	}

	void ContainerMenu::OpenMenu(TESObjectREFR* a_target, ContainerMenu::ContainerMode a_mode)
	{
		using func_t = decltype(&ContainerMenu::OpenMenu);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50211, 51140) };
		return func(a_target, a_mode);
	}
}
