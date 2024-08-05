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
#include "RE/B/bhkNiCollisionObject.h"
#include "RE/B/bhkRigidBody.h"
#include "RE/H/hkpRigidBody.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiProperty.h"
#include "RE/N/NiRTTI.h"
#include "RE/S/State.h"

namespace RE
{
	NiAVObject* NiAVObject::Clone()
	{
		using func_t = decltype(&NiAVObject::Clone);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68835, 70187) };
		return func(this);
	}

	void NiAVObject::CullGeometry(bool a_cull)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geo) -> BSVisit::BSVisitControl {
			a_geo->SetAppCulled(a_cull);

			return BSVisit::BSVisitControl::kContinue;
		});
	}

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
		static REL::Relocation<func_t> func{ RELOCATION_ID(25482, 26022) };
		return func(this);
	}

	COL_LAYER NiAVObject::GetCollisionLayer() const
	{
		const auto colObj = collisionObject ? collisionObject->AsBhkNiCollisionObject() : nullptr;
		const auto rigidBody = colObj && colObj->body ? colObj->body->AsBhkRigidBody() : nullptr;

		if (rigidBody && rigidBody->referencedObject) {
			if (const auto havokRigidBody = static_cast<hkpRigidBody*>(rigidBody->referencedObject.get())) {
				if (const auto collidable = havokRigidBody->GetCollidable()) {
					return collidable->GetCollisionLayer();
				}
			}
		}

		return COL_LAYER::kUnidentified;
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

	float NiAVObject::GetMass()
	{
		float mass = 0.0f;

		BSVisit::TraverseScenegraphCollision(this, [&](bhkNiCollisionObject* a_col) -> BSVisit::BSVisitControl {
			if (auto hkpBody = a_col->body ? static_cast<RE::hkpRigidBody*>(a_col->body->referencedObject.get()) : nullptr) {
				mass += hkpBody->motion.GetMass();
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return mass;
	}

	TESObjectREFR* NiAVObject::GetUserData() const
	{
		auto* thisUserData = REL::RelocateMember<RE::TESObjectREFR*>(this, 0x0F8, 0x110);
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
		REL::RelocateMember<RE::TESObjectREFR*>(this, 0x0F8, 0x110) = a_ref;
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
		static REL::Relocation<func_t> func{ RELOCATION_ID(15547, 15723) };
		return func(this);
	}

	void NiAVObject::SetAppCulled(bool a_cull)
	{
		a_cull ? GetFlags().set(Flag::kHidden) : GetFlags().reset(Flag::kHidden);
	}

	void NiAVObject::SetCollisionLayer(COL_LAYER a_collisionLayer)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayer);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76170, 77998) };
		return func(this, a_collisionLayer);
	}

	void NiAVObject::SetCollisionLayerAndGroup(COL_LAYER a_collisionLayer, std::uint32_t a_group)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayerAndGroup);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76171, 77999) };
		return func(this, a_collisionLayer, a_group);
	}

	bool NiAVObject::SetMotionType(hkpMotion::MotionType a_motionType, bool a_recurse, bool a_force, bool a_allowActivate)
	{
		using func_t = decltype(&NiAVObject::SetMotionType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76033, 77866) };
		return func(this, a_motionType, a_recurse, a_force, a_allowActivate);
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
		newShaderData->baseTexture = gState->GetRuntimeData().defaultTextureWhite;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect];
			auto shaderProp = netimmerse_cast<BSShaderProperty*>(effect.get());
			if (shaderProp && shaderProp->AcceptsEffectData()) {
				auto shaderData = shaderProp->effectData;
				if (!shaderData || shaderData->baseTexture == gState->GetRuntimeData().defaultTextureWhite) {
					shaderProp->SetEffectShaderData(newShaderData);
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::Update(NiUpdateData& a_data)
	{
		using func_t = decltype(&NiAVObject::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68900, 70251) };
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
		static REL::Relocation<func_t> func{ RELOCATION_ID(76271, 78103) };
		return func(this, a_enable, a_arg2, a_arg3);
	}

#ifdef SKYRIM_CROSS_VR
	void NiAVObject::PerformOp(PerformOpFunc& a_func)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PerformOp)>(0x26, 0x27, this, a_func);
	}

	void NiAVObject::AttachProperty(NiAlphaProperty* a_property)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::AttachProperty)>(0x27, 0x28, this, a_property);
	}

	void NiAVObject::SetMaterialNeedsUpdate(bool a_needsUpdate)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::SetMaterialNeedsUpdate)>(0x28, 0x29, this, a_needsUpdate);
	}

	void NiAVObject::SetDefaultMaterialNeedsUpdateFlag(bool a_flag)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::SetDefaultMaterialNeedsUpdateFlag)>(0x29, 0x2A, this, a_flag);
	}

	NiAVObject* NiAVObject::GetObjectByName(const BSFixedString& a_name)
	{
		return REL::RelocateVirtual<decltype(&NiAVObject::GetObjectByName)>(0x2A, 0x2B, this, a_name);
	}

	void NiAVObject::SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid)
	{
		return REL::RelocateVirtual<decltype(&NiAVObject::SetSelectiveUpdateFlags)>(0x2B, 0x2C, this, a_selectiveUpdate, a_selectiveUpdateTransforms, a_rigid);
	}

	void NiAVObject::UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateDownwardPass)>(0x2C, 0x2D, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateSelectedDownwardPass)>(0x2D, 0x2E, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateRigidDownwardPass)>(0x2E, 0x2F, this, a_data, a_arg2);
	}

	void NiAVObject::UpdateWorldBound()
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldBound)>(0x2F, 0x30, this);
	}

	void NiAVObject::UpdateWorldData(NiUpdateData* a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldData)>(0x30, 0x31, this, a_data);
	}

	void NiAVObject::UpdateTransformAndBounds(NiUpdateData& a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::UpdateTransformAndBounds)>(0x31, 0x32, this, a_data);
	}

	void NiAVObject::PreAttachUpdate(NiNode* a_parent, NiUpdateData& a_data)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PreAttachUpdate)>(0x32, 0x33, this, a_parent, a_data);
	}

	void NiAVObject::PostAttachUpdate()
	{
		REL::RelocateVirtual<decltype(&NiAVObject::PostAttachUpdate)>(0x33, 0x34, this);
	}

	void NiAVObject::OnVisible(NiCullingProcess& a_process)
	{
		REL::RelocateVirtual<decltype(&NiAVObject::OnVisible)>(0x34, 0x35, this, a_process);
	}
#endif
	BSLightingShaderProperty* NiAVObject::temp_nicast(BSGeometry* a_geometry)
	{
		if (auto effect = a_geometry->GetGeometryRuntimeData().properties[BSGeometry::States::kEffect].get(); effect) {
			if (auto rtti = effect->GetRTTI(); rtti) {
				const std::string temp_name(rtti->GetName());
				if (temp_name == "BSLightingShaderProperty") {
					return static_cast<RE::BSLightingShaderProperty*>(effect);
				}
			}
		}
		return nullptr;
	}
}
