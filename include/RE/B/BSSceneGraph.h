#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class NiCamera;
	class NiVisibleArray;

	class BSSceneGraph : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSceneGraph;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSSceneGraph;
		inline static constexpr auto VTABLE = VTABLE_BSSceneGraph;

		~BSSceneGraph() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;  // 02

		// add
		virtual float GetFarDistance();                                    // 3E
		virtual float GetNearDistance();                                   // 3F - { return fNearDistance:Display; }
		virtual void  SetViewDistanceBasedOnFrameRate(float a_frameRate);  // 40

		struct BS_SCENE_GRAPH_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                             \
	NiPointer<NiCamera> camera;         /* 128 */        \
	NiVisibleArray*     visArray;       /* 130 - 0x18 */ \
	bool                menuSceneGraph; /* 138 */        \
	std::uint8_t        pad139;         /* 139 */        \
	std::uint16_t       pad13A;         /* 13A */        \
	float               cameraFOV;      /* 13C */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline BS_SCENE_GRAPH_RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<BS_SCENE_GRAPH_RUNTIME_DATA>(this, 0x128, 0x150);
		}

		[[nodiscard]] inline const BS_SCENE_GRAPH_RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<BS_SCENE_GRAPH_RUNTIME_DATA>(this, 0x128, 0x150);
		}

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT
#endif
	};
}
#undef RUNTIME_DATA_CONTENT
