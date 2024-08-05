#pragma once

#include "RE/B/BSSceneGraph.h"

namespace RE
{
	class SceneGraph : public BSSceneGraph
	{
	public:
		inline static constexpr auto RTTI = RTTI_SceneGraph;
		inline static constexpr auto Ni_RTTI = NiRTTI_SceneGraph;
		inline static constexpr auto VTABLE = VTABLE_SceneGraph;

		~SceneGraph() override;  // 00

		// override (BSSceneGraph)
		const NiRTTI* GetRTTI() const override;    // 02
		float         GetFarDistance() override;   // 3E
		float         GetNearDistance() override;  // 3F

		struct SCENE_GRAPH_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                    \
	float         customNearDistance; /* 140 */ \
	float         customFarDistance;  /* 144 */ \
	bool          useCustomNear;      /* 148 */ \
	bool          useCustomFar;       /* 149 */ \
	std::uint16_t pad14A;             /* 14A */ \
	std::uint32_t pad14C;             /* 14C */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline SCENE_GRAPH_RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<SCENE_GRAPH_RUNTIME_DATA>(this, 0x140, 0x168);
		}

		[[nodiscard]] inline const SCENE_GRAPH_RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<SCENE_GRAPH_RUNTIME_DATA>(this, 0x140, 0x168);
		}

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
}
#undef RUNTIME_DATA_CONTENT
