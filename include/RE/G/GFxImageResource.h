#pragma once

#include "RE/G/GFxResource.h"
#include "RE/G/GFxResourceKey.h"
#include "RE/G/GPtr.h"

namespace RE
{
	class GImageInfoBase;

	class GFxImageResource : public GFxResource
	{
	public:
		~GFxImageResource() override;  // 00

		GImageInfoBase* GetImageInfo() const
		{
			return _imageInfo.get();
		}

	protected:
		// members
		GPtr<GImageInfoBase> _imageInfo;  // 18
		GFxResourceKey       _key;        // 20
		ResourceUse          _useType;    // 30
	};
	static_assert(sizeof(GFxImageResource) == 0x38);
}
