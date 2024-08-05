#pragma once

#include "RE/I/ImageSpaceEffectOption.h"
#include "RE/I/ImageSpaceTexture.h"

namespace RE
{
	class ImageSpaceEffectDepthOfField : public ImageSpaceEffectOption
	{
	public:
		inline static constexpr auto RTTI = RTTI_ImageSpaceEffectDepthOfField;
		inline static constexpr auto VTABLE = VTABLE_ImageSpaceEffectDepthOfField;

		~ImageSpaceEffectDepthOfField() override;  // 00

		// override (ImageSpaceEffectOption)
		void Render(BSTriShape* a_shape, ImageSpaceEffectParam* a_param) override;          // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override;  // 02
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;                       // 04
		void ReturnTextures() override;                                                     // 05
		bool IsActive() override;                                                           // 06
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;                         // 07

		// members
		std::uint64_t     unk0A8;     // 0A8
		std::uint32_t     unk0B0;     // 0B0
		std::uint32_t     unk0B4;     // 0B4
		std::uint32_t     unk0B8;     // 0B8
		std::uint32_t     unk0BC;     // 0BC
		std::uint8_t      unk0C0;     // 0C0
		std::uint8_t      unk0C1;     // 0C1
		std::uint16_t     unk0C2;     // 0C2
		std::uint32_t     unk0C4;     // 0C4
		ImageSpaceTexture unk0C8[4];  // 0C8
		bool              enabled;    // 148
		float             unk14C;     // 14C
		float             unk150;     // 150
		std::uint32_t     pad154;     // 154
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ImageSpaceEffectDepthOfField) == 0x158);
}
