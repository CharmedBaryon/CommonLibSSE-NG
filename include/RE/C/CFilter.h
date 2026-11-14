#pragma once

#include "RE/C/CollisionLayers.h"

namespace RE
{
	enum class BIPED_PART
	{
		kOther = 0,
		kHead = 1,
		kBody = 2,
		kSpine1 = 3,
		kSpine2 = 4,
		kLUpperArm = 5,
		kLForearm = 6,
		kLHand = 7,
		kLThigh = 8,
		kLCalf = 9,
		kLFoot = 10,
		kRUpperArm = 11,
		kRForearm = 12,
		kRHand = 13,
		kRThigh = 14,
		kRCalf = 15,
		kRFoot = 16,
		kTail = 17,
		kShield = 18,
		kQuiver = 19,
		kWeapon = 20,
		kPonyTail = 21,
		kWing = 22,
		kPack = 23,
		kChain = 24,
		kAddonHead = 25,
		kAddonChest = 26,
		kAddonLeg = 27,
		kAddonArm = 28
	};

	class CFilter
	{
	public:
		struct Flags
		{
			enum Flag
			{
				kNone = 0,
				kNoCollision = 1 << 14,
				kLinkedGroup = 1 << 15,

				kPartMask = 0x1F,  // BIPED_PART
				kLayerMask = 0x7F  // COL_LAYER
			};
		};

		COL_LAYER     GetCollisionLayer() const;  // 0–6
		BIPED_PART    GetBipedPart() const;       // 8–12
		bool          QNoCollision() const;       // 14
		bool          QLinkedGroup() const;       // 15
		std::uint32_t GetSystemGroup() const;     // 16–31

		void SetCollisionLayer(COL_LAYER a_layer);
		void SetBipedPart(BIPED_PART a_part);
		void SetNoCollision(bool a_set);
		void SetLinkedGroup(bool a_set);
		void SetSystemGroup(std::uint32_t a_group);

		// members
		std::uint32_t filter;  // 0
	};
	static_assert(sizeof(CFilter) == 0x4);
}
