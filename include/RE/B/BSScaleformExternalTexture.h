#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiTexture.h"

namespace RE
{
	class BSScaleformExternalTexture
	{
	public:
		BSScaleformExternalTexture() :
			gamebryoTexture{ nullptr },
			renderTarget(0),
			pad0C(0)
		{}

		~BSScaleformExternalTexture()
		{
			ReleaseTexture();
		}

		BSScaleformExternalTexture(const BSScaleformExternalTexture&) = delete;
		BSScaleformExternalTexture(BSScaleformExternalTexture&&) = delete;
		BSScaleformExternalTexture& operator=(const BSScaleformExternalTexture&) = delete;
		BSScaleformExternalTexture& operator=(BSScaleformExternalTexture&&) = delete;

		bool LoadPNG(const BSFixedString& a_path)
		{
			using func_t = decltype(&BSScaleformExternalTexture::LoadPNG);
			static REL::Relocation<func_t> func{ RELOCATION_ID(80298, 82321) };
			return func(this, a_path);
		}

		void ReleaseTexture()
		{
			using func_t = decltype(&BSScaleformExternalTexture::ReleaseTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(80294, 82317) };
			return func(this);
		}

		bool SetTexture(NiTexture* a_texture)
		{
			using func_t = decltype(&BSScaleformExternalTexture::SetTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(80295, 82318) };
			return func(this, a_texture);
		}

		// members
		NiPointer<NiTexture> gamebryoTexture;  // 00
		std::uint32_t        renderTarget;     // 08
		std::uint32_t        pad0C;            // 0C
		BSFixedString        filePath;         // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSScaleformExternalTexture) == 0x18);
}
