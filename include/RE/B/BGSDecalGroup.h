#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSTextureSet;
	class NiAVObject;
	class NiNode;
	class TESObjectCELL;

	struct DECAL_CREATION_DATA
	{
	public:
		// members (defaults match the engine constructor; the struct stays an aggregate)
		NiPoint3              origin{};                 // 00
		NiPoint3              direction{};              // 0C - the hit surface normal when placed by an impact
		NiPoint3              surfaceNormal{};          // 18
		ObjectRefHandle       objRef{};                 // 24
		NiPointer<NiAVObject> avObj{};                  // 28 - ApplyDecal does nothing while this is null; must resolve to a node
		NiNode*               clone{ nullptr };         // 30
		BGSTextureSet*        texSet{ nullptr };        // 38
		BGSTextureSet*        texSet2{ nullptr };       // 40
		std::int32_t          unk48{ -1 };              // 48
		float                 width{ 0.0f };            // 4C
		float                 height{ 0.0f };           // 50
		float                 depth{ 0.0f };            // 54
		NiMatrix3             rotation{};               // 58 - the source object's rotation for an impact; identity otherwise
		TESObjectCELL*        parentCell{ nullptr };    // 80
		float                 parallaxScale{ 0.0f };    // 88
		std::uint32_t         unk8C{ 0 };               // 8C
		std::uint64_t         unk90{ 0 };               // 90
		float                 shininess{ 4.0f };        // 98
		float                 angleThreshold{ 15.0f };  // 9C
		float                 unkA0{ 16.0f };           // A0
		float                 colorR{ 1.0f };           // A4
		float                 colorG{ 1.0f };           // A8
		float                 colorB{ 1.0f };           // AC
		std::uint32_t         unkB0{ 0 };               // B0
		std::uint16_t         unkB4{ 0 };               // B4
		std::uint8_t          unkB6{ 1 };               // B6
		std::uint8_t          parallax{ 0 };            // B7
		std::uint8_t          alphaTesting{ 1 };        // B8
		std::uint8_t          alphaBlending{ 0 };       // B9
		std::uint8_t          parallaxPasses{ 0 };      // BA
		std::uint8_t          unkBB{ 0 };               // BB - nonzero skips ApplyDecal's decal-LOD distance gate
		std::uint16_t         unkBC{ 0 };               // BC
		std::uint8_t          unkBE{ 0 };               // BE
		std::uint8_t          padBF{ 0 };               // BF
		std::uint32_t         unkC0{ 0 };               // C0 - 1-based index of the only shape to decal; 0 = every eligible shape
		std::uint32_t         padC4{ 0 };               // C4
	};
	static_assert(sizeof(DECAL_CREATION_DATA) == 0xC8);
	static_assert(offsetof(DECAL_CREATION_DATA, avObj) == 0x28);
	static_assert(offsetof(DECAL_CREATION_DATA, texSet) == 0x38);
	static_assert(offsetof(DECAL_CREATION_DATA, width) == 0x4C);
	static_assert(offsetof(DECAL_CREATION_DATA, rotation) == 0x58);
	static_assert(offsetof(DECAL_CREATION_DATA, parentCell) == 0x80);
	static_assert(offsetof(DECAL_CREATION_DATA, shininess) == 0x98);
	static_assert(offsetof(DECAL_CREATION_DATA, colorR) == 0xA4);
	static_assert(offsetof(DECAL_CREATION_DATA, unkC0) == 0xC0);

	struct BGSDecalGroup
	{
	public:
		// members
		bool                           permanentGroup;  // 00
		bool                           manualSaveLoad;  // 01
		std::uint16_t                  pad02;           // 02
		std::uint32_t                  pad04;           // 04
		BSTArray<std::uint32_t>        decalGroups;     // 08
		BSTArray<DECAL_CREATION_DATA*> pendingDecals;   // 20
	};
	static_assert(sizeof(BGSDecalGroup) == 0x38);
}
