#pragma once

#include "RE/G/GImageInfoBaseImpl.h"

namespace RE
{
	class GImageInfo : public GImageInfoBaseImpl
	{
	public:
		~GImageInfo() override;  // 00

		// override (GImageInfoImpl)
		std::uint32_t GetWidth() const override;                   // 01
		std::uint32_t GetHeight() const override;                  // 02
		GTexture*     GetTexture(GRenderer* a_renderer) override;  // 03
		std::uint32_t GetImageInfoType() const override;           // 06

		// override (GTexture::ChangeHandler)
		void OnChange(GRenderer* a_renderer, EventType a_changeType) override;  // 01
		bool Recreate(GRenderer* a_renderer) override;                          // 02

		// members
		GPtr<GImage>  image;         // 28
		std::uint32_t targetWidth;   // 30
		std::uint32_t targetHeight;  // 34
		bool          releaseImage;  // 38
		std::uint8_t  pad39;         // 39
		std::uint16_t pad3A;         // 3A
		std::uint32_t pad3C;         // 3C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GImageInfo) == 0x40);
}
