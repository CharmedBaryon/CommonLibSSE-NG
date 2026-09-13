#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	struct GrassType
	{
		BSMultiStreamInstanceTriShape* typeShape;        // 00
		ModelDBHandle                  typeModelHandle;  // 08
	};
	static_assert(sizeof(GrassType) == 0x10);

	class BGSGrassManager : public BSTSingletonSDM<BGSGrassManager>
	{
	public:
		static BGSGrassManager* GetSingleton()
		{
			static REL::Relocation<BGSGrassManager**> singleton{ RELOCATION_ID(514292, 400452) };
			return *singleton;
		}

		// members
		bool                                       generateGrassDataFiles;  // 01
		std::uint8_t                               unk02;                   // 02
		std::uint16_t                              unk04;                   // 04
		std::uint32_t                              unk08;                   // 08
		std::uint32_t                              unk0C;                   // 0C
		BSTFixedHashMap<std::uint64_t, GrassType*> grassTypeMap;            // 10
		mutable BSReadWriteLock                    grassTypeLock;           // 38
		mutable BSNonReentrantSpinLock             grassShapeLock;          // 40
		std::uint32_t                              pad44;                   // 44
		BSTArray<BSMultiStreamInstanceTriShape*>   grassShapes;             // 48
		float                                      totalGrassRange;         // 60
		std::uint32_t                              pad64;                   // 64
		NiPointer<NiNode>                          grassNode;               // 68
		std::uint32_t                              grassEvalSize;           // 70
		std::uint32_t                              grassEvalSizeSquared;    // 74
		std::uint32_t                              grassPatchSize;          // 78
		std::uint32_t                              unk7C;                   // 7C
		std::uint16_t*                             instanceData;            // 80
		bool                                       enableGrass;             // 88
	};
	static_assert(sizeof(BGSGrassManager) == 0x90);
}
