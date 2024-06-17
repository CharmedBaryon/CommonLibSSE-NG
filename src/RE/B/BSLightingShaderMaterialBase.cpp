#include "RE/B/BSLightingShaderMaterialBase.h"

#include "RE/B/BSLightingShaderMaterial.h"
#include "RE/B/BSLightingShaderMaterialEnvmap.h"
#include "RE/B/BSLightingShaderMaterialEye.h"
#include "RE/B/BSLightingShaderMaterialFacegen.h"
#include "RE/B/BSLightingShaderMaterialFacegenTint.h"
#include "RE/B/BSLightingShaderMaterialGlowmap.h"
#include "RE/B/BSLightingShaderMaterialHairTint.h"
#include "RE/B/BSLightingShaderMaterialLODLandscape.h"
#include "RE/B/BSLightingShaderMaterialLandscape.h"
#include "RE/B/BSLightingShaderMaterialMultiLayerParallax.h"
#include "RE/B/BSLightingShaderMaterialParallax.h"
#include "RE/B/BSLightingShaderMaterialParallaxOcc.h"
#include "RE/B/BSLightingShaderMaterialSnow.h"
#include "RE/B/BSTextureSet.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	void BSLightingShaderMaterialBase::CopyBaseMembers(BSLightingShaderMaterialBase* a_other)
	{
		texCoordOffset[0] = a_other->texCoordOffset[0];
		texCoordOffset[1] = a_other->texCoordOffset[1];
		texCoordScale[0] = a_other->texCoordScale[0];
		texCoordScale[1] = a_other->texCoordScale[1];

		diffuseTexture = a_other->diffuseTexture;
		normalTexture = a_other->normalTexture;
		rimSoftLightingTexture = a_other->rimSoftLightingTexture;
		specularBackLightingTexture = a_other->specularBackLightingTexture;
		textureClampMode = a_other->textureClampMode;
		textureSet = a_other->textureSet;

		materialAlpha = a_other->materialAlpha;
		specularPower = a_other->specularPower;
		specularColor = a_other->specularColor;
		specularColorScale = a_other->specularColorScale;
		refractionPower = a_other->refractionPower;
		subSurfaceLightRolloff = a_other->subSurfaceLightRolloff;
		rimLightPower = a_other->rimLightPower;
	}

	BSLightingShaderMaterialBase* BSLightingShaderMaterialBase::CreateMaterial(Feature a_feature)
	{
		switch (a_feature) {
		case Feature::kDefault:
			{
				auto material = malloc<BSLightingShaderMaterial>();
				std::memset(reinterpret_cast<void*>(material), 0, sizeof(BSLightingShaderMaterial));
				if (material) {
					material->Ctor();
					stl::emplace_vtable<BSLightingShaderMaterial>(material);
				}
				return material;
			}
		case Feature::kEnvironmentMap:
			{
				auto material = malloc<BSLightingShaderMaterialEnvmap>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kGlowMap:
			{
				auto material = malloc<BSLightingShaderMaterialGlowmap>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kParallax:
			{
				auto material = malloc<BSLightingShaderMaterialParallax>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kFaceGen:
			{
				auto material = malloc<BSLightingShaderMaterialFacegen>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kFaceGenRGBTint:
			{
				auto material = malloc<BSLightingShaderMaterialFacegenTint>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kHairTint:
			{
				auto material = malloc<BSLightingShaderMaterialHairTint>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kParallaxOcc:
			{
				auto material = malloc<BSLightingShaderMaterialParallaxOcc>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kMultiTexLand:
		case Feature::kMultiTexLandLODBlend:
			{
				auto material = malloc<BSLightingShaderMaterialLandscape>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kLODLand:
		case Feature::kLODLandNoise:
			{
				auto material = malloc<BSLightingShaderMaterialLODLandscape>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kUnknown:
		case Feature::kMultiIndexTriShapeSnow:
			{
				auto material = malloc<BSLightingShaderMaterialSnow>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kMultilayerParallax:
			{
				auto material = malloc<BSLightingShaderMaterialMultiLayerParallax>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		case Feature::kEye:
			{
				auto material = malloc<BSLightingShaderMaterialEye>();
				if (material) {
					material->Ctor();
				}
				return material;
			}
		default:
			return nullptr;
		}
	}

	NiPointer<BSTextureSet> BSLightingShaderMaterialBase::GetTextureSet() const
	{
		return textureSet;
	}

	void BSLightingShaderMaterialBase::SetTextureSet(NiPointer<BSTextureSet> a_textureSet)
	{
		textureSet = a_textureSet;
	}

	void BSLightingShaderMaterialBase::CopyMembers(BSShaderMaterial* that)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSShaderMaterial*, BSShaderMaterial*)>((vtable.get()[0x2]));
		return baseMethod(this, that);
	}

	bool BSLightingShaderMaterialBase::DoIsCopy(BSShaderMaterial* that)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<bool (*)(BSShaderMaterial*, BSShaderMaterial*)>((vtable.get()[0x3]));
		return baseMethod(this, that);
	}

	std::uint32_t BSLightingShaderMaterialBase::ComputeCRC32(uint32_t srcHash)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<uint32_t (*)(BSShaderMaterial*, uint32_t)>((vtable.get()[0x4]));
		return baseMethod(this, srcHash);
	}

	BSShaderMaterial* BSLightingShaderMaterialBase::GetDefault()
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<BSShaderMaterial* (*)(BSShaderMaterial*)>((vtable.get()[0x5]));
		return baseMethod(this);
	}

	BSShaderMaterial::Feature BSLightingShaderMaterialBase::GetFeature() const
	{
		return Feature::kDefault;
	}

	BSShaderMaterial::Type BSLightingShaderMaterialBase::GetType() const
	{
		return Type::kLighting;
	}

	void BSLightingShaderMaterialBase::OnLoadTextureSet(std::uint64_t arg1, BSTextureSet* inTextureSet)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSLightingShaderMaterialBase*, uint64_t, BSTextureSet*)>((vtable.get()[0x8]));
		return baseMethod(this, arg1, inTextureSet);
	}

	void BSLightingShaderMaterialBase::ClearTextures()
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSLightingShaderMaterialBase*)>((vtable.get()[0x9]));
		return baseMethod(this);
	}

	void BSLightingShaderMaterialBase::ReceiveValuesFromRootMaterial(bool skinned, bool rimLighting, bool softLighting, bool backLighting, bool MSN)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSLightingShaderMaterialBase*, bool, bool, bool, bool, bool)>((vtable.get()[0xA]));
		return baseMethod(this, skinned, rimLighting, softLighting, backLighting, MSN);
	}

	uint32_t BSLightingShaderMaterialBase::GetTextures(NiSourceTexture** textures)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<uint32_t (*)(BSLightingShaderMaterialBase*, NiSourceTexture**)>((vtable.get()[0xB]));
		return baseMethod(this, textures);
	}

	void BSLightingShaderMaterialBase::SaveBinary(NiStream& stream)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSLightingShaderMaterialBase*, NiStream&)>((vtable.get()[0xC]));
		return baseMethod(this, stream);
	}

	void BSLightingShaderMaterialBase::LoadBinary(NiStream& stream)
	{
		auto vtable = REL::Relocation<void***>(BSLightingShaderMaterialBase::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSLightingShaderMaterialBase*, NiStream&)>((vtable.get()[0xD]));
		return baseMethod(this, stream);
	}
}
