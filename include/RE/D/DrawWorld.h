#pragma once

namespace RE
{
	class SceneGraph;
	class Sun;

	struct DrawWorld
	{
		static DrawWorld& GetSingleton()
		{
			static REL::Relocation<DrawWorld*> singleton{ RELOCATION_ID(528082, 415027) };
			return *singleton;
		}

		// members
		NiPoint3         firstPersonNodePosition;  // 00
		float            firstPersonFOV;           // 0C
		float            worldFOV;                 // 10
		std::uint32_t    pad14;                    // 14
		NiAVObject*      pcFirstPerson3D;          // 18
		NiAVObject*      pcThirdPerson3D;          // 20
		SceneGraph*      worldSceneGraph;          // 28
		ShadowSceneNode* mainShadowSceneNode;      // 30
		Sun*             sun;                      // 38
		std::uint32_t    activeShadowLightCount;   // 40
		std::uint32_t    shadowLightCount;         // 44
		std::uint32_t    shadowLightMaskIndex;     // 48
		std::uint32_t    shadowLightMask;          // 4C
		bool             disableUpdateFOV;         // 50
		bool             disableSunShadows;        // 51
		bool             unk52;                    // 52
	};
	static_assert(sizeof(DrawWorld) == 0x58);
}
