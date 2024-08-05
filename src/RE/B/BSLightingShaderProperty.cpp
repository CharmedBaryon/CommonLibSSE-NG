#include "RE/B/BSLightingShaderProperty.h"

#include "RE/B/BSRenderPass.h"
#include "RE/B/BSShader.h"

namespace RE
{
	void BSLightingShaderProperty::CopyMembers(BSLightingShaderProperty* a_other)
	{
		flags = a_other->flags;
		alpha = a_other->alpha;
		lastRenderPassState = (std::numeric_limits<std::int32_t>::max)();
		if (flags.all(EShaderPropertyFlag::kOwnEmit) && a_other->emissiveColor) {
			if (!emissiveColor) {
				emissiveColor = new NiColor();
			}
			emissiveColor->red = a_other->emissiveColor->red;
			emissiveColor->green = a_other->emissiveColor->green;
			emissiveColor->blue = a_other->emissiveColor->blue;
		}
		projectedUVParams = a_other->projectedUVParams;
		projectedUVColor = a_other->projectedUVColor;
		emissiveMult = a_other->emissiveMult;
	}

	void BSLightingShaderProperty::Data::Clear()
	{
		while (head != nullptr) {
			BSRenderPass* next = head->next;
			head->ClearRenderPass();
			head = next;
		}
		head = nullptr;
	}

	BSRenderPass* BSLightingShaderProperty::Data::EmplacePass(BSShader* a_shader, BSShaderProperty* a_property, BSGeometry* a_geometry,
		uint32_t a_technique, uint8_t a_numLights, BSLight* a_light0, BSLight* a_light1, BSLight* a_light2, BSLight* a_light3)
	{
		BSLight* lights[4]{
			a_light0,
			a_light1,
			a_light2,
			a_light3
		};
		auto* newPass = a_shader->MakeRenderPass(a_property, a_geometry, a_technique, a_numLights, lights);
		if (head != nullptr) {
			RE::BSRenderPass* lastPass = head;
			while (lastPass->next != nullptr) {
				lastPass = lastPass->next;
			}
			lastPass->next = newPass;
		} else {
			head = newPass;
		}
		return newPass;
	}

#ifdef ENABLE_SKYRIM_VR
	void BSLightingShaderProperty::InvalidateTextures(std::uint32_t a_unk1)
	{
		using func_t = decltype(&BSLightingShaderProperty::InvalidateTextures);
		REL::Relocation<func_t> func{ REL::ID(5388393136) };
		func(this, a_unk1);
	}
#endif
}
