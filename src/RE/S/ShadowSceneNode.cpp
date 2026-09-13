#include "RE/S/ShadowSceneNode.h"
#include "RE/B/BSLight.h"
#include "RE/B/BSShadowLight.h"

namespace RE
{
	BSLight* ShadowSceneNode::AddLight(NiLight* a_light, const ShadowSceneNode::LIGHT_CREATE_PARAMS& a_params)
	{
		using func_t = BSLight* (*)(ShadowSceneNode*, NiLight*, const ShadowSceneNode::LIGHT_CREATE_PARAMS&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99692, 106326) };
		return func(this, a_light, a_params);
	}

	void ShadowSceneNode::AddLight(BSLight* a_light)
	{
		using func_t = void (*)(ShadowSceneNode*, BSLight*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99693, 106327) };
		func(this, a_light);
	}

	BSCompoundFrustum* ShadowSceneNode::BuildSharedCompoundFrustum(BSCullingProcess* a_cullingProcess, BSPortal* a_portal)
	{
		using func_t = decltype(&ShadowSceneNode::BuildSharedCompoundFrustum);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99735, 106379) };
		return func(this, a_cullingProcess, a_portal);
	}

	BSLight* ShadowSceneNode::GetLight(NiLight* a_light)
	{
		auto light = GetPointLight(a_light);
		if (!light) {
			light = GetShadowLight(a_light);
		}
		return light;
	}

	BSLight* ShadowSceneNode::GetPointLight(NiLight* a_light)
	{
		for (auto& light : GetRuntimeData().activeLights) {
			if (light && light->light.get() == a_light) {
				return light.get();
			}
		}
		return nullptr;
	}

	BSLight* ShadowSceneNode::GetShadowLight(NiLight* a_light)
	{
		for (auto& light : GetRuntimeData().activeShadowLights) {
			if (light && light->light.get() == a_light) {
				return light.get();
			}
		}
		return nullptr;
	}

	void ShadowSceneNode::RemoveAllLights()
	{
		using func_t = decltype(&ShadowSceneNode::RemoveAllLights);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99704, 106338) };
		func(this);
	}

	void ShadowSceneNode::RemoveLight(NiLight* a_light)
	{
		using func_t = void (*)(ShadowSceneNode*, NiLight*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99697, 106331) };
		func(this, a_light);
	}

	void ShadowSceneNode::RemoveLight(const NiPointer<BSLight>& a_light)
	{
		using func_t = void (*)(ShadowSceneNode*, const NiPointer<BSLight>&);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99698, 106332) };
		func(this, a_light);
	}

	void ShadowSceneNode::SetPortalGraph(BSPortalGraph* a_graph)
	{
		using func_t = decltype(&ShadowSceneNode::SetPortalGraph);
		static REL::Relocation<func_t> func{ RELOCATION_ID(99741, 106385) };
		func(this, a_graph);
	}
}
