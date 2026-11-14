#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiExtraData.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSFurnitureMarker
	{
	public:
		enum class AnimationType
		{
			kSit = 1 << 0,
			kSleep = 1 << 1,
			kLean = 1 << 2
		};

		enum class EntryProperties
		{
			kFront = 1 << 0,
			kBehind = 1 << 1,
			kRight = 1 << 2,
			kLeft = 1 << 3,
			kUp = 1 << 4
		};

		NiPoint3                                     offset;           // 00
		float                                        heading;          // 0C
		REX::EnumSet<AnimationType, std::uint16_t>   animationType;    // 10
		REX::EnumSet<EntryProperties, std::uint16_t> entryProperties;  // 12
	};

	class BSFurnitureMarkerNode : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFurnitureMarkerNode;
		inline static auto           NiRTTI = NiRTTI_BSFurnitureMarkerNode;

		[[nodiscard]] static BSFurnitureMarkerNode* FindBSFurnitureMarkerNode(NiObjectNET* a_object)
		{
			using func_t = decltype(&BSFurnitureMarkerNode::FindBSFurnitureMarkerNode);
			static REL::Relocation<func_t> func{ RELOCATION_ID(74889, 76647) };
			return func(a_object);
		}

		[[nodiscard]] static std::uint32_t GetNumFurnitureMarkers(NiObjectNET* a_object)
		{
			const auto markerNode = FindBSFurnitureMarkerNode(a_object);
			return markerNode ? markerNode->markers.size() : 0;
		}

		// members
		BSTArray<BSFurnitureMarker> markers;  // 18
	};
}
