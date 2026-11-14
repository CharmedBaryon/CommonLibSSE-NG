#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSingleton.h"
#include "RE/C/CollisionLayers.h"
#include "RE/H/hkpCollisionFilter.h"

namespace RE
{
	class bhkCollisionFilter : public hkpCollisionFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCollisionFilter;
		inline static constexpr auto VTABLE = VTABLE_bhkCollisionFilter;

		[[nodiscard]] static bhkCollisionFilter* GetSingleton()
		{
			static REL::Relocation<bhkCollisionFilter**> singleton{ RELOCATION_ID(514415, 400562) };
			return *singleton;
		}

		~bhkCollisionFilter() override;  // 00

		std::uint32_t GetNewSystemGroup()
		{
			nextSystemGroup = nextSystemGroup + 1;
			if (nextSystemGroup == 65535) {
				nextSystemGroup = 10;
			}
			return nextSystemGroup;
		}

		// Sets or clears the mutual collision bit between two layers in layerBitfields.
		void SetLayerPairCollisionEnabled(COL_LAYER a_layerA, COL_LAYER a_layerB, bool a_enabled);

		// Sets layerBitfields[a_layer] to a_mask and mirrors each bit into the other layers' rows.
		void SetLayerBitfield(COL_LAYER a_layer, std::uint64_t a_mask);

		// members
		std::uint32_t unk48;                     // 048
		std::uint32_t nextSystemGroup;           // 04C
		std::uint32_t bipedBitfields[32];        // 050
		std::uint32_t layerCollisionGroups[64];  // 0D0
		std::uint64_t layerBitfields[64];        // 1D0
		std::uint64_t triggerField;              // 3D0
		std::uint64_t sensorField;               // 3D8
		BSFixedString collisionLayerNames[64];   // 3E0
		std::uint8_t  unk5E0[256];               // 5E0
		BSFixedString collisionBoneNames[32];    // 6E0
	};
	static_assert(sizeof(bhkCollisionFilter) == 0x7E0);
}
