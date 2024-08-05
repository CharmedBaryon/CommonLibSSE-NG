#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class BSUtilityShader : public BSShader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSUtilityShader;
		inline static constexpr auto VTABLE = VTABLE_BSUtilityShader;

		enum class Flags
		{
			None = 0,
			Vc = 1 << 0,
			Texture = 1 << 1,
			Skinned = 1 << 2,
			Normals = 1 << 3,
			BinormalTangent = 1 << 4,
			AlphaTest = 1 << 7,
			LodLandscape = 1 << 8,
			RenderNormal = 1 << 9,
			RenderNormalFalloff = 1 << 10,
			RenderNormalClamp = 1 << 11,
			RenderNormalClear = 1 << 12,
			RenderDepth = 1 << 13,
			RenderShadowmap = 1 << 14,
			RenderShadowmapClamped = 1 << 15,
			GrayscaleToAlpha = 1 << 15,
			RenderShadowmapPb = 1 << 16,
			AdditionalAlphaMask = 1 << 16,
			DepthWriteDecals = 1 << 17,
			DebugShadowSplit = 1 << 18,
			DebugColor = 1 << 19,
			GrayscaleMask = 1 << 20,
			RenderShadowmask = 1 << 21,
			RenderShadowmaskSpot = 1 << 22,
			RenderShadowmaskPb = 1 << 23,
			RenderShadowmaskDpb = 1 << 24,
			RenderBaseTexture = 1 << 25,
			TreeAnim = 1 << 26,
			LodObject = 1 << 27,
			LocalMapFogOfWar = 1 << 28,
			OpaqueEffect = 1 << 29,
		};

		static BSUtilityShader* GetSingleton()
		{
			REL::Relocation<BSUtilityShader**> singleton{ RELOCATION_ID(528354, 415300) };
			return *singleton;
		}
		~BSUtilityShader() override;  // 00

		// override (BSShader)
		bool SetupTechnique(std::uint32_t globalTechnique) override;        // 02
		void RestoreTechnique(std::uint32_t globalTechnique) override;      // 03
		void SetupGeometry(BSRenderPass* pass, uint32_t flags) override;    // 06
		void RestoreGeometry(BSRenderPass* pass, uint32_t flags) override;  // 07

		// members
		std::uint64_t unk90;  // 90
	};
	static_assert(sizeof(BSUtilityShader) == 0x98);
}
