#pragma once

#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"

namespace RE
{
	class BSRenderPass;

	class BSBatchRenderer
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSBatchRenderer;
		inline static constexpr auto VTABLE = VTABLE_BSBatchRenderer;

		struct PersistentPassList
		{
			BSRenderPass* head;  // 000
			BSRenderPass* tail;  // 008
		};
		static_assert(sizeof(PersistentPassList) == 0x10);

		struct GeometryGroup
		{
			BSBatchRenderer*   batchRenderer;  // 000
			PersistentPassList passList;       // 008
			std::uintptr_t     UnkPtr4;        // 018
			float              depth;          // 020 Distance from geometry to camera location
			std::uint16_t      count;          // 024
			std::uint8_t       flags;          // 026
		};
		static_assert(sizeof(GeometryGroup) == 0x28);

		struct PassGroup
		{
			BSRenderPass* passes[5];      // 000
			std::uint32_t validPassBits;  // 028 OR'd with (1 << PassIndex)
		};
		static_assert(sizeof(PassGroup) == 0x30);

		virtual ~BSBatchRenderer();  // 00

		// add
		virtual void RegisterPassSorted(BSRenderPass* renderPass, std::uint32_t techniqueID);                            // 01
		virtual void RegisterPass(BSRenderPass* renderPass, std::uint32_t techniqueID);                                  // 02
		virtual void RenderActivePassRange(std::uint32_t firstPass, std::uint32_t lastPass, std::uint32_t renderFlags);  // 03

		void SetupAndDrawPass(BSRenderPass* a_pass, std::uint32_t a_technique, bool a_alphaTest, std::uint32_t a_renderFlags)
		{
			using func_t = decltype(&BSBatchRenderer::SetupAndDrawPass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100854, 107644) };
			func(this, a_pass, a_technique, a_alphaTest, a_renderFlags);
		}

		// members
		BSTArray<PassGroup*>                renderPass;           // 008
		BSTFixedHashMap<uint32_t, uint32_t> renderPassMap;        // 020  Technique ID -> Index in renderPass
		std::uint64_t                       unk48;                // 048
		std::uint32_t                       currentFirstPass;     // 050
		std::uint32_t                       currentLastPass;      // 054
		BSSimpleList<uint32_t>              activePassIndexList;  // 058  head node embedded: item 058, next 060
		std::uint32_t                       groupingAlphasCount;  // 068
		bool                                autoClearPasses;      // 06C
		std::uint8_t                        pad06D;               // 06D
		std::uint16_t                       pad06E;               // 06E
		GeometryGroup*                      geometryGroups[16];   // 070
		GeometryGroup*                      alphaGroup;           // 0F0
		void*                               unk0F8;               // 0F8
		void*                               unk100;               // 100
	};
	static_assert(sizeof(BSBatchRenderer) == 0x108);
}
