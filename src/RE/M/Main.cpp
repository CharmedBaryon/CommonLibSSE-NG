#include "RE/M/Main.h"

#include "RE/N/NiCamera.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/SceneGraph.h"

namespace RE
{
	Main* Main::GetSingleton()
	{
		static REL::Relocation<Main**> singleton{ RELOCATION_ID(516943, 403449) };
		return *singleton;
	}

	bool Main::IsRoomVisible(NiNode* a_room)
	{
		using func_t = decltype(&Main::IsRoomVisible);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35608, 36618) };
		return func(this, a_room);
	}

	float Main::QFrameAnimTime()
	{
		static REL::Relocation<float*> data{ RELOCATION_ID(516940, 403447) };
		return *data;
	}

	NiCamera* Main::WorldRootCamera()
	{
		using func_t = decltype(&Main::WorldRootCamera);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35601, 36609) };
		return func();
	}

	SceneGraph* Main::WorldRootNode()
	{
		static REL::Relocation<NiPointer<SceneGraph>*> nodePtr{ RELOCATION_ID(517006, 403513) };
		return nodePtr->get();
	}

	void Main::RenderWorld(bool a_unk)
	{
		using func_t = decltype(&Main::RenderWorld);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100424, 107142) };
		return func(a_unk);
	}

	void Main::SetActive(bool a_active)
	{
		using func_t = decltype(&Main::SetActive);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35598, 36606) };
		return func(this, a_active);
	}
}
