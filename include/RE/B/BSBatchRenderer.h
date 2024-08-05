#pragma once

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
		virtual void Unk_01(void);  // 01
		virtual void Unk_02(void);  // 02
		virtual void Unk_03(void);  // 03

		// members
		BSTArray<void*>              unk008;              // 008
		BSTHashMap<UnkKey, UnkValue> unk020;              // 020
		std::uint64_t                unk050;              // 050
		std::uint64_t                unk058;              // 058
		std::uint64_t                unk060;              // 060
		std::uint64_t                unk068;              // 068
		GeometryGroup*               geometryGroups[16];  // 070
		GeometryGroup*               alphaGroup;          // 0F0
		void*                        unk0F8;              // 0F8
		void*                        unk100;              // 100
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSBatchRenderer) == 0x108);
}
