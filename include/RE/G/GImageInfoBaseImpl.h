#pragma once

#include "RE/G/GImageInfoBase.h"

namespace RE
{
	class GImageInfoBaseImpl : public GImageInfoBase
	{
	public:
		~GImageInfoBaseImpl() override;  // 00

		// override (GImageInfoBase)
		GTexture* GetTexture(GRenderer* a_renderer) override;  // 03

		// override (GTexture::ChangeHandler)
		void OnChange(GRenderer* a_renderer, EventType a_changeType);  // 01

		// members
		GPtr<GTexture> texture;       // 18
		std::uint32_t  textureUsage;  // 20
		std::uint32_t  pad24;         // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GImageInfoBaseImpl) == 0x28);
}
