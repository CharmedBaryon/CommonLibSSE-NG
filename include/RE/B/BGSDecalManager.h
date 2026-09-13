#pragma once

#include "RE/B/BGSDecalGroup.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTempEffectSimpleDecal.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSShaderAccumulator;
	class NiCamera;

	class BGSDecalManager
	{
	public:
		static BGSDecalManager* GetSingleton()
		{
			static REL::Relocation<BGSDecalManager**> singleton{ RELOCATION_ID(514414, 400561) };
			return *singleton;
		}

		// The engine call every vanilla decal (blood, scorch) already goes
		// through -- lets a caller place one without a real hit event.
		void ApplyDecal(DECAL_CREATION_DATA& a_data, bool a_forceDecal = false, BGSDecalGroup* a_group = nullptr)
		{
			using func_t = decltype(&BGSDecalManager::ApplyDecal);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15029, 15203) };
			return func(this, a_data, a_forceDecal, a_group);
		}

		// members
		std::uint32_t                                unk00;                       // 00
		std::uint32_t                                decalCountCurrentFrame;      // 04
		std::uint32_t                                skinDecalCountCurrentFrame;  // 08
		std::uint32_t                                decalCount;                  // 0C
		std::uint32_t                                skinDecalCount;              // 10
		bool                                         unk14;                       // 14
		std::uint8_t                                 pad15;                       // 15
		std::uint16_t                                pad16;                       // 16
		BSTArray<NiPointer<BSTempEffect>>            decals;                      // 18
		BSTArray<NiPointer<BGSDecalEmitter>>         decalEmitters;               // 30
		BSTArray<NiPointer<BGSDecalNode>>            decalNodes;                  // 48
		BSTArray<NiPointer<BSTempEffectSimpleDecal>> simpleDecals;                // 60
		NiPointer<NiCamera>                          camera;                      // 78
		NiPointer<BSShaderAccumulator>               shaderAccumulator;           // 80
		std::uint32_t                                unk88;                       // 88
	};
	static_assert(sizeof(BGSDecalManager) == 0x90);
};
