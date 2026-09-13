#include "RE/B/BGSTerrainManager.h"

namespace RE
{
	bool& BGSTerrainManager::CameraAboveMaxHeight()
	{
		static REL::Relocation<bool*> cam{ RELOCATION_ID(516109, 402260) };
		return *cam;
	}

	bool& BGSTerrainManager::Enabled()
	{
		static REL::Relocation<bool*> enabled{ RELOCATION_ID(508302, 379909) };
		return *enabled;
	}

	BGSTerrainManager* BGSTerrainManager::GetActiveManager()
	{
		static REL::Relocation<BGSTerrainManager**> mgr{ RELOCATION_ID(516111, 402262) };
		return *mgr;
	}

	BSSpinLock& BGSTerrainManager::GetCameraTerrainLock()
	{
		static REL::Relocation<BSSpinLock*> lock{ RELOCATION_ID(516179, 402330) };
		return *lock;
	}

	NiPointer<NiNode>& BGSTerrainManager::GetLODLandRoot()
	{
		static REL::Relocation<NiPointer<NiNode>*> lodLandRoot{ RELOCATION_ID(516173, 402324) };
		return *lodLandRoot;
	}

	NiNode* BGSTerrainManager::GetLODLandRootForLevel(std::uint32_t a_level)
	{
		using func_t = decltype(&BGSTerrainManager::GetLODLandRootForLevel);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31018, 31803) };
		return func(a_level);
	}

	NiPointer<NiNode>& BGSTerrainManager::GetLODObjectRoot()
	{
		static REL::Relocation<NiPointer<NiNode>*> lodObjectRoot{ RELOCATION_ID(516174, 402325) };
		return *lodObjectRoot;
	}

	NiPointer<NiNode>& BGSTerrainManager::GetLODRoot()
	{
		static REL::Relocation<NiPointer<NiNode>*> lodRoot{ RELOCATION_ID(516172, 402323) };
		return *lodRoot;
	}

	NiPointer<NiNode>& BGSTerrainManager::GetTreeNode()
	{
		static REL::Relocation<NiPointer<NiNode>*> treeNode{ RELOCATION_ID(516170, 402321) };
		return *treeNode;
	}

	NiPointer<NiNode>& BGSTerrainManager::GetWaterNode()
	{
		static REL::Relocation<NiPointer<NiNode>*> waterNode{ RELOCATION_ID(516171, 402322) };
		return *waterNode;
	}

	bool& BGSTerrainManager::LoadScreenUp()
	{
		static REL::Relocation<bool*> up{ RELOCATION_ID(516108, 402259) };
		return *up;
	}

	void BGSTerrainManager::SetCullState(const CullState& a_state)
	{
		using func_t = decltype(&BGSTerrainManager::SetCullState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31036, 31822) };
		func(this, a_state);
	}

	void BGSTerrainManager::UnloadAll(bool a_unloadStaticData, bool a_shutdown)
	{
		using func_t = decltype(&BGSTerrainManager::UnloadAll);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31026, 31812) };
		func(this, a_unloadStaticData, a_shutdown);
	}

	void BGSTerrainManager::Update(const NiPoint3& a_viewPos, const std::int32_t& a_updateType)
	{
		using func_t = decltype(&BGSTerrainManager::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31017, 31802) };
		func(this, a_viewPos, a_updateType);
	}
}
