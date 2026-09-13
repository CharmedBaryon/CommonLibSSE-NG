#include "RE/B/BSProceduralLightningTasklet.h"

using namespace REL;

namespace RE
{
	void BSProceduralLightningTasklet::Dtor()
	{
		RelocateVirtual<void(BSProceduralLightningTasklet*)>(0x00, 0x00, this);
	}

	void BSProceduralLightningTasklet::Func2()
	{
		RelocateVirtual<decltype(&BSProceduralLightningTasklet::Func2)>(0x02, 0x02, this);
	}

	void BSProceduralLightningTasklet::Func3()
	{
		RelocateVirtual<decltype(&BSProceduralLightningTasklet::Func3)>(0x03, 0x03, this);
	}
}
