#pragma once

#include "RE/B/BSTHashMap.h"
#include "RE/G/GFxImageLoader.h"
#include "RE/G/GPtr.h"

namespace RE
{
	class BSScaleformExternalTexture;
	class GTexture;
	class NiTexture;

	class BSScaleformImageLoader : public GFxImageLoader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSScaleformImageLoader;
		inline static constexpr auto VTABLE = VTABLE_BSScaleformImageLoader;

		class TextureEntry
		{
		public:
			GPtr<GTexture> texture;        // 00
			NiTexture*     sourceTexture;  // 08
			std::uint32_t  refCount;       // 10
			std::uint32_t  pad14;          // 14
		};
		static_assert(sizeof(TextureEntry) == 0x18);

		virtual ~BSScaleformImageLoader();  // 00

		// override (GFxImageLoader)
		GImageInfoBase* LoadImage(const char* a_url) override;  // 01

		bool AddTexture(BSScaleformExternalTexture& a_texture)
		{
			using func_t = decltype(&BSScaleformImageLoader::AddTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(82382, 84469) };
			return func(this, a_texture);
		}

		void RemoveTexture(BSScaleformExternalTexture& a_texture)
		{
			using func_t = decltype(&BSScaleformImageLoader::RemoveTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(82383, 84470) };
			return func(this, a_texture);
		}

		// members
		BSTHashMap<std::uint32_t, TextureEntry> textures;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSScaleformImageLoader) == 0x48);
}
