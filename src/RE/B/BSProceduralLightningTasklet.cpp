#include "RE/B/BSProceduralLightningTasklet.h"

using namespace REL;

namespace RE
{
	void BSProceduralLightningTasklet::Dtor()
	{
		RelocateVirtual<void(BSProceduralLightningTasklet*)>(0x00, 0x00, this);
	}

	void BSProceduralLightningTasklet::Process()
	{
		RelocateVirtual<decltype(&BSProceduralLightningTasklet::Process)>(0x02, 0x02, this);
	}

	void BSProceduralLightningTasklet::OnComplete()
	{
		RelocateVirtual<decltype(&BSProceduralLightningTasklet::OnComplete)>(0x03, 0x03, this);
	}
}
