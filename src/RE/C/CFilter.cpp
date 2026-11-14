#include "RE/C/CFilter.h"

namespace RE
{
	COL_LAYER CFilter::GetCollisionLayer() const
	{
		return static_cast<COL_LAYER>(filter & Flags::kLayerMask);
	}

	BIPED_PART CFilter::GetBipedPart() const
	{
		return static_cast<BIPED_PART>((filter >> 8) & Flags::kPartMask);
	}

	bool CFilter::QNoCollision() const
	{
		return (filter >> 14) & 1;
	}

	bool CFilter::QLinkedGroup() const
	{
		return (filter >> 15) & 1;
	}

	std::uint32_t CFilter::GetSystemGroup() const
	{
		return filter >> 16;
	}

	void CFilter::SetCollisionLayer(COL_LAYER a_layer)
	{
		filter &= ~(Flags::kLayerMask);
		filter |= (std::to_underlying(a_layer) & Flags::kLayerMask);
	}

	void CFilter::SetBipedPart(BIPED_PART a_part)
	{
		filter &= ~(Flags::kPartMask << 8);
		filter |= ((std::to_underlying(a_part) & Flags::kPartMask) << 8);
	}

	void CFilter::SetNoCollision(bool a_set)
	{
		if (a_set) {
			filter |= Flags::kNoCollision;
		} else {
			filter &= ~Flags::kNoCollision;
		}
	}

	void CFilter::SetLinkedGroup(bool a_set)
	{
		if (a_set) {
			filter |= Flags::kLinkedGroup;
		} else {
			filter &= ~Flags::kLinkedGroup;
		}
	}

	void CFilter::SetSystemGroup(std::uint32_t a_group)
	{
		filter &= 0x0000FFFF;
		filter |= a_group << 16;
	}
}
