#include "RE/N/NiAVObject.h"

#include "RE/B/BSEffectShaderData.h"
#include "RE/B/BSGeometry.h"
#include "RE/B/BSLightingShaderMaterialFacegenTint.h"
#include "RE/B/BSLightingShaderMaterialHairTint.h"
#include "RE/B/BSLightingShaderProperty.h"
#include "RE/B/BSShaderMaterial.h"
#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSVisit.h"
#include "RE/B/BSXFlags.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiProperty.h"
#include "RE/N/NiRTTI.h"
#include "RE/S/State.h"

namespace RE
{
	void NiAVObject::CullNode(bool a_cull)
	{
		BSVisit::TraverseScenegraphObjects(this, [&](NiAVObject* a_object) -> BSVisit::BSVisitControl {
			a_object->SetAppCulled(a_cull);

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	bool NiAVObject::GetAppCulled() const
	{
		return GetFlags().all(Flag::kHidden);
	}

	bhkCollisionObject* NiAVObject::GetCollisionObject() const
	{
		using func_t = decltype(&NiAVObject::GetCollisionObject);
		REL::Relocation<func_t> func{ REL::RelocationID(25482, 26022) };
		return func(this);
	}

	BSGeometry* NiAVObject::GetFirstGeometryOfShaderType(BSShaderMaterial::Feature a_type)
	{
		BSGeometry* firstGeometry = nullptr;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				if (a_type == BSShaderMaterial::Feature::kNone) {
					firstGeometry = a_geometry;
					return BSVisit::BSVisitControl::kStop;
				}
				const auto material = lightingShader->material;
				if (material && material->GetFeature() == a_type) {
					firstGeometry = a_geometry;
					return BSVisit::BSVisitControl::kStop;
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});

		return firstGeometry;
	}

	TESObjectREFR* NiAVObject::GetUserData() const
	{
		auto* thisUserData = REL::RelocateMember<RE::TESObjectREFR*>(this, 0x0F8, 0x100);
		if (thisUserData) {
			return thisUserData;
		}

		if (parent) {
			return parent->GetUserData();
		}

		return nullptr;
	}

	void NiAVObject::SetUserData(TESObjectREFR* a_ref) noexcept
	{
		REL::RelocateMember<RE::TESObjectREFR*>(this, 0x0F8, 0x100) = a_ref;
	}

	bool NiAVObject::HasAnimation() const
	{
		const auto bsxFlags = GetExtraData<BSXFlags>("BSX");
		return bsxFlags && ((bsxFlags->value & 2) != 0);
	}

	bool NiAVObject::HasShaderType(BSShaderMaterial::Feature a_type)
	{
		bool hasShaderType = false;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				auto material = lightingShader->material;
				if (material && material->GetFeature() == a_type) {
					hasShaderType = true;
					return BSVisit::BSVisitControl::kStop;
				}
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return hasShaderType;
	}

	void NiAVObject::RemoveDecals()
	{
		using func_t = decltype(&NiAVObject::RemoveDecals);
		REL::Relocation<func_t> func{ REL::RelocationID(15547, 15723) };
		return func(this);
	}

	void NiAVObject::SetAppCulled(bool a_cull)
	{
		a_cull ? GetFlags().set(Flag::kHidden) : GetFlags().reset(Flag::kHidden);
	}

	void NiAVObject::SetCollisionLayer(COL_LAYER a_collisionLayer)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayer);
		REL::Relocation<func_t> func{ REL::RelocationID(76170, 77998) };
		return func(this, a_collisionLayer);
	}

	void NiAVObject::SetCollisionLayerAndGroup(COL_LAYER a_collisionLayer, std::uint32_t a_group)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayerAndGroup);
		REL::Relocation<func_t> func{ REL::RelocationID(76171, 77999) };
		return func(this, a_collisionLayer, a_group);
	}

	bool NiAVObject::SetMotionType(std::uint32_t a_motionType, bool a_arg2, bool a_arg3, bool a_allowActivate)
	{
		using func_t = decltype(&NiAVObject::SetMotionType);
		REL::Relocation<func_t> func{ Offset::NiAVObject::SetMotionType };
		return func(this, a_motionType, a_arg2, a_arg3, a_allowActivate);
	}

	bool NiAVObject::SetProjectedUVData(const NiColorA& a_projectedUVParams, const NiColor& a_projectedUVColor, bool a_isSnow)
	{
		bool result = false;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using Flag = BSShaderProperty::EShaderPropertyFlag;
			using Flag8 = BSShaderProperty::EShaderPropertyFlag8;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				if (lightingShader->flags.any(Flag::kSkinned) || lightingShader->flags.any(Flag::kTreeAnim) || lightingShader->flags.any(Flag::kBackLighting)) {
					return BSVisit::BSVisitControl::kContinue;
				}

				if (const auto material = lightingShader->material; material) {
					if (const auto feature = material->GetFeature(); feature == Feature::kParallax || feature == Feature::kMultilayerParallax || feature == Feature::kFaceGen || feature == Feature::kMultiTexLand) {
						return BSVisit::BSVisitControl::kContinue;
					}
				}

				result = true;

				lightingShader->SetFlags(Flag8::kProjectedUV, true);
				if (a_isSnow) {
					lightingShader->SetFlags(Flag8::kSnow, true);
				}

				lightingShader->projectedUVParams = a_projectedUVParams;
				lightingShader->projectedUVColor = a_projectedUVColor;

				lightingShader->SetupGeometry(a_geometry);
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return result;
	}

	void NiAVObject::TintScenegraph(const NiColorA& a_color)
	{
		auto                                gState = BSGraphics::State::GetSingleton();
		BSTSmartPointer<BSEffectShaderData> newShaderData(new BSEffectShaderData());
		newShaderData->fillColor = a_color;
		newShaderData->baseTexture = gState->defaultTextureWhite;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect];
			auto shaderProp = netimmerse_cast<BSShaderProperty*>(effect.get());
			if (shaderProp && shaderProp->AcceptsEffectData()) {
				auto shaderData = shaderProp->effectData;
				if (!shaderData || shaderData->baseTexture == gState->defaultTextureWhite) {
					shaderProp->SetEffectShaderData(newShaderData);
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::Update(NiUpdateData& a_data)
	{
		using func_t = decltype(&NiAVObject::Update);
		REL::Relocation<func_t> func{ Offset::NiAVObject::Update };
		return func(this, a_data);
	}

	void NiAVObject::UpdateBodyTint(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->GetGeometryRuntimeData().properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kFaceGenRGBTint) {
						auto facegenTint = static_cast<BSLightingShaderMaterialFacegenTint*>(material);
						facegenTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateHairColor(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->GetGeometryRuntimeData().properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kHairTint) {
						auto hairTint = static_cast<BSLightingShaderMaterialHairTint*>(material);
						hairTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateMaterialAlpha(float a_alpha, bool a_doOnlySkin)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->GetGeometryRuntimeData().properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = static_cast<BSLightingShaderMaterialBase*>(lightingShader->material);
					if (material) {
						if (a_doOnlySkin) {
							if (auto const feature = material->GetFeature(); feature != Feature::kFaceGen && feature != Feature::kFaceGenRGBTint) {
								return BSVisit::BSVisitControl::kContinue;
							}
						}
						material->materialAlpha = a_alpha;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateRigidConstraints(bool a_enable, std::uint8_t a_arg2, std::uint32_t a_arg3)
	{
		using func_t = decltype(&NiAVObject::UpdateRigidConstraints);
		REL::Relocation<func_t> func{ REL::RelocationID(76271, 78103) };
		return func(this, a_enable, a_arg2, a_arg3);
	}

	void NiAVObject::PerformOp(PerformOpFunc& a_func)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PerformOp)>(0x03, 0x04, this, a_func);
	}

	void NiAVObject::AttachProperty(NiAlphaProperty* a_property)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::AttachProperty)>(0x04, 0x05, this, a_property);
	}

	void NiAVObject::SetMaterialNeedsUpdate(bool a_needsUpdate)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::SetMaterialNeedsUpdate)>(0x05, 0x06, this, a_needsUpdate);
	}

	void NiAVObject::SetDefaultMaterialNeedsUpdateFlag(bool a_flag)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::SetDefaultMaterialNeedsUpdateFlag)>(0x06, 0x07, this, a_flag);
	}

	NiAVObject* NiAVObject::GetObjectByName(const BSFixedString& a_name)
	{
		return REL::RelocateVirtual<decltype(&NiAVObject::GetObjectByName)>(0x07, 0x08, this, a_name);
	}

	void NiAVObject::SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid)
	{
		return REL::RelocateVirtual<decltype(&NiAVObject::SetSelectiveUpdateFlags)>(0x08, 0x09, this, a_selectiveUpdate, a_selectiveUpdateTransforms, a_rigid);
	}

	void NiAVObject::UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateDownwardPass)>(0x09, 0x0A, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateSelectedDownwardPass)>(0x0A, 0x0B, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateRigidDownwardPass)>(0x0B, 0x0C, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateWorldBound()
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldBound)>(0x0C, 0x0D, this);
	}

	void NiAVObject::UpdateWorldData(NiUpdateData* a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldData)>(0x0D, 0x0E, this, a_data);
	}

	void NiAVObject::UpdateTransformAndBounds(NiUpdateData& a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateTransformAndBounds)>(0x0E, 0x0F, this, a_data);
	}

	void NiAVObject::PreAttachUpdate(NiNode* a_parent, NiUpdateData& a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PreAttachUpdate)>(0x0F, 0x10, this, a_parent, a_data);
	}

	void NiAVObject::PostAttachUpdate()
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PostAttachUpdate)>(0x10, 0x11, this);
	}

	void NiAVObject::OnVisible(NiCullingProcess& a_process)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::OnVisible)>(0x11, 0x12, this, a_process);
	}
}
