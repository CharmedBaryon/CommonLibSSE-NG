#pragma once

#include "RE/I/ImageSpaceData.h"
#include "RE/I/ImageSpaceTexture.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class BSShader;
	class BSTriShape;
	class ImageSpaceEffect;

	class ImageSpaceManager
	{
	public:
		enum ImageSpaceEffectEnum
		{
			WorldMap = 0,                                  // ImageSpaceEffectWorldMap
			Refraction = 1,                                // ImageSpaceEffectRefraction
			ISFXAA = 2,                                    // BSImagespaceShaderFXAA
			DepthOfField = 3,                              // ImageSpaceEffectDepthOfField
			RadialBlur = 5,                                // ImageSpaceEffectRadialBlur
			FullScreenBlur = 6,                            // ImageSpaceEffectFullScreenBlur
			GetHit = 7,                                    // ImageSpaceEffectGetHit
			Map = 8,                                       // ImageSpaceEffectMap
			Blur3 = 9,                                     // ImageSpaceEffectBlur
			Blur5 = 10,                                    // ImageSpaceEffectBlur
			Blur7 = 11,                                    // ImageSpaceEffectBlur
			Blur9 = 12,                                    // ImageSpaceEffectBlur
			Blur11 = 13,                                   // ImageSpaceEffectBlur
			Blur13 = 14,                                   // ImageSpaceEffectBlur
			Blur15 = 15,                                   // ImageSpaceEffectBlur
			BlurNonHDR3 = 16,                              // ImageSpaceEffectBlur
			BlurNonHDR5 = 17,                              // ImageSpaceEffectBlur
			BlurNonHDR7 = 18,                              // ImageSpaceEffectBlur
			BlurNonHDR9 = 19,                              // ImageSpaceEffectBlur
			BlurNonHDR11 = 20,                             // ImageSpaceEffectBlur
			BlurNonHDR13 = 21,                             // ImageSpaceEffectBlur
			BlurNonHDR15 = 22,                             // ImageSpaceEffectBlur
			BlurBrightPass3 = 23,                          // ImageSpaceEffectBlur
			BlurBrightPass5 = 24,                          // ImageSpaceEffectBlur
			BlurBrightPass7 = 25,                          // ImageSpaceEffectBlur
			BlurBrightPass9 = 26,                          // ImageSpaceEffectBlur
			BlurBrightPass11 = 27,                         // ImageSpaceEffectBlur
			BlurBrightPass13 = 28,                         // ImageSpaceEffectBlur
			BlurBrightPass15 = 29,                         // ImageSpaceEffectBlur
			HDR = 30,                                      // ImageSpaceEffectHDR
			WaterDisplacement = 31,                        // ImageSpaceEffectWaterDisplacement
			VolumetricLighting = 32,                       // ImageSpaceEffectVolumetricLighting
			Noise = 33,                                    // ImageSpaceEffectNoise
			ISCopy = 34,                                   // BSImagespaceShaderCopy
			ISCopyDynamicFetchDisabled = 35,               // BSImagespaceShaderCopyDynamicFetchDisabled
			ISCopyScaleBias = 36,                          // BSImagespaceShaderCopyScaleBias
			ISCopyCustomViewport = 37,                     // BSImagespaceShaderCopyCustomViewport
			ISCopyGrayScale = 38,                          // BSImagespaceShaderGreyScale
			ISRefraction = 39,                             // BSImagespaceShaderRefraction
			ISDoubleVision = 40,                           // BSImagespaceShaderDoubleVision
			ISCopyTextureMask = 41,                        // BSImagespaceShaderTextureMask
			ISMap = 42,                                    // BSImagespaceShaderMap
			ISWorldMap = 43,                               // BSImagespaceShaderWorldMap
			ISWorldMapNoSkyBlur = 44,                      // BSImagespaceShaderWorldMapNoSkyBlur
			ISDepthOfField = 45,                           // BSImagespaceShaderDepthOfField
			ISDepthOfFieldFogged = 46,                     // BSImagespaceShaderDepthOfFieldFogged
			ISDepthOfFieldMaskedFogged = 47,               // BSImagespaceShaderDepthOfFieldMaskedFogged
			ISDistantBlur = 49,                            // BSImagespaceShaderDistantBlur
			ISDistantBlurFogged = 50,                      // BSImagespaceShaderDistantBlurFogged
			ISDistantBlurMaskedFogged = 51,                // BSImagespaceShaderDistantBlurMaskedFogged
			ISRadialBlur = 52,                             // BSImagespaceShaderRadialBlur
			ISRadialBlurMedium = 53,                       // BSImagespaceShaderRadialBlurMedium
			ISRadialBlurHigh = 54,                         // BSImagespaceShaderRadialBlurHigh
			ISHDRTonemapBlendCinematic = 55,               // BSImagespaceShaderHDRTonemapBlendCinematic
			ISHDRTonemapBlendCinematicFade = 56,           // BSImagespaceShaderHDRTonemapBlendCinematicFade
			ISHDRDownSample16 = 57,                        // BSImagespaceShaderHDRDownSample16
			ISHDRDownSample4 = 58,                         // BSImagespaceShaderHDRDownSample4
			ISHDRDownSample16Lum = 59,                     // BSImagespaceShaderHDRDownSample16Lum
			ISHDRDownSample4RGB2Lum = 60,                  // BSImagespaceShaderHDRDownSample4RGB2Lum
			ISHDRDownSample4LumClamp = 61,                 // BSImagespaceShaderHDRDownSample4LumClamp
			ISHDRDownSample4LightAdapt = 62,               // BSImagespaceShaderHDRDownSample4LightAdapt
			ISHDRDownSample16LumClamp = 63,                // BSImagespaceShaderHDRDownSample16LumClamp
			ISHDRDownSample16LightAdapt = 64,              // BSImagespaceShaderHDRDownSample16LightAdapt
			ISBlur3 = 65,                                  // BSImagespaceShaderBlur3
			ISBlur5 = 66,                                  // BSImagespaceShaderBlur5
			ISBlur7 = 67,                                  // BSImagespaceShaderBlur7
			ISBlur9 = 68,                                  // BSImagespaceShaderBlur9
			ISBlur11 = 69,                                 // BSImagespaceShaderBlur11
			ISBlur13 = 70,                                 // BSImagespaceShaderBlur13
			ISBlur15 = 71,                                 // BSImagespaceShaderBlur15
			ISNonHDRBlur3 = 72,                            // BSImagespaceShaderNonHDRBlur3
			ISNonHDRBlur5 = 73,                            // BSImagespaceShaderNonHDRBlur5
			ISNonHDRBlur7 = 74,                            // BSImagespaceShaderNonHDRBlur7
			ISNonHDRBlur9 = 75,                            // BSImagespaceShaderNonHDRBlur9
			ISNonHDRBlur11 = 76,                           // BSImagespaceShaderNonHDRBlur11
			ISNonHDRBlur13 = 77,                           // BSImagespaceShaderNonHDRBlur13
			ISNonHDRBlur15 = 78,                           // BSImagespaceShaderNonHDRBlur15
			ISBrightPassBlur3 = 79,                        // BSImagespaceShaderBrightPassBlur3
			ISBrightPassBlur5 = 80,                        // BSImagespaceShaderBrightPassBlur5
			ISBrightPassBlur7 = 81,                        // BSImagespaceShaderBrightPassBlur7
			ISBrightPassBlur9 = 82,                        // BSImagespaceShaderBrightPassBlur9
			ISBrightPassBlur11 = 83,                       // BSImagespaceShaderBrightPassBlur11
			ISBrightPassBlur13 = 84,                       // BSImagespaceShaderBrightPassBlur13
			ISBrightPassBlur15 = 85,                       // BSImagespaceShaderBrightPassBlur15
			ISWaterDisplacementClearSimulation = 86,       // BSImagespaceShaderWaterDisplacementClearSimulation
			ISWaterDisplacementTexOffset = 87,             // BSImagespaceShaderWaterDisplacementTexOffset
			ISWaterDisplacementWadingRipple = 88,          // BSImagespaceShaderWaterDisplacementWadingRipple
			ISWaterDisplacementRainRipple = 89,            // BSImagespaceShaderWaterDisplacementRainRipple
			ISWaterWadingHeightmap = 90,                   // BSImagespaceShaderWaterWadingHeightmap
			ISWaterRainHeightmap = 91,                     // BSImagespaceShaderWaterRainHeightmap
			ISWaterBlendHeightmaps = 92,                   // BSImagespaceShaderWaterBlendHeightmaps
			ISWaterSmoothHeightmap = 93,                   // BSImagespaceShaderWaterSmoothHeightmap
			ISWaterDisplacementNormals = 94,               // BSImagespaceShaderWaterDisplacementNormals
			ISNoiseScrollAndBlend = 95,                    // BSImagespaceShaderNoiseScrollAndBlend
			ISNoiseNormalmap = 96,                         // BSImagespaceShaderNoiseNormalmap
			ISVolumetricLighting = 97,                     // BSImagespaceShaderVolumetricLighting
			ISLocalMap = 98,                               // BSImagespaceShaderLocalMap
			ISAlphaBlend = 99,                             // BSImagespaceShaderAlphaBlend
			ISLensFlare = 100,                             // BSImagespaceShaderLensFlare
			ISLensFlareVisibility = 101,                   // BSImagespaceShaderLensFlareVisibility
			ISApplyReflections = 102,                      // BSImagespaceShaderApplyReflections
			ISApplyVolumetricLighting = 103,               // BSImagespaceShaderISApplyVolumetricLighting
			ISBasicCopy = 104,                             // BSImagespaceShaderISBasicCopy
			ISBlur = 105,                                  // BSImagespaceShaderISBlur
			ISVolumetricLightingBlurHCS = 106,             // BSImagespaceShaderISVolumetricLightingBlurHCS
			ISVolumetricLightingBlurVCS = 107,             // BSImagespaceShaderISVolumetricLightingBlurVCS
			ISReflectionBlurHCS = 108,                     // BSImagespaceShaderReflectionBlurHCS
			ISReflectionBlurVCS = 109,                     // BSImagespaceShaderReflectionBlurVCS
			ISParallaxMaskBlurHCS = 110,                   // BSImagespaceShaderISParallaxMaskBlurHCS
			ISParallaxMaskBlurVCS = 111,                   // BSImagespaceShaderISParallaxMaskBlurVCS
			ISDepthOfFieldBlurHCS = 112,                   // BSImagespaceShaderISDepthOfFieldBlurHCS
			ISDepthOfFieldBlurVCS = 113,                   // BSImagespaceShaderISDepthOfFieldBlurVCS
			ISCompositeVolumetricLighting = 114,           // BSImagespaceShaderISCompositeVolumetricLighting
			ISCompositeLensFlare = 115,                    // BSImagespaceShaderISCompositeLensFlare
			ISCompositeLensFlareVolumetricLighting = 116,  // BSImagespaceShaderISCompositeLensFlareVolumetricLighting
			ISCopySubRegionCS = 117,                       // BSImagespaceShaderISCopySubRegionCS
			ISDebugSnow = 118,                             // BSImagespaceShaderISDebugSnow
			ISDownsample = 119,                            // BSImagespaceShaderISDownsample
			ISDownsampleIgnoreBrightest = 120,             // BSImagespaceShaderISDownsampleIgnoreBrightest
			ISDownsampleCS = 121,                          // BSImagespaceShaderISDownsampleCS
			ISDownsampleIgnoreBrightestCS = 122,           // BSImagespaceShaderISDownsampleIgnoreBrightestCS
			ISExp = 123,                                   // BSImagespaceShaderISExp
			ISIBLensFlares = 124,                          // BSImagespaceShaderISIBLensFlares
			ISLightingComposite = 125,                     // BSImagespaceShaderISLightingComposite
			ISLightingCompositeNoDirectionalLight = 126,   // BSImagespaceShaderISLightingCompositeNoDirectionalLight
			ISLightingCompositeMenu = 127,                 // BSImagespaceShaderISLightingCompositeMenu
			ISPerlinNoiseCS = 128,                         // BSImagespaceShaderISPerlinNoiseCS
			ISPerlinNoise2DCS = 129,                       // BSImagespaceShaderISPerlinNoise2DCS
			ISReflectionsRayTracing = 130,                 // BSImagespaceShaderReflectionsRayTracing
			ISReflectionsDebugSpecMask = 131,              // BSImagespaceShaderReflectionsDebugSpecMask
			ISSAOBlurH = 132,                              // BSImagespaceShaderISSAOBlurH
			ISSAOBlurV = 133,                              // BSImagespaceShaderISSAOBlurV
			ISSAOBlurHCS = 134,                            // BSImagespaceShaderISSAOBlurHCS
			ISSAOBlurVCS = 135,                            // BSImagespaceShaderISSAOBlurVCS
			ISSAOCameraZ = 136,                            // BSImagespaceShaderISSAOCameraZ
			ISSAOCameraZAndMipsCS = 137,                   // BSImagespaceShaderISSAOCameraZAndMipsCS
			ISSAOCompositeSAO = 138,                       // BSImagespaceShaderISSAOCompositeSAO
			ISSAOCompositeFog = 139,                       // BSImagespaceShaderISSAOCompositeFog
			ISSAOCompositeSAOFog = 140,                    // BSImagespaceShaderISSAOCompositeSAOFog
			ISMinify = 141,                                // BSImagespaceShaderISMinify
			ISMinifyContrast = 142,                        // BSImagespaceShaderISMinifyContrast
			ISSAORawAO = 143,                              // BSImagespaceShaderISSAORawAO
			ISSAORawAONoTemporal = 144,                    // BSImagespaceShaderISSAORawAONoTemporal
			ISSAORawAOCS = 145,                            // BSImagespaceShaderISSAORawAOCS
			ISSILComposite = 146,                          // BSImagespaceShaderISSILComposite
			ISSILRawInd = 147,                             // BSImagespaceShaderISSILRawInd
			ISSimpleColor = 148,                           // BSImagespaceShaderISSimpleColor
			ISDisplayDepth = 149,                          // BSImagespaceShaderISDisplayDepth
			ISSnowSSS = 150,                               // BSImagespaceShaderISSnowSSS
			ISTemporalAA = 151,                            // BSImagespaceShaderISTemporalAA
			ISTemporalAA_UI = 152,                         // BSImagespaceShaderISTemporalAA_UI
			ISTemporalAA_Water = 153,                      // BSImagespaceShaderISTemporalAA_Water
			ISUpsampleDynamicResolution = 154,             // BSImagespaceShaderISUpsampleDynamicResolution
			ISWaterBlend = 155,                            // BSImagespaceShaderISWaterBlend
			ISUnderwaterMask = 156,                        // BSImagespaceShaderISUnderwaterMask
			ISWaterFlow = 157,                             // BSImagespaceShaderWaterFlow

			Total = 159
		};

		struct UNK_BSImagespaceShaderISTemporalAA
		{
			BSImagespaceShaderISTemporalAA* shader;                                // 00
			BSImagespaceShader*             BSImagespaceShaderISTemporalAA_UI;     // 08
			BSImagespaceShader*             BSImagespaceShaderISTemporalAA_Water;  // 10
			bool                            taaEnabled;                            // 18
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                                                                                     \
	std::uint8_t        unk58;                                                           /* 058, VR 68 */                                                                                        \
	std::uint32_t       unk5C;                                                           /* 05C, VR 68 */                                                                                        \
	std::uint32_t       unk60;                                                           /* 060, VR 6C */                                                                                        \
	RENDER_TARGET       renderTarget;                                                    /* 064, VR 70 */                                                                                        \
	std::uint32_t       unk68;                                                           /* 068, VR 74 */                                                                                        \
	std::uint32_t       unk6C;                                                           /* 06C, VR 78 */                                                                                        \
	std::uint32_t       unk70;                                                           /* 070, VR 7C */                                                                                        \
	float               unk74;                                                           /* 074, VR 80 */                                                                                        \
	ImageSpaceTexture   unk78;                                                           /* 078, VR 88 */                                                                                        \
	NiColorA            refractionTint;                                                  /* 098, VR A8 */                                                                                        \
	ImageSpaceBaseData* currentBaseData;                                                 /* 0A8, VR B8 */                                                                                        \
	ImageSpaceBaseData* overrideBaseData;                                                /* 0B0, VR C0 */                                                                                        \
	ImageSpaceBaseData* underwaterBaseData;                                              /* 0B8, VR C8 */                                                                                        \
	ImageSpaceBaseData* consoleBaseData;                                                 /* 0C0, VR D0 */                                                                                        \
	ImageSpaceData      data;                                                            /* 0C8, VR D8 */                                                                                        \
																						 /* the structure is unclear and varies for each, but at least the first entry is a BSImagespaceShader*/ \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderApplyReflections;              /* 168, VR 178 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISApplyVolumetricLighting;     /* 170, VR 180 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISBasicCopy;                   /* 178, VR 188 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISBlur;                        /* 180, VR 190 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISVolumetricLightingBlurHCS;   /* 188, VR 198 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISCompositeVolumetricLighting; /* 190, VR 1A0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISCopySubRegionCS;             /* 198, VR 1A8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISDebugSnow;                   /* 1A0, VR 1B0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISExp;                         /* 1A8, VR 1C0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISLightingComposite;           /* 1B0, VR 1D0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISPerlinNoiseCS;               /* 1B8, VR 1D8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderReflectionsRayTracing;         /* 1C0, VR 1E8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSAOBlurH;                    /* 1C8, VR 1F0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSAOBlurHCS;                  /* 1D0, VR 1F8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSILComposite;                /* 1D8, VR 200 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSimpleColor;                 /* 1E0, VR 208 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSnowSSS;                     /* 1E8, VR 210 */                                                                                       \
	UNK_BSImagespaceShaderISTemporalAA* BSImagespaceShaderISTemporalAA;                  /* 1F0, VR 218 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISUpsampleDynamicResolution;   /* 1F8, VR 220 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISWaterBlend;                  /* 200, VR 228 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISUnderwaterMask;              /* 208, VR 230 */                                                                                       \
	bool                                usesLDR;                                         /* 210, VR 238 */                                                                                       \
	bool                                unk211;                                          /* 211, VR 239 */                                                                                       \
	std::uint64_t                       unk218;                                          /* 218, VR 240 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x1C8);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                                                                                                          \
	NiPointer<BSTriShape> VRunk58;                                                               /* VR 058 */                                                                                            \
	NiPointer<BSTriShape> VRunk60;                                                               /* VR 060 */                                                                                            \
	std::uint32_t         unk5C;                                                                 /* 05C, VR 68 */                                                                                        \
	std::uint32_t         unk60;                                                                 /* 060, VR 6C */                                                                                        \
	RENDER_TARGET         renderTarget;                                                          /* 064, VR 70 */                                                                                        \
	std::uint32_t         unk68;                                                                 /* 068, VR 74 */                                                                                        \
	std::uint32_t         unk6C;                                                                 /* 06C, VR 78 */                                                                                        \
	std::uint32_t         unk70;                                                                 /* 070, VR 7C */                                                                                        \
	float                 VRunk84;                                                               /* VR, 84*/                                                                                             \
	float                 unk74;                                                                 /* 074, VR 80 */                                                                                        \
	ImageSpaceTexture     unk78;                                                                 /* 078, VR 88 */                                                                                        \
	NiColorA              refractionTint;                                                        /* 098, VR A8 */                                                                                        \
	ImageSpaceBaseData*   currentBaseData;                                                       /* 0A8, VR B8 */                                                                                        \
	ImageSpaceBaseData*   overrideBaseData;                                                      /* 0B0, VR C0 */                                                                                        \
	ImageSpaceBaseData*   underwaterBaseData;                                                    /* 0B8, VR C8 */                                                                                        \
	ImageSpaceBaseData*   consoleBaseData;                                                       /* 0C0, VR D0 */                                                                                        \
	ImageSpaceData        data;                                                                  /* 0C8, VR D8 */                                                                                        \
																								 /* the structure is unclear and varies for each, but at least the first entry is a BSImagespaceShader*/ \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderApplyReflections;                      /* 168, VR 178 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISApplyVolumetricLighting;             /* 170, VR 180 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISBasicCopy;                           /* 178, VR 188 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISBlur;                                /* 180, VR 190 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISVolumetricLightingBlurHCS;           /* 188, VR 198 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISCompositeVolumetricLighting;         /* 190, VR 1A0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISCopySubRegionCS;                     /* 198, VR 1A8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISDebugSnow;                           /* 1A0, VR 1B0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISDownsampleHierarchicalDepthBufferCS; /* VR, 1B8 */                                                                                           \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISExp;                                 /* 1A8, VR 1C0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISFullScreenVR;                        /* VR 1C8 */                                                                                            \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISLightingComposite;                   /* 1B0, VR 1D0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISPerlinNoiseCS;                       /* 1B8, VR 1D8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderTransformLvl7PreTest;                  /* VR 1E0 */                                                                                            \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderReflectionsRayTracing;                 /* 1C0, VR 1E8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSAOBlurH;                            /* 1C8, VR 1F0 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSAOBlurHCS;                          /* 1D0, VR 1F8 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSILComposite;                        /* 1D8, VR 200 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSimpleColor;                         /* 1E0, VR 208 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISSnowSSS;                             /* 1E8, VR 210 */                                                                                       \
	UNK_BSImagespaceShaderISTemporalAA* BSImagespaceShaderISTemporalAA;                          /* 1F0, VR 218 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISUpsampleDynamicResolution;           /* 1F8, VR 220 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISWaterBlend;                          /* 200, VR 228 */                                                                                       \
	NiPointer<BSImagespaceShader>       BSImagespaceShaderISUnderwaterMask;                      /* 208, VR 230 */                                                                                       \
	bool                                usesLDR;                                                 /* 210, VR 238 */                                                                                       \
	bool                                unk211;                                                  /* 211, VR 239 */                                                                                       \
	std::uint64_t                       unk218;                                                  /* 218, VR 240 */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x1F0);
		static ImageSpaceManager* GetSingleton()
		{
			REL::Relocation<ImageSpaceManager**> singleton{ RELOCATION_ID(527731, 414660) };
			return *singleton;
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0);
		}

		[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x58);
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x58);
		}

		// members
		std::uint64_t                        unk00;       /* 000 */
		std::uint64_t                        unk08;       /* 008 */
		std::int32_t                         unk10;       /* 010 */
		std::int32_t                         unk14;       /* 014 */
		std::uint64_t                        unk18;       /* 018 */
		NiTPrimitiveArray<ImageSpaceEffect*> effects;     /* 020 */
		bool                                 initEffects; /* 038 */
		std::uint32_t                        unk3C;       /* 03C */
		std::int32_t                         unk40;       /* 040 */
		NiPointer<BSTriShape>                unk48;       /* 048 */
		NiPointer<BSTriShape>                unk50;       /* 050 */
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(ImageSpaceManager) == 0x220);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ImageSpaceManager) == 0x248);
#else
	static_assert(sizeof(ImageSpaceManager) == 0x58);

#endif
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
