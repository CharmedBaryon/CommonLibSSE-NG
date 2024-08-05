#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiObject.h"
#include "RE/N/NiSmartPointer.h"

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

namespace RE
{
	NiSmartPointer(NiTexture);

	class NiTexture : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTexture;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTexture;
		inline static constexpr auto VTABLE = VTABLE_NiTexture;

		class FormatPrefs
		{
		public:
			enum class PixelLayout
			{
				kPalettized8,
				kHighColor16,
				kTrueColor32,
				kCompressed,
				kBumpmap,
				kPalettized4,
				kDefault,
				kSingleColor8,
				kSingleColor16,
				kSingleColor32,
				kDoubleColor32,
				kDoubleColor64,
				kFloatColor32,
				kFloatColor64,
				kFloatColor128
			};

			enum class AlphaFormat
			{
				kNone,
				kBinary,  // 1-bit
				kSmooth,  // multi-bit
				kDefault
			};

			enum class MipFlag
			{
				kNo = 0,
				kYes = 1,
				kDefault
			};

			FormatPrefs();

			// members
			stl::enumeration<PixelLayout, std::uint32_t> pixelLayout;  // 00
			stl::enumeration<AlphaFormat, std::uint32_t> alphaFormat;  // 04
			stl::enumeration<MipFlag, std::uint32_t>     mipMapped;    // 08
			std::uint32_t                                pad0C;        // 0C
		};
		static_assert(sizeof(FormatPrefs) == 0x10);

		class RendererData
		{
		public:
			RendererData(std::uint16_t width, std::uint16_t height) noexcept :
				width(width), height(height) {}

			ID3D11Texture2D*          texture{ nullptr };       // 00
			std::uint64_t             unk08{ 0 };               // 08
			ID3D11ShaderResourceView* resourceView{ nullptr };  // 10
			std::uint16_t             width;                    // 18
			std::uint16_t             height;                   // 1A
			std::uint8_t              unk1C{ 1 };               // 1C
			std::uint8_t              unk1D{ 0x1C };            // 1D
			std::uint16_t             unk1E{ 0 };               // 1E
			std::uint32_t             unk20{ 1 };               // 20
			std::uint32_t             unk24{ 0x130012 };        // 24

			TES_HEAP_REDEFINE_NEW();
		};
		static_assert(sizeof(RendererData) == 0x28);

		~NiTexture() override;

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;  // 02

		// add
		virtual void Unk_25(void);  // 25 - { return 0; }
		virtual void Unk_26(void);  // 26 - { return 0; }
		virtual void Unk_27(void);  // 27 - { return "n/a"; }
		virtual void Unk_28(void);  // 28
		virtual void Unk_29(void);  // 29 - { return 0; }
		virtual void Unk_2A(void);  // 2A - { return 0; }

		// members
		FormatPrefs   formatPrefs;  // 10
		BSFixedString name;         // 20
		std::uint32_t unk28;        // 28
		std::uint32_t unk2C;        // 2C
		NiTexture*    prev;         // 30
		NiTexture*    next;         // 38
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiTexture) == 0x40);
}
