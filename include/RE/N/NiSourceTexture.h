#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTexture.h"

namespace RE
{
	namespace BSGraphics
	{
		struct Texture
		{
			ID3D11Texture2D*          texture;       // 00
			uint64_t                  unk08;         // 08
			ID3D11ShaderResourceView* resourceView;  // 10
		};
		static_assert(sizeof(Texture) == 0x18);
	}

	namespace BSResource
	{
		class Stream;
	}

	NiSmartPointer(NiSourceTexture);

	class NiSourceTexture : public NiTexture
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSourceTexture;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSourceTexture;
		inline static constexpr auto VTABLE = VTABLE_NiSourceTexture;

		~NiSourceTexture() override;  // 00

		// override (NiTexture)
		const NiRTTI* GetRTTI() const override;  // 02
		void          Unk_25(void) override;     // 25 - { return 0; }
		void          Unk_26(void) override;     // 26 - { return 0; }
		void          Unk_27(void) override;     // 27
		void          Unk_28(void) override;     // 28
		void          Unk_29(void) override;     // 29 - { return; }
		void          Unk_2A(void) override;     // 2A - { return; }

		// members
		BSResource::Stream*  unk40;            // 40
		BSGraphics::Texture* rendererTexture;  // 48
		std::uint8_t         flags;            // 50
		std::uint8_t         pad51;            // 51
		std::uint16_t        pad52;            // 52
		std::uint32_t        pad54;            // 54
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiSourceTexture) == 0x58);
}
