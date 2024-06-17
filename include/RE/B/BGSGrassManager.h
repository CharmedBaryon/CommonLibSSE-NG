#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	class BGSGrassManager : public BSTSingletonSDM<BGSGrassManager>
	{
	public:
		static BGSGrassManager* GetSingleton()
		{
			REL::Relocation<BGSGrassManager**> singleton{ RELOCATION_ID(514292, 400452) };
			return *singleton;
		}

		// members
		bool                    generateGrassDataFiles;  // 01
		std::uint8_t            unk02;                   // 02
		std::uint16_t           unk04;                   // 04
		std::uint32_t           unk08;                   // 08
		std::uint32_t           unk0C;                   // 0C
		std::uint64_t           unk10;                   // 10 - BSTHashMap<std::uint64_t, GrassType*> ?
		std::uint64_t           unk18;                   // 18
		std::uint64_t           unk20;                   // 20
		std::uint64_t           unk28;                   // 28
		std::uint64_t           unk30;                   // 30
		mutable BSReadWriteLock lock;                    // 38
		std::uint32_t           unk40;                   // 40
		std::uint32_t           pad44;                   // 44
		BSTArray<void*>         unk48;                   // 48
		float                   unk60;                   // 60
		std::uint32_t           pad64;                   // 64
		NiPointer<NiNode>       grassNode;               // 68
		std::uint32_t           grassEvalSize;           // 70
		std::uint32_t           grassEvalSizeSquared;    // 74
		std::uint32_t           unk78;                   // 78
		std::uint32_t           unk7C;                   // 7C
		std::uint64_t           unk80;                   // 80
		bool                    enableGrass;             // 88
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSGrassManager) == 0x90);
}
