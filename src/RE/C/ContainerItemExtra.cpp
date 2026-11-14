#include "RE/C/ContainerItemExtra.h"
#include "RE/T/TESForm.h"

namespace RE
{
	ContainerItemExtra::Conditional::Conditional() :
		global(nullptr)
	{}

	ContainerItemExtra::ContainerItemExtra() :
		ContainerItemExtra(nullptr)
	{}

	ContainerItemExtra::ContainerItemExtra(TESForm* a_owner) :
		owner(a_owner),
		conditional(),
		healthMult(1.0f),
		pad14(0)
	{}
}
