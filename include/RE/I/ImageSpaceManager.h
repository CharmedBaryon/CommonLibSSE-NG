#pragma once

#include "RE/I/ImageSpaceData.h"
#include "RE/I/ImageSpaceTexture.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiRect.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"
#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

namespace RE
{
	class BSImagespaceShader;
	class BSImagespaceShaderISTemporalAA;
	class BSShader;
	class BSTriShape;
	class ImageSpaceEffect;

	class ImageSpaceManager
	{
	public:
#define IMAGE_SPACE_EFFECTS                                                                                                     \
	X(WorldMap, 0)     /* ImageSpaceEffectWorldMap */                                                                           \
	X(Refraction, 1)   /* ImageSpaceEffectRefraction */                                                                         \
	X(ISFXAA, 2)       /* BSImagespaceShaderFXAA */                                                                             \
	X(DepthOfField, 3) /* ImageSpaceEffectDepthOfField */                                                                       \
	/* Missing SE 4 */                                                                                                          \
	X(RadialBlur, 5)                  /* ImageSpaceEffectRadialBlur */                                                          \
	X(FullScreenBlur, 6)              /* ImageSpaceEffectFullScreenBlur */                                                      \
	X(GetHit, 7)                      /* ImageSpaceEffectGetHit */                                                              \
	X(Map, 8)                         /* ImageSpaceEffectMap */                                                                 \
	X(Blur3, 9)                       /* ImageSpaceEffectBlur */                                                                \
	X(Blur5, 10)                      /* ImageSpaceEffectBlur */                                                                \
	X(Blur7, 11)                      /* ImageSpaceEffectBlur */                                                                \
	X(Blur9, 12)                      /* ImageSpaceEffectBlur */                                                                \
	X(Blur11, 13)                     /* ImageSpaceEffectBlur */                                                                \
	X(Blur13, 14)                     /* ImageSpaceEffectBlur */                                                                \
	X(Blur15, 15)                     /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR3, 16)                /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR5, 17)                /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR7, 18)                /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR9, 19)                /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR11, 20)               /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR13, 21)               /* ImageSpaceEffectBlur */                                                                \
	X(BlurNonHDR15, 22)               /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass3, 23)            /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass5, 24)            /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass7, 25)            /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass9, 26)            /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass11, 27)           /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass13, 28)           /* ImageSpaceEffectBlur */                                                                \
	X(BlurBrightPass15, 29)           /* ImageSpaceEffectBlur */                                                                \
	X(HDR, 30)                        /* ImageSpaceEffectHDR */                                                                 \
	X(WaterDisplacement, 31)          /* ImageSpaceEffectWaterDisplacement */                                                   \
	X(VolumetricLighting, 32)         /* ImageSpaceEffectVolumetricLighting */                                                  \
	X(Noise, 33)                      /* ImageSpaceEffectNoise */                                                               \
	X(ISCopy, 34)                     /* BSImagespaceShaderCopy */                                                              \
	X(ISCopyDynamicFetchDisabled, 35) /* BSImagespaceShaderCopyDynamicFetchDisabled */                                          \
	X(ISCopyScaleBias, 36)            /* BSImagespaceShaderCopyScaleBias */                                                     \
	X(ISCopyCustomViewport, 37)       /* BSImagespaceShaderCopyCustomViewport */                                                \
	X(ISCopyGrayScale, 38)            /* BSImagespaceShaderGreyScale */                                                         \
	X(ISRefraction, 39)               /* BSImagespaceShaderRefraction */                                                        \
	X(ISDoubleVision, 40)             /* BSImagespaceShaderDoubleVision */                                                      \
	X(ISCopyTextureMask, 41)          /* BSImagespaceShaderTextureMask */                                                       \
	X(ISMap, 42)                      /* BSImagespaceShaderMap */                                                               \
	X(ISWorldMap, 43)                 /* BSImagespaceShaderWorldMap */                                                          \
	X(ISWorldMapNoSkyBlur, 44)        /* BSImagespaceShaderWorldMapNoSkyBlur */                                                 \
	X(ISDepthOfField, 45)             /* BSImagespaceShaderDepthOfField */                                                      \
	X(ISDepthOfFieldFogged, 46)       /* BSImagespaceShaderDepthOfFieldFogged */                                                \
	X(ISDepthOfFieldMaskedFogged, 47) /* BSImagespaceShaderDepthOfFieldMaskedFogged */                                          \
	/* Missing SE 48 */                                                                                                         \
	X(ISDistantBlur, 49)                                 /* BSImagespaceShaderDistantBlur */                                    \
	X(ISDistantBlurFogged, 50)                           /* BSImagespaceShaderDistantBlurFogged */                              \
	X(ISDistantBlurMaskedFogged, 51)                     /* BSImagespaceShaderDistantBlurMaskedFogged */                        \
	X(ISRadialBlur, 52)                                  /* BSImagespaceShaderRadialBlur */                                     \
	X(ISRadialBlurMedium, 53)                            /* BSImagespaceShaderRadialBlurMedium */                               \
	X(ISRadialBlurHigh, 54)                              /* BSImagespaceShaderRadialBlurHigh */                                 \
	X(ISHDRTonemapBlendCinematic, 55)                    /* BSImagespaceShaderHDRTonemapBlendCinematic */                       \
	X(ISHDRTonemapBlendCinematicFade, 56)                /* BSImagespaceShaderHDRTonemapBlendCinematicFade */                   \
	X(ISHDRDownSample16, 57)                             /* BSImagespaceShaderHDRDownSample16 */                                \
	X(ISHDRDownSample4, 58)                              /* BSImagespaceShaderHDRDownSample4 */                                 \
	X(ISHDRDownSample16Lum, 59)                          /* BSImagespaceShaderHDRDownSample16Lum */                             \
	X(ISHDRDownSample4RGB2Lum, 60)                       /* BSImagespaceShaderHDRDownSample4RGB2Lum */                          \
	X(ISHDRDownSample4LumClamp, 61)                      /* BSImagespaceShaderHDRDownSample4LumClamp */                         \
	X(ISHDRDownSample4LightAdapt, 62)                    /* BSImagespaceShaderHDRDownSample4LightAdapt */                       \
	X(ISHDRDownSample16LumClamp, 63)                     /* BSImagespaceShaderHDRDownSample16LumClamp */                        \
	X(ISHDRDownSample16LightAdapt, 64)                   /* BSImagespaceShaderHDRDownSample16LightAdapt */                      \
	X(ISBlur3, 65)                                       /* BSImagespaceShaderBlur3 */                                          \
	X(ISBlur5, 66)                                       /* BSImagespaceShaderBlur5 */                                          \
	X(ISBlur7, 67)                                       /* BSImagespaceShaderBlur7 */                                          \
	X(ISBlur9, 68)                                       /* BSImagespaceShaderBlur9 */                                          \
	X(ISBlur11, 69)                                      /* BSImagespaceShaderBlur11 */                                         \
	X(ISBlur13, 70)                                      /* BSImagespaceShaderBlur13 */                                         \
	X(ISBlur15, 71)                                      /* BSImagespaceShaderBlur15 */                                         \
	X(ISNonHDRBlur3, 72)                                 /* BSImagespaceShaderNonHDRBlur3 */                                    \
	X(ISNonHDRBlur5, 73)                                 /* BSImagespaceShaderNonHDRBlur5 */                                    \
	X(ISNonHDRBlur7, 74)                                 /* BSImagespaceShaderNonHDRBlur7 */                                    \
	X(ISNonHDRBlur9, 75)                                 /* BSImagespaceShaderNonHDRBlur9 */                                    \
	X(ISNonHDRBlur11, 76)                                /* BSImagespaceShaderNonHDRBlur11 */                                   \
	X(ISNonHDRBlur13, 77)                                /* BSImagespaceShaderNonHDRBlur13 */                                   \
	X(ISNonHDRBlur15, 78)                                /* BSImagespaceShaderNonHDRBlur15 */                                   \
	X(ISBrightPassBlur3, 79)                             /* BSImagespaceShaderBrightPassBlur3 */                                \
	X(ISBrightPassBlur5, 80)                             /* BSImagespaceShaderBrightPassBlur5 */                                \
	X(ISBrightPassBlur7, 81)                             /* BSImagespaceShaderBrightPassBlur7 */                                \
	X(ISBrightPassBlur9, 82)                             /* BSImagespaceShaderBrightPassBlur9 */                                \
	X(ISBrightPassBlur11, 83)                            /* BSImagespaceShaderBrightPassBlur11 */                               \
	X(ISBrightPassBlur13, 84)                            /* BSImagespaceShaderBrightPassBlur13 */                               \
	X(ISBrightPassBlur15, 85)                            /* BSImagespaceShaderBrightPassBlur15 */                               \
	X(ISWaterDisplacementClearSimulation, 86)            /* BSImagespaceShaderWaterDisplacementClearSimulation */               \
	X(ISWaterDisplacementTexOffset, 87)                  /* BSImagespaceShaderWaterDisplacementTexOffset */                     \
	X(ISWaterDisplacementWadingRipple, 88)               /* BSImagespaceShaderWaterDisplacementWadingRipple */                  \
	X(ISWaterDisplacementRainRipple, 89)                 /* BSImagespaceShaderWaterDisplacementRainRipple */                    \
	X(ISWaterWadingHeightmap, 90)                        /* BSImagespaceShaderWaterWadingHeightmap */                           \
	X(ISWaterRainHeightmap, 91)                          /* BSImagespaceShaderWaterRainHeightmap */                             \
	X(ISWaterBlendHeightmaps, 92)                        /* BSImagespaceShaderWaterBlendHeightmaps */                           \
	X(ISWaterSmoothHeightmap, 93)                        /* BSImagespaceShaderWaterSmoothHeightmap */                           \
	X(ISWaterDisplacementNormals, 94)                    /* BSImagespaceShaderWaterDisplacementNormals */                       \
	X(ISNoiseScrollAndBlend, 95)                         /* BSImagespaceShaderNoiseScrollAndBlend */                            \
	X(ISNoiseNormalmap, 96)                              /* BSImagespaceShaderNoiseNormalmap */                                 \
	X(ISVolumetricLighting, 97)                          /* BSImagespaceShaderVolumetricLighting */                             \
	X2(ISLocalMap, 98, 101)                              /* BSImagespaceShaderLocalMap */                                       \
	X2(ISAlphaBlend, 99, 102)                            /* BSImagespaceShaderAlphaBlend */                                     \
	X2(ISLensFlare, 100, 103)                            /* BSImagespaceShaderLensFlare */                                      \
	X2(ISLensFlareVisibility, 101, 104)                  /* BSImagespaceShaderLensFlareVisibility */                            \
	X2(ISApplyReflections, 102, 105)                     /* BSImagespaceShaderApplyReflections */                               \
	X2(ISApplyVolumetricLighting, 103, 106)              /* BSImagespaceShaderISApplyVolumetricLighting */                      \
	X2(ISBasicCopy, 104, 107)                            /* BSImagespaceShaderISBasicCopy */                                    \
	X2(ISBlur, 105, 108)                                 /* BSImagespaceShaderISBlur */                                         \
	X2(ISVolumetricLightingBlurHCS, 106, 109)            /* BSImagespaceShaderISVolumetricLightingBlurHCS */                    \
	X2(ISVolumetricLightingBlurVCS, 107, 110)            /* BSImagespaceShaderISVolumetricLightingBlurVCS */                    \
	X2(ISReflectionBlurHCS, 108, 111)                    /* BSImagespaceShaderReflectionBlurHCS */                              \
	X2(ISReflectionBlurVCS, 109, 112)                    /* BSImagespaceShaderReflectionBlurVCS */                              \
	X2(ISParallaxMaskBlurHCS, 110, 113)                  /* BSImagespaceShaderISParallaxMaskBlurHCS */                          \
	X2(ISParallaxMaskBlurVCS, 111, 114)                  /* BSImagespaceShaderISParallaxMaskBlurVCS */                          \
	X2(ISDepthOfFieldBlurHCS, 112, 115)                  /* BSImagespaceShaderISDepthOfFieldBlurHCS */                          \
	X2(ISDepthOfFieldBlurVCS, 113, 116)                  /* BSImagespaceShaderISDepthOfFieldBlurVCS */                          \
	X2(ISCompositeVolumetricLighting, 114, 117)          /* BSImagespaceShaderISCompositeVolumetricLighting */                  \
	X2(ISCompositeLensFlare, 115, 118)                   /* BSImagespaceShaderISCompositeLensFlare */                           \
	X2(ISCompositeLensFlareVolumetricLighting, 116, 119) /* BSImagespaceShaderISCompositeLensFlareVolumetricLighting */         \
	X2(ISCopySubRegionCS, 117, 120)                      /* BSImagespaceShaderISCopySubRegionCS */                              \
	X2(ISDebugSnow, 118, 121)                            /* BSImagespaceShaderISDebugSnow */                                    \
	X2(ISDownsample, 119, 122)                           /* BSImagespaceShaderISDownsample */                                   \
	X2(ISDownsampleIgnoreBrightest, 120, 123)            /* BSImagespaceShaderISDownsampleIgnoreBrightest */                    \
	X2(ISDownsampleCS, 121, 124)                         /* BSImagespaceShaderISDownsampleCS */                                 \
	X2(ISDownsampleIgnoreBrightestCS, 122, 125)          /* BSImagespaceShaderISDownsampleIgnoreBrightestCS */                  \
	X2(ISExp, 123, 128)                                  /* BSImagespaceShaderISExp */                                          \
	X2(ISIBLensFlares, 124, 130)                         /* BSImagespaceShaderISIBLensFlares */                                 \
	X2(ISLightingComposite, 125, 131)                    /* BSImagespaceShaderISLightingComposite */                            \
	X2(ISLightingCompositeNoDirectionalLight, 126, 132)  /* BSImagespaceShaderISLightingCompositeNoDirectionalLight */          \
	X2(ISLightingCompositeMenu, 127, 133)                /* BSImagespaceShaderISLightingCompositeMenu */                        \
	X2(ISPerlinNoiseCS, 128, 134)                        /* BSImagespaceShaderISPerlinNoiseCS */                                \
	X2(ISPerlinNoise2DCS, 129, 135)                      /* BSImagespaceShaderISPerlinNoise2DCS */                              \
	X2(ISReflectionsRayTracing, 130, 145)                /* BSImagespaceShaderReflectionsRayTracing */                          \
	X2(ISReflectionsDebugSpecMask, 131, 146)             /* BSImagespaceShaderReflectionsDebugSpecMask */                       \
	X2(ISSAOBlurH, 132, 147)                             /* BSImagespaceShaderISSAOBlurH */                                     \
	X2(ISSAOBlurV, 133, 148)                             /* BSImagespaceShaderISSAOBlurV */                                     \
	X2(ISSAOBlurHCS, 134, 149)                           /* BSImagespaceShaderISSAOBlurHCS */                                   \
	X2(ISSAOBlurVCS, 135, 150)                           /* BSImagespaceShaderISSAOBlurVCS */                                   \
	X2(ISSAOCameraZ, 136, 151)                           /* BSImagespaceShaderISSAOCameraZ */                                   \
	X2(ISSAOCameraZAndMipsCS, 137, 152)                  /* BSImagespaceShaderISSAOCameraZAndMipsCS */                          \
	X2(ISSAOCompositeSAO, 138, 153)                      /* BSImagespaceShaderISSAOCompositeSAO */                              \
	X2(ISSAOCompositeFog, 139, 154)                      /* BSImagespaceShaderISSAOCompositeFog */                              \
	X2(ISSAOCompositeSAOFog, 140, 155)                   /* BSImagespaceShaderISSAOCompositeSAOFog */                           \
	X2(ISMinify, 141, 156)                               /* BSImagespaceShaderISMinify */                                       \
	X2(ISMinifyContrast, 142, 157)                       /* BSImagespaceShaderISMinifyContrast */                               \
	X2(ISSAORawAO, 143, 158)                             /* BSImagespaceShaderISSAORawAO */                                     \
	X2(ISSAORawAONoTemporal, 144, 159)                   /* BSImagespaceShaderISSAORawAONoTemporal */                           \
	X2(ISSAORawAOCS, 145, 160)                           /* BSImagespaceShaderISSAORawAOCS */                                   \
	X2(ISSILComposite, 146, 161)                         /* BSImagespaceShaderISSILComposite */                                 \
	X2(ISSILRawInd, 147, 162)                            /* BSImagespaceShaderISSILRawInd */                                    \
	X2(ISSimpleColor, 148, 163)                          /* BSImagespaceShaderISSimpleColor */                                  \
	X2(ISDisplayDepth, 149, 164)                         /* BSImagespaceShaderISDisplayDepth */                                 \
	X2(ISSnowSSS, 150, 165)                              /* BSImagespaceShaderISSnowSSS */                                      \
	X2(ISTemporalAA, 151, 166)                           /* BSImagespaceShaderISTemporalAA */                                   \
	X2(ISTemporalAA_UI, 152, 167)                        /* BSImagespaceShaderISTemporalAA_UI */                                \
	X2(ISTemporalAA_Water, 153, 168)                     /* BSImagespaceShaderISTemporalAA_Water */                             \
	X2(ISUpsampleDynamicResolution, 154, 169)            /* BSImagespaceShaderISUpsampleDynamicResolution */                    \
	X2(ISWaterBlend, 155, 170)                           /* BSImagespaceShaderISWaterBlend */                                   \
	X2(ISUnderwaterMask, 156, 171)                       /* BSImagespaceShaderISUnderwaterMask */                               \
	X2(ISWaterFlow, 157, 172)                            /* BSImagespaceShaderWaterFlow */                                      \
	/* SE 158 missing */                                                                                                        \
	/* VR only */                                                                                                               \
	X2(ISCopyDepthBuffer, INVALID_INDEX, 98)            /* BSImagespaceShaderCopyDepthBuffer */                                 \
	X2(ISCopyDepthBuffer_DR, INVALID_INDEX, 99)         /* BSImagespaceShaderCopyDepthBuffer_DR */                              \
	X2(ISCopyDepthBufferTargetSize, INVALID_INDEX, 100) /* BSImagespaceShaderCopyDepthBuffer_TargetSize */                      \
	/* VR 111 = ISReflectionBlurHCS; ISGraphicsTextureFilterMode was a phantom (removed) */                                     \
	X2(ISDownsampleHierarchicalDepthBufferCS, INVALID_INDEX, 126) /* BSImagespaceShaderISDownsampleHierarchicalDepthBufferCS */ \
	X2(ISDiffScaleDownsampleDepthBufferCS, INVALID_INDEX, 127)    /* BSImagespaceShaderISDiffScaleDownsampleDepthBufferCS */    \
	X2(ISFullScreenVR, INVALID_INDEX, 129)                        /* BSImagespaceShaderISFullScreenVR */                        \
	X2(ISTransformLvl7PreTest, INVALID_INDEX, 136)                /* BSImagespaceShaderTransformLvl7PreTest */                  \
	X2(ISLvl6PreTest, INVALID_INDEX, 137)                         /* BSImagespaceShaderLvl6PreTest */                           \
	X2(ISLvl5PreTest, INVALID_INDEX, 138)                         /* BSImagespaceShaderLvl5PreTest */                           \
	X2(ISLvl4PreTest, INVALID_INDEX, 139)                         /* BSImagespaceShaderLvl4PreTest */                           \
	X2(ISLvl3PreTest, INVALID_INDEX, 140)                         /* BSImagespaceShaderLvl3PreTest */                           \
	X2(ISLvl2PreTest, INVALID_INDEX, 141)                         /* BSImagespaceShaderLvl2PreTest */                           \
	X2(ISLvl1PreTest, INVALID_INDEX, 142)                         /* BSImagespaceShaderLvl1PreTest */                           \
	X2(ISLvl0PreTest, INVALID_INDEX, 143)                         /* BSImagespaceShaderLvl0PreTest */                           \
	X2(ISSetupPreTest, INVALID_INDEX, 144)                        /* BSImagespaceShaderSetupPreTest */

// IDs pack SE (low byte) + VR (high byte). Single-runtime builds resolve to the concrete
// runtime index (so the enum value matches the binary, which the id discovery relies on);
// SKYRIM_CROSS_VR keeps the packed form for GetCurrentIndex(). NOTE: in a single-runtime
// build every effect absent from that runtime collapses to INVALID_INDEX, so name lookup
// uses an if-chain rather than a switch (duplicate case labels are an error).
#if defined(SKYRIM_CROSS_VR)
#	define MakeImageSpaceID(se, vr) (se | (vr << 8))
#elif defined(EXCLUSIVE_SKYRIM_VR)
#	define MakeImageSpaceID(se, vr) (vr)
#else
#	define MakeImageSpaceID(se, vr) (se)
#endif
		static constexpr std::uint16_t INVALID_INDEX = 255;

		static constexpr std::uint16_t TOTAL_SE_EFFECTS = 159;
		static constexpr std::uint16_t TOTAL_VR_EFFECTS = 173;

#define X(name, index) name = MakeImageSpaceID(index, index),
#define X2(name, se, vr) name = MakeImageSpaceID(se, vr),
		/**
		 * @brief Enumeration of image space effect types.
		 *
		 * Defines identifiers for various image space shaders and effects used in Skyrim's
		 * rendering pipeline. Values are packed to support both SE/AE and VR indices.
		 * Use GetSEIndex() and GetVRIndex() to extract runtime-specific indices.
		 */
		enum ImageSpaceEffectEnum : std::int32_t
		{
			IMAGE_SPACE_EFFECTS
				Total = TOTAL_SE_EFFECTS,
			VRTotal = TOTAL_VR_EFFECTS
		};
#undef X
#undef X2

		/**
		 * @brief Gets the Skyrim Special Edition index for an effect ID.
		 * @return The SE index, or INVALID_INDEX in a VR-only build.
		 */
		[[nodiscard]] static constexpr std::uint16_t GetSEIndex([[maybe_unused]] ImageSpaceEffectEnum a_effect) noexcept
		{
#if defined(SKYRIM_CROSS_VR)
			return static_cast<std::uint16_t>(a_effect & 0xFF);
#elif defined(EXCLUSIVE_SKYRIM_VR)
			return INVALID_INDEX;                         // SE index is not encoded in a VR-only build
#else
			return static_cast<std::uint16_t>(a_effect);  // id is already the SE/AE index
#endif
		}

		/**
		 * @brief Gets the Skyrim VR index for an effect ID.
		 * @return The VR index, or INVALID_INDEX in a non-VR build.
		 */
		[[nodiscard]] static constexpr std::uint16_t GetVRIndex([[maybe_unused]] ImageSpaceEffectEnum a_effect) noexcept
		{
#if defined(SKYRIM_CROSS_VR)
			return static_cast<std::uint16_t>((a_effect >> 8) & 0xFF);
#elif defined(EXCLUSIVE_SKYRIM_VR)
			return static_cast<std::uint16_t>(a_effect);  // id is already the VR index
#else
			return INVALID_INDEX;                         // VR index is not encoded in a non-VR build
#endif
		}

		/**
		 * @brief Gets the index for the current runtime (SE/AE or VR).
		 * @param a_effect The packed effect enum value.
		 * @return The runtime-specific index.
		 */
		[[nodiscard]] static std::uint16_t GetCurrentIndex(ImageSpaceEffectEnum a_effect) noexcept
		{
			return REL::Module::IsVR() ? GetVRIndex(a_effect) : GetSEIndex(a_effect);
		}

		/**
		 * @brief Gets the total number of effects for the current runtime.
		 * @return Total count of effects (159 for SE/AE, 173 for VR).
		 */
		[[nodiscard]] static std::uint16_t GetTotal() noexcept
		{
			return REL::Module::IsVR() ? TOTAL_VR_EFFECTS : TOTAL_SE_EFFECTS;
		}

		/**
		 * @brief Gets the string name of an image space effect.
		 * @param a_effect The effect enum value.
		 * @return String representation of the effect name.
		 */
		[[nodiscard]] static std::string GetImageSpaceEffectName(ImageSpaceEffectEnum a_effect)
		{
#define X(name, index)      \
	if (a_effect == (name)) \
		return #name;
#define X2(name, se, vr)    \
	if (a_effect == (name)) \
		return #name;
			// if-chain (not switch): single-runtime builds collapse every cross-runtime
			// effect to INVALID_INDEX; duplicate switch cases are an error, duplicate
			// if-conditions are not. Present effects have unique values (first match wins).
			IMAGE_SPACE_EFFECTS
			return "Unknown";
#undef X
#undef X2
		}

		struct UNK_BSImagespaceShaderISTemporalAA
		{
			BSImagespaceShaderISTemporalAA* shader;                                // 00
			BSImagespaceShader*             BSImagespaceShaderISTemporalAA_UI;     // 08
			BSImagespaceShader*             BSImagespaceShaderISTemporalAA_Water;  // 10
			bool                            taaEnabled;                            // 18
		};

		// Real type of the field misnamed BSImagespaceShaderISSAOBlurH below (all three
		// runtimes; the feeding allocation is 0x70 bytes, not sizeof(BSImagespaceShader)
		// == 0x1A8). Holds pointers to the rest of the SAO effect chain plus SAO/DOF
		// Display-menu ini defaults, incl. bSAOEnable:Display into enableSAO.
		struct SAOEffectParams
		{
			ImageSpaceEffect* blurH;            // 00 - ISSAOBlurH (self)
			ImageSpaceEffect* blurV;            // 08 - ISSAOBlurV
			ImageSpaceEffect* cameraZ;          // 10 - ISSAOCameraZ
			ImageSpaceEffect* compositeSAO;     // 18 - ISSAOCompositeSAO
			ImageSpaceEffect* compositeFog;     // 20 - ISSAOCompositeFog
			ImageSpaceEffect* compositeSAOFog;  // 28 - ISSAOCompositeSAOFog
			ImageSpaceEffect* minify;           // 30 - ISMinify
			ImageSpaceEffect* minifyContrast;   // 38 - ISMinifyContrast
			ImageSpaceEffect* rawAO;            // 40 - ISSAORawAO
			ImageSpaceEffect* rawAONoTemporal;  // 48 - ISSAORawAONoTemporal
			bool              enableSAO;        // 50 - from bSAOEnable:Display (low byte of an 8-byte slot)
			std::uint8_t      pad51[3];         // 51
			std::uint32_t     unk54;            // 54 - always 0 at construction
			std::uint64_t     unk58;            // 58 - always 0 at construction
			std::uint64_t     unk60;            // 60 - always 0 at construction
			std::uint64_t     unk68;            // 68 - always 0 at construction
		};
		static_assert(sizeof(SAOEffectParams) == 0x70);

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
	SAOEffectParams*                    BSImagespaceShaderISSAOBlurH;                    /* 1C8, VR 1F0 -- see SAOEffectParams doc comment */                                                    \
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
	NiPointer<NiAVObject>               underwaterSplitterGeom;                          /* 218, VR 240 */
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
	SAOEffectParams*                    BSImagespaceShaderISSAOBlurH;                            /* 1C8, VR 1F0 -- see SAOEffectParams doc comment above */                                              \
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
	NiPointer<NiAVObject>               underwaterSplitterGeom;                                  /* 218, VR 240 */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x1F0);
		static ImageSpaceManager* GetSingleton()
		{
			static REL::Relocation<ImageSpaceManager**> singleton{ RELOCATION_ID(527731, 414660) };
			return *singleton;
		}

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x58, 0);

		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x58);

		// Prefer these over GetRuntimeData()/GetVRRuntimeData() directly --
		// always resolves the right struct regardless of layout differences.
		RUNTIME_DATA_FIELD_ACCESSOR(ImageSpaceData, GetImageSpaceData, GetRuntimeData, GetVRRuntimeData, data);
		RUNTIME_DATA_FIELD_ACCESSOR(ImageSpaceBaseData*, GetCurrentBaseData, GetRuntimeData, GetVRRuntimeData, currentBaseData);
		RUNTIME_DATA_FIELD_ACCESSOR(ImageSpaceBaseData*, GetOverrideBaseData, GetRuntimeData, GetVRRuntimeData, overrideBaseData);

		/**
		 * @brief Gets all effects supported by the current runtime, sorted by index.
		 * @return Vector of effect enums available in the current runtime.
		 */
		[[nodiscard]] static std::vector<ImageSpaceEffectEnum> GetAllEffects()
		{
			static std::vector<ImageSpaceEffectEnum> allEffects;
			if (allEffects.empty()) {
#define X(name, index) allEffects.push_back(name);
#define X2(name, se, vr) allEffects.push_back(name);
				IMAGE_SPACE_EFFECTS
#undef X
#undef X2
			}
			std::vector<ImageSpaceEffectEnum> filtered;
			for (auto e : allEffects) {
				if (SupportsCurrentRuntime(e)) {
					filtered.push_back(e);
				}
			}
			std::ranges::sort(filtered, [](ImageSpaceEffectEnum a, ImageSpaceEffectEnum b) {
				return GetCurrentIndex(a) < GetCurrentIndex(b);
			});
			return filtered;
		}

		/**
		 * @brief Checks if an effect is supported in Skyrim Special Edition.
		 * @param a_effect The effect to check.
		 * @return True if the effect has a valid SE index.
		 */
		[[nodiscard]] static constexpr bool SupportsSE(ImageSpaceEffectEnum a_effect) noexcept
		{
			return GetSEIndex(a_effect) != INVALID_INDEX;
		}

		/**
		 * @brief Checks if an effect is supported in Skyrim VR.
		 * @param a_effect The effect to check.
		 * @return True if the effect has a valid VR index.
		 */
		[[nodiscard]] static constexpr bool SupportsVR(ImageSpaceEffectEnum a_effect) noexcept
		{
			return GetVRIndex(a_effect) != INVALID_INDEX;
		}

		/**
		 * @brief Checks if an effect is supported in Skyrim Anniversary Edition.
		 * @param a_effect The effect to check.
		 * @return True if the effect is supported (same as SE).
		 */
		[[nodiscard]] static constexpr bool SupportsAE(ImageSpaceEffectEnum a_effect) noexcept
		{
			return SupportsSE(a_effect);  // AE uses same indices as SE
		}

		/**
		 * @brief Checks if an effect is supported in the current runtime.
		 * @param a_effect The effect to check.
		 * @return True if the effect is supported in the current runtime.
		 */
		[[nodiscard]] static constexpr bool SupportsCurrentRuntime(ImageSpaceEffectEnum a_effect) noexcept
		{
			return REL::Module::IsVR() ? SupportsVR(a_effect) : SupportsSE(a_effect);
		}

		// members
		std::uint64_t                        unk00;       /* 000 */
		std::uint64_t                        unk08;       /* 008 */
		NiRect<std::int32_t>                 rect;        // 010
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
	};
	STATIC_ASSERT_SIZE(ImageSpaceManager, 0x220, 0x220, 0x248, 0x58);
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
